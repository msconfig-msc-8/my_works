#include "network_resilience_module.hpp"

#include "agent/AnalyzeNetworkResilienceAgent.hpp"

SC_MODULE_REGISTER(NetworkResilienceModule)
    ->Agent<AnalyzeNetworkResilienceAgent>();
