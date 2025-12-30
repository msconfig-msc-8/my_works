#pragma once

#include <sc-memory/sc_keynodes.hpp>

class NetworkResilienceKeynodes : public ScKeynodes
{
public:
  // Action classes
  static inline ScKeynode const action_analyze_network_resilience{
      "action_analyze_network_resilience", ScType::ConstNodeClass};

  // Non-role relations describing topology and analysis results
  static inline ScKeynode const nrel_physical_connection{
      "nrel_physical_connection", ScType::ConstNodeNonRole};

  static inline ScKeynode const nrel_vertex_connectivity{
      "nrel_vertex_connectivity", ScType::ConstNodeNonRole};

  static inline ScKeynode const nrel_edge_connectivity{
      "nrel_edge_connectivity", ScType::ConstNodeNonRole};

  static inline ScKeynode const nrel_articulation_points{
      "nrel_articulation_points", ScType::ConstNodeNonRole};

  static inline ScKeynode const nrel_bridge_connections{
      "nrel_bridge_connections", ScType::ConstNodeNonRole};
};
