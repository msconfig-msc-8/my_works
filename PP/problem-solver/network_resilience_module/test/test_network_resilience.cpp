#include <gtest/gtest.h>
#include <sc-memory/test/sc_test.hpp>

#include "agent/AnalyzeNetworkResilienceAgent.hpp"
#include "keynodes/network_resilience_keynodes.hpp"

using NetworkResilienceTest = ScMemoryTest;

namespace
{
ScAddr MakeUndirectedConnection(ScMemoryContext & ctx, ScAddr const & a, ScAddr const & b)
{
  ScAddr arc = ctx.GenerateConnector(ScType::ConstCommonArc, a, b);
  ctx.GenerateConnector(ScType::ConstPermPosArc, NetworkResilienceKeynodes::nrel_physical_connection, arc);
  return arc;
}

int ReadIntRelation(ScMemoryContext & ctx, ScAddr const & subject, ScAddr const & rel)
{
  ScIterator5Ptr it5 = ctx.CreateIterator5(
      subject,
      ScType::ConstCommonArc,
      ScType::ConstNodeLink,
      ScType::ConstPermPosArc,
      rel);
  if (!it5->Next()) return -1;
  std::string content;
  ctx.GetLinkContent(it5->Get(2), content);
  return std::stoi(content);
}

ScAddr ReadSetByRelation(ScMemoryContext & ctx, ScAddr const & subject, ScAddr const & rel)
{
  ScIterator5Ptr it5 = ctx.CreateIterator5(
      subject,
      ScType::ConstCommonArc,
      ScType::ConstNode,
      ScType::ConstPermPosArc,
      rel);
  if (!it5->Next()) return ScAddr();
  return it5->Get(2);
}

size_t CountSetElements(ScMemoryContext & ctx, ScAddr const & setNode)
{
  size_t cnt = 0;
  ScIterator3Ptr it3 = ctx.CreateIterator3(setNode, ScType::ConstPermPosArc, ScType::Unknown);
  while (it3->Next()) ++cnt;
  return cnt;
}
}
bool HasMember(ScMemoryContext & ctx, ScAddr const & setNode, ScAddr const & elem)
{
  ScIterator3Ptr it3 = ctx.CreateIterator3(setNode, ScType::ConstPermPosArc, elem);
  return it3->Next();
}


TEST_F(NetworkResilienceTest, CycleGraphHasConnectivity2)
{
  m_ctx->SubscribeAgent<AnalyzeNetworkResilienceAgent>();

  ScStructure topology = m_ctx->GenerateStructure();

  ScAddr v0 = m_ctx->GenerateNode(ScType::ConstNode);
  ScAddr v1 = m_ctx->GenerateNode(ScType::ConstNode);
  ScAddr v2 = m_ctx->GenerateNode(ScType::ConstNode);
  ScAddr v3 = m_ctx->GenerateNode(ScType::ConstNode);

  // Add vertices to topology
  m_ctx->GenerateConnector(ScType::ConstPermPosArc, topology, v0);
  m_ctx->GenerateConnector(ScType::ConstPermPosArc, topology, v1);
  m_ctx->GenerateConnector(ScType::ConstPermPosArc, topology, v2);
  m_ctx->GenerateConnector(ScType::ConstPermPosArc, topology, v3);

  // Cycle: v0-v1-v2-v3-v0
  MakeUndirectedConnection(*m_ctx, v0, v1);
  MakeUndirectedConnection(*m_ctx, v1, v2);
  MakeUndirectedConnection(*m_ctx, v2, v3);
  MakeUndirectedConnection(*m_ctx, v3, v0);

  ScAction action = m_ctx->GenerateAction(NetworkResilienceKeynodes::action_analyze_network_resilience);
  action.SetArgument(1, topology);

  EXPECT_TRUE(action.InitiateAndWait());
  EXPECT_TRUE(action.IsFinishedSuccessfully());

  int kappa = ReadIntRelation(*m_ctx, topology, NetworkResilienceKeynodes::nrel_vertex_connectivity);
  int lambda = ReadIntRelation(*m_ctx, topology, NetworkResilienceKeynodes::nrel_edge_connectivity);

  EXPECT_EQ(kappa, 2);
  EXPECT_EQ(lambda, 2);

  ScAddr arts = ReadSetByRelation(*m_ctx, topology, NetworkResilienceKeynodes::nrel_articulation_points);
  ScAddr bridges = ReadSetByRelation(*m_ctx, topology, NetworkResilienceKeynodes::nrel_bridge_connections);

  EXPECT_TRUE(arts.IsValid());
  EXPECT_TRUE(bridges.IsValid());

  EXPECT_EQ(CountSetElements(*m_ctx, arts), 0u);
  EXPECT_EQ(CountSetElements(*m_ctx, bridges), 0u);

  m_ctx->UnsubscribeAgent<AnalyzeNetworkResilienceAgent>();
}

TEST_F(NetworkResilienceTest, ChainGraphHasArticulationPointsAndBridges)
{
  m_ctx->SubscribeAgent<AnalyzeNetworkResilienceAgent>();

  ScStructure topology = m_ctx->GenerateStructure();

  std::vector<ScAddr> v(5);
  for (auto & x : v)
  {
    x = m_ctx->GenerateNode(ScType::ConstNode);
    m_ctx->GenerateConnector(ScType::ConstPermPosArc, topology, x);
  }

  // Chain v0-v1-v2-v3-v4
  MakeUndirectedConnection(*m_ctx, v[0], v[1]);
  MakeUndirectedConnection(*m_ctx, v[1], v[2]);
  MakeUndirectedConnection(*m_ctx, v[2], v[3]);
  MakeUndirectedConnection(*m_ctx, v[3], v[4]);

  ScAction action = m_ctx->GenerateAction(NetworkResilienceKeynodes::action_analyze_network_resilience);
  action.SetArgument(1, topology);

  EXPECT_TRUE(action.InitiateAndWait());
  EXPECT_TRUE(action.IsFinishedSuccessfully());

  int kappa = ReadIntRelation(*m_ctx, topology, NetworkResilienceKeynodes::nrel_vertex_connectivity);
  int lambda = ReadIntRelation(*m_ctx, topology, NetworkResilienceKeynodes::nrel_edge_connectivity);

  EXPECT_EQ(kappa, 1);
  EXPECT_EQ(lambda, 1);

  ScAddr arts = ReadSetByRelation(*m_ctx, topology, NetworkResilienceKeynodes::nrel_articulation_points);
  ScAddr bridges = ReadSetByRelation(*m_ctx, topology, NetworkResilienceKeynodes::nrel_bridge_connections);

  EXPECT_TRUE(arts.IsValid());
  EXPECT_TRUE(bridges.IsValid());

  // In a chain of 5: articulation points are v1,v2,v3 (3 points)
  EXPECT_EQ(CountSetElements(*m_ctx, arts), 3u);
  // All 4 edges are bridges
  EXPECT_EQ(CountSetElements(*m_ctx, bridges), 4u);

  m_ctx->UnsubscribeAgent<AnalyzeNetworkResilienceAgent>();
}

TEST_F(NetworkResilienceTest, StarGraphHasOneArticulationAndAllBridges)
{
  m_ctx->SubscribeAgent<AnalyzeNetworkResilienceAgent>();

  ScStructure topology = m_ctx->GenerateStructure();

  ScAddr center = m_ctx->GenerateNode(ScType::ConstNode);
  m_ctx->GenerateConnector(ScType::ConstPermPosArc, topology, center);

  std::vector<ScAddr> leaf(4);
  for (auto & x : leaf)
  {
    x = m_ctx->GenerateNode(ScType::ConstNode);
    m_ctx->GenerateConnector(ScType::ConstPermPosArc, topology, x);
  }

  // Star: center connected to all leaves
  std::vector<ScAddr> arcs;
  arcs.reserve(4);
  for (auto const & x : leaf)
    arcs.push_back(MakeUndirectedConnection(*m_ctx, center, x));

  ScAction action = m_ctx->GenerateAction(NetworkResilienceKeynodes::action_analyze_network_resilience);
  action.SetArgument(1, topology);

  EXPECT_TRUE(action.InitiateAndWait());
  EXPECT_TRUE(action.IsFinishedSuccessfully());

  int kappa = ReadIntRelation(*m_ctx, topology, NetworkResilienceKeynodes::nrel_vertex_connectivity);
  int lambda = ReadIntRelation(*m_ctx, topology, NetworkResilienceKeynodes::nrel_edge_connectivity);

  EXPECT_EQ(kappa, 1);
  EXPECT_EQ(lambda, 1);

  ScAddr arts = ReadSetByRelation(*m_ctx, topology, NetworkResilienceKeynodes::nrel_articulation_points);
  ScAddr bridges = ReadSetByRelation(*m_ctx, topology, NetworkResilienceKeynodes::nrel_bridge_connections);

  EXPECT_TRUE(arts.IsValid());
  EXPECT_TRUE(bridges.IsValid());

  EXPECT_EQ(CountSetElements(*m_ctx, arts), 1u);
  EXPECT_EQ(CountSetElements(*m_ctx, bridges), 4u);

  // Strong checks: center is articulation, leaves are not
  EXPECT_TRUE(HasMember(*m_ctx, arts, center));
  for (auto const & x : leaf)
    EXPECT_FALSE(HasMember(*m_ctx, arts, x));

  // Strong checks: all star edges are bridges
  for (auto const & a : arcs)
    EXPECT_TRUE(HasMember(*m_ctx, bridges, a));

  m_ctx->UnsubscribeAgent<AnalyzeNetworkResilienceAgent>();
}
TEST_F(NetworkResilienceTest, BowtieGraphHasArticulationButNoBridgesAndEdgeConn2)
{
  m_ctx->SubscribeAgent<AnalyzeNetworkResilienceAgent>();

  ScStructure topology = m_ctx->GenerateStructure();

  // vertices 0..4
  ScAddr v0 = m_ctx->GenerateNode(ScType::ConstNode);
  ScAddr v1 = m_ctx->GenerateNode(ScType::ConstNode);
  ScAddr v2 = m_ctx->GenerateNode(ScType::ConstNode);
  ScAddr v3 = m_ctx->GenerateNode(ScType::ConstNode);
  ScAddr v4 = m_ctx->GenerateNode(ScType::ConstNode);

  // add to topology
  m_ctx->GenerateConnector(ScType::ConstPermPosArc, topology, v0);
  m_ctx->GenerateConnector(ScType::ConstPermPosArc, topology, v1);
  m_ctx->GenerateConnector(ScType::ConstPermPosArc, topology, v2);
  m_ctx->GenerateConnector(ScType::ConstPermPosArc, topology, v3);
  m_ctx->GenerateConnector(ScType::ConstPermPosArc, topology, v4);

  // edges: triangle (0,1,2) and triangle (0,3,4)
  MakeUndirectedConnection(*m_ctx, v0, v1);
  MakeUndirectedConnection(*m_ctx, v1, v2);
  MakeUndirectedConnection(*m_ctx, v2, v0);

  MakeUndirectedConnection(*m_ctx, v0, v3);
  MakeUndirectedConnection(*m_ctx, v3, v4);
  MakeUndirectedConnection(*m_ctx, v4, v0);

  ScAction action = m_ctx->GenerateAction(NetworkResilienceKeynodes::action_analyze_network_resilience);
  action.SetArgument(1, topology);

  EXPECT_TRUE(action.InitiateAndWait());
  EXPECT_TRUE(action.IsFinishedSuccessfully());

  int kappa = ReadIntRelation(*m_ctx, topology, NetworkResilienceKeynodes::nrel_vertex_connectivity);
  int lambda = ReadIntRelation(*m_ctx, topology, NetworkResilienceKeynodes::nrel_edge_connectivity);

  EXPECT_EQ(kappa, 1);
  EXPECT_EQ(lambda, 2);

  ScAddr arts = ReadSetByRelation(*m_ctx, topology, NetworkResilienceKeynodes::nrel_articulation_points);
  ScAddr bridges = ReadSetByRelation(*m_ctx, topology, NetworkResilienceKeynodes::nrel_bridge_connections);

  EXPECT_TRUE(arts.IsValid());
  EXPECT_TRUE(bridges.IsValid());

  EXPECT_EQ(CountSetElements(*m_ctx, arts), 1u);
  EXPECT_EQ(CountSetElements(*m_ctx, bridges), 0u);

  EXPECT_TRUE(HasMember(*m_ctx, arts, v0));
  EXPECT_FALSE(HasMember(*m_ctx, arts, v1));
  EXPECT_FALSE(HasMember(*m_ctx, arts, v2));
  EXPECT_FALSE(HasMember(*m_ctx, arts, v3));
  EXPECT_FALSE(HasMember(*m_ctx, arts, v4));

  m_ctx->UnsubscribeAgent<AnalyzeNetworkResilienceAgent>();
}
