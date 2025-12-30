#include "AnalyzeNetworkResilienceAgent.hpp"

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <string>
#include <unordered_set>
#include <utility>

#include <sc-memory/sc_memory.hpp>

#include "../keynodes/network_resilience_keynodes.hpp"

namespace
{
struct Dinic
{
  struct E
  {
    int to;
    int rev;
    int cap;
  };

  int n;
  std::vector<std::vector<E>> g;
  std::vector<int> level;
  std::vector<int> it;

  explicit Dinic(int n)
      : n(n)
      , g(n)
      , level(n)
      , it(n)
  {
  }

  void addEdge(int fr, int to, int cap)
  {
    E a{to, (int)g[to].size(), cap};
    E b{fr, (int)g[fr].size(), 0};
    g[fr].push_back(a);
    g[to].push_back(b);
  }

  bool bfs(int s, int t)
  {
    std::fill(level.begin(), level.end(), -1);
    std::queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty())
    {
      int v = q.front();
      q.pop();
      for (auto const & e : g[v])
      {
        if (e.cap > 0 && level[e.to] < 0)
        {
          level[e.to] = level[v] + 1;
          q.push(e.to);
        }
      }
    }
    return level[t] >= 0;
  }

  int dfs(int v, int t, int f)
  {
    if (!f) return 0;
    if (v == t) return f;
    for (int & i = it[v]; i < (int)g[v].size(); ++i)
    {
      E & e = g[v][i];
      if (e.cap <= 0) continue;
      if (level[e.to] != level[v] + 1) continue;
      int pushed = dfs(e.to, t, std::min(f, e.cap));
      if (pushed)
      {
        e.cap -= pushed;
        g[e.to][e.rev].cap += pushed;
        return pushed;
      }
    }
    return 0;
  }

  int maxflow(int s, int t, int limit = std::numeric_limits<int>::max())
  {
    int flow = 0;
    while (flow < limit && bfs(s, t))
    {
      std::fill(it.begin(), it.end(), 0);
      while (flow < limit)
      {
        int pushed = dfs(s, t, limit - flow);
        if (!pushed) break;
        flow += pushed;
      }
    }
    return flow;
  }
};

bool IsConnected(AnalyzeNetworkResilienceAgent::Graph const & graph)
{
  if (graph.vertices.empty()) return true;
  std::vector<char> vis(graph.vertices.size(), 0);
  std::queue<int> q;
  vis[0] = 1;
  q.push(0);
  while (!q.empty())
  {
    int v = q.front();
    q.pop();
    for (auto const & [to, eid] : graph.adj[v])
    {
      (void)eid;
      if (!vis[to])
      {
        vis[to] = 1;
        q.push(to);
      }
    }
  }
  for (char x : vis)
    if (!x) return false;
  return true;
}

} // namespace

AnalyzeNetworkResilienceAgent::AnalyzeNetworkResilienceAgent() = default;

ScAddr AnalyzeNetworkResilienceAgent::GetActionClass() const
{
  return NetworkResilienceKeynodes::action_analyze_network_resilience;
}

ScResult AnalyzeNetworkResilienceAgent::DoProgram(ScAction & action)
{
  auto const & [topology] = action.GetArguments<1>();

  if (!topology.IsValid())
    return action.FinishWithError();

  Graph graph;
  std::string error;
  if (!BuildGraphFromTopology(topology, graph, error))
  {
    return action.FinishWithError();
  }

  std::vector<int> articulationVertexIds;
  std::vector<int> bridgeEdgeIds;
  FindArticulationPointsAndBridges(graph, articulationVertexIds, bridgeEdgeIds);

  int edgeConnectivity = 0;
  int vertexConnectivity = 0;

  if (IsConnected(graph) && graph.vertices.size() >= 2)
  {
    edgeConnectivity = ComputeEdgeConnectivity(graph);
    vertexConnectivity = ComputeVertexConnectivity(graph);
  }

  ScStructure result = FormResult(
      topology,
      vertexConnectivity,
      edgeConnectivity,
      articulationVertexIds,
      bridgeEdgeIds,
      graph);

  action.SetResult(result);
  return action.FinishSuccessfully();
}

bool AnalyzeNetworkResilienceAgent::BuildGraphFromTopology(ScAddr const & topology, Graph & graph, std::string & error) const
{
  error.clear();

  // 1) Collect vertices: topology -> vertex
  std::unordered_map<ScAddr, int, ScAddrHashFunc> indexOf;
  {
    ScIterator3Ptr it3 = m_context.CreateIterator3(topology, ScType::ConstPermPosArc, ScType::ConstNode);
    while (it3->Next())
    {
      ScAddr v = it3->Get(2);
      if (!v.IsValid())
        continue;
      if (indexOf.find(v) != indexOf.end())
        continue;
      int idx = (int)graph.vertices.size();
      indexOf.emplace(v, idx);
      graph.vertices.push_back(v);
    }
  }

  if (graph.vertices.empty())
  {
    error = "Topology has no vertices";
    return false;
  }

  std::unordered_set<ScAddr, ScAddrHashFunc> vertexSet;
  vertexSet.reserve(graph.vertices.size() * 2);
  for (auto const & v : graph.vertices)
    vertexSet.insert(v);

  // 2) Collect edges: from each vertex search common arcs marked by nrel_physical_connection
  std::unordered_set<ScAddr, ScAddrHashFunc> seenArcs;
  for (auto const & v : graph.vertices)
  {
    ScIterator5Ptr it5 = m_context.CreateIterator5(
        v,
        ScType::ConstCommonArc,
        ScType::ConstNode,
        ScType::ConstPermPosArc,
        NetworkResilienceKeynodes::nrel_physical_connection);

    while (it5->Next())
    {
      ScAddr arc = it5->Get(1);
      ScAddr to = it5->Get(2);
      if (!arc.IsValid() || !to.IsValid())
        continue;

      // Consider only edges between vertices of this topology
      if (vertexSet.find(to) == vertexSet.end())
        continue;

      if (seenArcs.find(arc) != seenArcs.end())
        continue;
      seenArcs.insert(arc);

      auto itU = indexOf.find(v);
      auto itV = indexOf.find(to);
      if (itU == indexOf.end() || itV == indexOf.end())
        continue;

      Edge e;
      e.u = itU->second;
      e.v = itV->second;
      e.arcAddr = arc;
      graph.edges.push_back(e);
    }
  }

  // 3) Build adjacency
  graph.adj.assign(graph.vertices.size(), {});
  for (int eid = 0; eid < (int)graph.edges.size(); ++eid)
  {
    auto const & e = graph.edges[eid];
    if (e.u == e.v)
      continue;
    graph.adj[e.u].push_back({e.v, eid});
    graph.adj[e.v].push_back({e.u, eid});
  }

  return true;
}

void AnalyzeNetworkResilienceAgent::FindArticulationPointsAndBridges(
    Graph const & graph,
    std::vector<int> & articulationVertexIds,
    std::vector<int> & bridgeEdgeIds) const
{
  int n = (int)graph.vertices.size();
  std::vector<int> tin(n, -1);
  std::vector<int> low(n, -1);
  std::vector<char> isArt(n, 0);
  int timer = 0;

  bridgeEdgeIds.clear();

  std::function<void(int, int)> dfs = [&](int v, int parentEdge)
  {
    tin[v] = low[v] = timer++;
    int children = 0;

    for (auto const & [to, eid] : graph.adj[v])
    {
      if (eid == parentEdge) continue;

      if (tin[to] != -1)
      {
        // back edge
        low[v] = std::min(low[v], tin[to]);
      }
      else
      {
        dfs(to, eid);
        low[v] = std::min(low[v], low[to]);

        if (low[to] > tin[v])
        {
          bridgeEdgeIds.push_back(eid);
        }

        if (low[to] >= tin[v] && parentEdge != -1)
        {
          isArt[v] = 1;
        }

        ++children;
      }
    }

    if (parentEdge == -1 && children > 1)
      isArt[v] = 1;
  };

  for (int v = 0; v < n; ++v)
  {
    if (tin[v] == -1)
      dfs(v, -1);
  }

  articulationVertexIds.clear();
  for (int v = 0; v < n; ++v)
    if (isArt[v]) articulationVertexIds.push_back(v);

  std::sort(bridgeEdgeIds.begin(), bridgeEdgeIds.end());
  bridgeEdgeIds.erase(std::unique(bridgeEdgeIds.begin(), bridgeEdgeIds.end()), bridgeEdgeIds.end());
}

int AnalyzeNetworkResilienceAgent::ComputeEdgeConnectivity(Graph const & graph) const
{
  int n = (int)graph.vertices.size();
  if (n <= 1) return 0;

  int best = std::numeric_limits<int>::max();

  // For undirected graphs: min s-t cut over all pairs with unit capacities.
  for (int s = 0; s < n; ++s)
  {
    for (int t = s + 1; t < n; ++t)
    {
      Dinic dinic(n);
      for (auto const & e : graph.edges)
      {
        if (e.u == e.v) continue;
        dinic.addEdge(e.u, e.v, 1);
        dinic.addEdge(e.v, e.u, 1);
      }

      int flow = dinic.maxflow(s, t, best);
      best = std::min(best, flow);
      if (best == 0) return 0;
      if (best == 1) return 1;
    }
  }

  if (best == std::numeric_limits<int>::max())
    return 0;
  return best;
}

int AnalyzeNetworkResilienceAgent::ComputeVertexConnectivity(Graph const & graph) const
{
  int n = (int)graph.vertices.size();
  if (n <= 1) return 0;

  int best = std::numeric_limits<int>::max();
  int const INF = 1000000000;

  // Menger theorem with node-splitting and max-flow
  // For each pair (s,t) compute max # of internally vertex-disjoint paths.
  for (int s = 0; s < n; ++s)
  {
    for (int t = s + 1; t < n; ++t)
    {
      int N = 2 * n;
      auto vin = [&](int v) { return 2 * v; };
      auto vout = [&](int v) { return 2 * v + 1; };

      Dinic dinic(N);

      for (int v = 0; v < n; ++v)
      {
        int cap = (v == s || v == t) ? INF : 1;
        dinic.addEdge(vin(v), vout(v), cap);
      }

      for (auto const & e : graph.edges)
      {
        if (e.u == e.v) continue;
        dinic.addEdge(vout(e.u), vin(e.v), INF);
        dinic.addEdge(vout(e.v), vin(e.u), INF);
      }

      int flow = dinic.maxflow(vout(s), vin(t), best);
      best = std::min(best, flow);

      if (best == 0) return 0;
      if (best == 1) return 1;
    }
  }

  if (best == std::numeric_limits<int>::max())
    return 0;
  return best;
}

ScStructure AnalyzeNetworkResilienceAgent::FormResult(
    ScAddr const & topology,
    int vertexConnectivity,
    int edgeConnectivity,
    std::vector<int> const & articulationVertexIds,
    std::vector<int> const & bridgeEdgeIds,
    Graph const & graph) const
{
  ScStructure result = m_context.GenerateStructure();
  result << topology;

  auto addNumberRelation = [&](ScAddr const & rel, int value)
  {
    ScAddr link = m_context.GenerateLink(ScType::ConstNodeLink);
    m_context.SetLinkContent(link, std::to_string(value));

    ScAddr commonArc = m_context.GenerateConnector(ScType::ConstCommonArc, topology, link);
    ScAddr attrArc = m_context.GenerateConnector(ScType::ConstPermPosArc, rel, commonArc);

    result << link << commonArc << attrArc;
  };

  addNumberRelation(NetworkResilienceKeynodes::nrel_vertex_connectivity, vertexConnectivity);
  addNumberRelation(NetworkResilienceKeynodes::nrel_edge_connectivity, edgeConnectivity);

  // Articulation points set
  ScAddr artSet = m_context.GenerateNode(ScType::ConstNode);
  {
    ScAddr commonArc = m_context.GenerateConnector(ScType::ConstCommonArc, topology, artSet);
    ScAddr attrArc = m_context.GenerateConnector(
        ScType::ConstPermPosArc, NetworkResilienceKeynodes::nrel_articulation_points, commonArc);
    result << artSet << commonArc << attrArc;

    for (int vid : articulationVertexIds)
    {
      if (vid < 0 || vid >= (int)graph.vertices.size()) continue;
      ScAddr vAddr = graph.vertices[vid];
      ScAddr mArc = m_context.GenerateConnector(ScType::ConstPermPosArc, artSet, vAddr);
      result << vAddr << mArc;
    }
  }

  // Bridges set
  ScAddr bridgeSet = m_context.GenerateNode(ScType::ConstNode);
  {
    ScAddr commonArc = m_context.GenerateConnector(ScType::ConstCommonArc, topology, bridgeSet);
    ScAddr attrArc = m_context.GenerateConnector(
        ScType::ConstPermPosArc, NetworkResilienceKeynodes::nrel_bridge_connections, commonArc);
    result << bridgeSet << commonArc << attrArc;

    for (int eid : bridgeEdgeIds)
    {
      if (eid < 0 || eid >= (int)graph.edges.size()) continue;
      ScAddr arcAddr = graph.edges[eid].arcAddr;
      if (!arcAddr.IsValid()) continue;
      ScAddr mArc = m_context.GenerateConnector(ScType::ConstPermPosArc, bridgeSet, arcAddr);
      result << arcAddr << mArc;
    }
  }

  return result;
}
