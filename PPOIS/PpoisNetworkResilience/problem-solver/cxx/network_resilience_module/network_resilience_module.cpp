#include "network_resilience_module.hpp"
#include "agents/vertex_connectivity_agent.hpp"
#include "agents/articulation_points_agent.hpp"
#include "agents/bridges_agent.hpp"
#include "keynodes/resilience_keynodes.hpp"

SC_MODULE_REGISTER(NetworkResilienceModule)
    ->Agent<VertexConnectivityAgent>()
    ->Agent<ArticulationPointsAgent>()
    ->Agent<BridgesAgent>();
