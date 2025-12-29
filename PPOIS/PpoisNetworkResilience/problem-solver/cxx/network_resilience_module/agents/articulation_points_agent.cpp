#include "articulation_points_agent.hpp"
#include "../keynodes/resilience_keynodes.hpp"
#include <sc-memory/sc_memory.hpp>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

ScAddr ArticulationPointsAgent::GetActionClass() const
{
  return ResilienceKeynodes::action_find_articulation_points;
}

ScResult ArticulationPointsAgent::DoProgram(ScAction & action)
{
  m_logger.Info("Starting Articulation Points Search");
  auto const & [argsAddr] = action.GetArguments<1>();
  ScAddr graphNode = argsAddr;

  if (!m_context.IsElement(graphNode))
  {
    return action.FinishWithError();
  }

  vector<ScAddr> nodes;
  map<size_t, vector<size_t>> adj;
  map<ScAddr, size_t, ScAddrLessFunc> addrToIndex;
  map<size_t, ScAddr> indexToAddr;

  ScIterator3Ptr itNodes =
      m_context.CreateIterator3(ResilienceKeynodes::concept_device, ScType::ConstPermPosArc, ScType::Unknown);

  size_t idx = 0;
  while (itNodes->Next())
  {
    ScAddr node = itNodes->Get(2);
    if (m_context.CheckConnector(graphNode, node, ScType::ConstPermPosArc))
    {
      nodes.push_back(node);
      addrToIndex[node] = idx;
      indexToAddr[idx] = node;
      idx++;
    }
  }

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
        adj[v].push_back(u);
      }
    }
  }

  size_t n = nodes.size();
  vector<bool> visited(n, false);
  vector<int> tin(n, -1), low(n, -1);
  int timer = 0;
  vector<ScAddr> articulationPoints;

  std::function<void(int, int)> dfs = [&](int u, int p = -1)
  {
    visited[u] = true;
    tin[u] = low[u] = timer++;
    int children = 0;
    for (int v : adj[u])
    {
      if (v == p)
        continue;
      if (visited[v])
      {
        low[u] = min(low[u], tin[v]);
      }
      else
      {
        dfs(v, u);
        low[u] = min(low[u], low[v]);
        if (low[v] >= tin[u] && p != -1)
          articulationPoints.push_back(indexToAddr[u]);
        children++;
      }
    }
    if (p == -1 && children > 1)
      articulationPoints.push_back(indexToAddr[u]);
  };

  for (size_t i = 0; i < n; ++i)
  {
    if (!visited[i])
      dfs(i, -1);
  }

  ScStructure result = m_context.GenerateStructure();
  for (auto const & ap : articulationPoints)
  {
    result << ap;
  }

  sort(articulationPoints.begin(), articulationPoints.end(), ScAddrLessFunc());
  articulationPoints.erase(unique(articulationPoints.begin(), articulationPoints.end()), articulationPoints.end());

  action.SetResult(result);
  return action.FinishSuccessfully();
}
