#include "SimpleRpcService.h"
#include "SimpleRpcServer.h"

int main() {
  srpc::SimpleRpcServer server("tcp://127.0.0.1:1234");
  google::protobuf::Service* service = new srpc::SimpleRpcServiceImpl();
  server.AddService(service);
  server.Start();

  return 0;
}