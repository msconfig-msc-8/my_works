#pragma once

#include <sc-memory/sc_keynodes.hpp>

class ResilienceKeynodes : public ScKeynodes
{
public:
  static inline ScKeynode const action_find_vertex_connectivity{
      "action_find_vertex_connectivity",
      ScType::ConstNodeClass};

  static inline ScKeynode const action_find_articulation_points{
      "action_find_articulation_points",
      ScType::ConstNodeClass};

  static inline ScKeynode const action_find_bridges{"action_find_bridges", ScType::ConstNodeClass};

  static inline ScKeynode const nrel_connected_to{"nrel_connected_to", ScType::ConstNodeNonRole};

  static inline ScKeynode const concept_device{"concept_device", ScType::ConstNodeClass};

  static inline ScKeynode const concept_server{"concept_server", ScType::ConstNodeClass};

  static inline ScKeynode const concept_workstation{"concept_workstation", ScType::ConstNodeClass};

  static inline ScKeynode const concept_switch{"concept_switch", ScType::ConstNodeClass};

  static inline ScKeynode const concept_router{"concept_router", ScType::ConstNodeClass};

  static inline ScKeynode const concept_gateway{"concept_gateway", ScType::ConstNodeClass};
};
