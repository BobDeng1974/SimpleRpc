#include "SimpleRpcChannel.h"

#include "SimpleRpc.pb.h"

#include <iostream>

#include "args.hxx"

int main(int argc, char* argv[]) {
  args::ArgumentParser parser("SimpleRpc argument");
  args::ValueFlag<std::string> addr(parser, "ip addr", "ip address", {'i'},
                                    "tcp://127.0.0.1:1234");
  parser.ParseCLI(argc, argv);
  std::string ip_addr = args::get(addr);

  srpc::SimpleRpcChannel channel(ip_addr.c_str());
  SimpleRpc::SimpleService_Stub stub(&channel);

  SimpleRpc::SimpleRequest request;
  request.set_request("My first request.");

  SimpleRpc::SimpleResponse response;
  stub.SimpleCall(nullptr, &request, &response, nullptr);
  std::cout << response.response() << std::endl;

  request.set_request("My second request.");
  stub.SimpleCall(nullptr, &request, &response, nullptr);
  std::cout << response.response() << std::endl;

  return 0;
}