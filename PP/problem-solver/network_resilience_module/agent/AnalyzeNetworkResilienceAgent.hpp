#pragma once

#include <sc-memory/sc_agent.hpp>

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class AnalyzeNetworkResilienceAgent : public ScActionInitiatedAgent
{
public:
  AnalyzeNetworkResilienceAgent();

  ScAddr GetActionClass() const override;
  ScResult DoProgram(ScAction & action) override;

  // Эти структуры сделаны public, потому что в .cpp есть helper-функции
  // (например IsConnected), которые принимают Graph по ссылке.
  // Иначе сборка падает с ошибкой "Graph is private within this context".
  struct Edge
  {
    int u;
    int v;
    ScAddr arcAddr;  // sc-common-arc representing physical connection
  };

  struct Graph
  {
    std::vector<ScAddr> vertices;
    std::vector<Edge> edges;
    std::vector<std::vector<std::pair<int, int>>> adj; // (to, edgeId)
  };

private:
  bool BuildGraphFromTopology(ScAddr const & topology, Graph & graph, std::string & error) const;

  void FindArticulationPointsAndBridges(
      Graph const & graph,
      std::vector<int> & articulationVertexIds,
      std::vector<int> & bridgeEdgeIds) const;

  int ComputeEdgeConnectivity(Graph const & graph) const;
  int ComputeVertexConnectivity(Graph const & graph) const;

  ScStructure FormResult(
      ScAddr const & topology,
      int vertexConnectivity,
      int edgeConnectivity,
      std::vector<int> const & articulationVertexIds,
      std::vector<int> const & bridgeEdgeIds,
      Graph const & graph) const;
};
