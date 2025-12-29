#include <sc-memory/test/sc_test.hpp>
#include <sc-memory/sc_memory.hpp>
#include <sc-memory/sc_addr.hpp>
#include <sc-memory/sc_type.hpp>
#include <sc-memory/sc_iterator.hpp>
#include <sc-memory/sc_link.hpp>
#include "../agents/articulation_points_agent.hpp"
#include "../agents/bridges_agent.hpp"
#include "../agents/vertex_connectivity_agent.hpp"
#include "../keynodes/resilience_keynodes.hpp"

using AgentTest = ScMemoryTest;

ScAddr create_device(ScMemoryContext * ctx)
{
  ScAddr node = ctx->GenerateNode(ScType::ConstNode);
  ctx->GenerateConnector(ScType::ConstPermPosArc, ResilienceKeynodes::concept_device, node);
  return node;
}

void connect_devices(ScMemoryContext * ctx, ScAddr d1, ScAddr d2)
{
  ScAddr arc = ctx->GenerateConnector(ScType::ConstCommonArc, d1, d2);
  ctx->GenerateConnector(ScType::ConstPermPosArc, ResilienceKeynodes::nrel_connected_to, arc);
}

TEST_F(AgentTest, ArticulationPointsLineGraph)
{
  ScAddr a = create_device(m_ctx.get());
  ScAddr b = create_device(m_ctx.get());
  ScAddr c = create_device(m_ctx.get());

  connect_devices(m_ctx.get(), a, b);
  connect_devices(m_ctx.get(), b, c);

  m_ctx->SubscribeAgent<ArticulationPointsAgent>();

  ScStructure structNode = m_ctx->GenerateStructure();
  structNode << a << b << c;

  ScAction action = m_ctx->GenerateAction(ResilienceKeynodes::action_find_articulation_points);
  action.SetArguments(structNode);

  EXPECT_TRUE(action.InitiateAndWait());
  EXPECT_TRUE(action.IsFinishedSuccessfully());

  ScAddr res = action.GetResult();
  EXPECT_TRUE(m_ctx->CheckConnector(res, b, ScType::ConstPermPosArc));
  EXPECT_FALSE(m_ctx->CheckConnector(res, a, ScType::ConstPermPosArc));
  EXPECT_FALSE(m_ctx->CheckConnector(res, c, ScType::ConstPermPosArc));

  m_ctx->UnsubscribeAgent<ArticulationPointsAgent>();
}

TEST_F(AgentTest, BridgesLineGraph)
{
  ScAddr a = create_device(m_ctx.get());
  ScAddr b = create_device(m_ctx.get());
  ScAddr c = create_device(m_ctx.get());

  connect_devices(m_ctx.get(), a, b);
  connect_devices(m_ctx.get(), b, c);

  m_ctx->SubscribeAgent<BridgesAgent>();

  ScStructure structNode = m_ctx->GenerateStructure();
  structNode << a << b << c;

  ScAction action = m_ctx->GenerateAction(ResilienceKeynodes::action_find_bridges);
  action.SetArguments(structNode);

  EXPECT_TRUE(action.InitiateAndWait());
  EXPECT_TRUE(action.IsFinishedSuccessfully());

  ScAddr res = action.GetResult();
  int count = 0;
  ScIterator3Ptr it = m_ctx->CreateIterator3(res, ScType::ConstPermPosArc, ScType::ConstCommonArc);
  while (it->Next())
    count++;
  EXPECT_EQ(count, 2);

  m_ctx->UnsubscribeAgent<BridgesAgent>();
}

TEST_F(AgentTest, VertexConnectivityCheck)
{
  ScAddr a = create_device(m_ctx.get());
  ScAddr b = create_device(m_ctx.get());
  connect_devices(m_ctx.get(), a, b);

  m_ctx->SubscribeAgent<VertexConnectivityAgent>();

  ScStructure structNode = m_ctx->GenerateStructure();
  structNode << a << b;

  ScAction action = m_ctx->GenerateAction(ResilienceKeynodes::action_find_vertex_connectivity);
  action.SetArguments(structNode);

  EXPECT_TRUE(action.InitiateAndWait());
  EXPECT_TRUE(action.IsFinishedSuccessfully());

  ScAddr res = action.GetResult();
  ScIterator3Ptr it = m_ctx->CreateIterator3(res, ScType::ConstPermPosArc, ScType::ConstNodeLink);
  EXPECT_TRUE(it->Next());

  m_ctx->UnsubscribeAgent<VertexConnectivityAgent>();
}
