#include "SimpleRpcServer.h"
#include "SimpleRpcService.h"

#include "args.hxx"

int main(int argc, char* argv[]) {
  args::ArgumentParser parser("SimpleRpc argument");
  args::ValueFlagList<std::string> addrs(parser, "ip addrs", "ip addresses",
                                         {'i'}, {"tcp://*:1234"});
  parser.ParseCLI(argc, argv);

  srpc::SimpleRpcServer server;

  for (const std::string ip_addr : args::get(addrs)) {
    server.Bind(ip_addr.c_str());
  }

  google::protobuf::Service* service = new srpc::SimpleRpcServiceImpl();
  server.AddService(service);
  server.Start();

  return 0;
}