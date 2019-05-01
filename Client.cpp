#include "SimpleRpcChannel.h"

#include "SimpleRPC.pb.h"

#include <iostream>

int main() {
  srpc::SimpleRpcChannel channel("tcp://127.0.0.1:1234");
  SimpleRPC::SimpleService_Stub stub(&channel);

  SimpleRPC::SimpleRequest request;
  request.set_request("My first request.");

  SimpleRPC::SimpleResponse response;
  stub.SimpleCall(nullptr, &request, &response, nullptr);
  std::cout << response.response() << std::endl;

  request.set_request("My second request.");
  stub.SimpleCall(nullptr, &request, &response, nullptr);
  std::cout << response.response() << std::endl;

  return 0;
}