// ex-plugin.cc

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"

namespace ns3 {

int
main(int argc, char* argv[])
{
    CommandLine cmd;
    cmd.Parse(argc, argv);

    AnnotatedTopologyReader topologyReader("", 25);
    //topologyReader.SetFileName("~/ndnSIM/ns-3/scrtch/top.txt");
    topologyReader.SetFileName("src/ndnSIM/examples/topologies/topo-grid-3x3.txt");
    topologyReader.Read();

    ndn::StackHelper ndnHelper;
    ndnHelper.InstallAll();

    ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
    ndnGlobalRoutingHelper.InstallAll();

    Ptr<Node> producer = Names::Find<Node>("Node8");
    NodeContainer consumerNodes;
    consumerNodes.Add(Names::Find<Node>("Node0"));

    std::string prefix = "/prefix";

    ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
    consumerHelper.SetPrefix(prefix);
    consumerHelper.SetAttribute("Frequency", StringValue("100"));
    consumerHelper.Install(consumerNodes);

    ndn::AppHelper producerHelper("ns3::ndn::Producer");
    producerHelper.SetPrefix(prefix);
    producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
    producerHelper.Install(producer);

    ndnGlobalRoutingHelper.AddOrigins(prefix, producer);

    ndn::GlobalRoutingHelper::CalculateRoutes();

    Simulator::Stop(Seconds(20.0));

    Simulator::Run();

    Simulator::Destroy();

    return 0;
   
}
}  // namespace ns3

int
main(int argc, char* argv[])
{
    return ns3::main(argc, argv);
}
