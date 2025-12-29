#include "vertex_connectivity_agent.hpp"
#include "../keynodes/resilience_keynodes.hpp"
#include <sc-memory/sc_memory.hpp>
#include <sc-memory/sc_link.hpp>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

ScAddr VertexConnectivityAgent::GetActionClass() const
{
  return ResilienceKeynodes::action_find_vertex_connectivity;
}

ScResult VertexConnectivityAgent::DoProgram(ScAction & action)
{
  m_logger.Info("Starting Vertex Connectivity Calculation");
  auto const & [argsAddr] = action.GetArguments<1>();
  ScAddr graphNode = argsAddr;

  if (!m_context.IsElement(graphNode))
    return action.FinishWithError();

  vector<ScAddr> nodes;
  map<size_t, vector<size_t>> adj;
  map<ScAddr, size_t, ScAddrLessFunc> addrToIndex;

  ScIterator3Ptr itNodes =
      m_context.CreateIterator3(ResilienceKeynodes::concept_device, ScType::ConstPermPosArc, ScType::Unknown);

  size_t idx = 0;
  while (itNodes->Next())
  {
    ScAddr node = itNodes->Get(2);
    if (m_context.CheckConnector(graphNode, node, ScType::ConstPermPosArc))
    {
      nodes.push_back(node);
      addrToIndex[node] = idx++;
    }
  }

  if (nodes.empty())
    return action.FinishWithError();

  for (auto const & node : nodes)
  {
    size_t u = addrToIndex[node];
    ScIterator5Ptr itEdges = m_context.CreateIterator5(
        node, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, ResilienceKeynodes::nrel_connected_to);
    while (itEdges->Next())
    {
      ScAddr neighbor = itEdges->Get(2);
      if (addrToIndex.count(neighbor))
      {
        size_t v = addrToIndex[neighbor];
        adj[u].push_back(v);
      }
    }
  }

  vector<bool> visited(nodes.size(), false);
  vector<size_t> q;
  q.push_back(0);
  visited[0] = true;
  size_t head = 0;
  while (head < q.size())
  {
    size_t u = q[head++];
    for (size_t v : adj[u])
    {
      if (!visited[v])
      {
        visited[v] = true;
        q.push_back(v);
      }
    }
  }

  bool connected = (q.size() == nodes.size());

  ScAddr resultLink = m_context.GenerateLink();
  std::string resStr = connected ? "Connected (Connectivity >= 1)" : "Disconnected (Connectivity = 0)";
  m_context.SetLinkContent(resultLink, resStr);

  ScStructure result = m_context.GenerateStructure();
  result << resultLink;

  action.SetResult(result);
  return action.FinishSuccessfully();
}
