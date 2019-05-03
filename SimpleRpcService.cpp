#include "SimpleRpcService.h"

#include <iostream>
#include <string>

void srpc::SimpleRpcServiceImpl::SimpleCall(
    google::protobuf::RpcController* controller,
    const SimpleRpc::SimpleRequest* request,
    SimpleRpc::SimpleResponse* response, 
    google::protobuf::Closure* done) {
  // get request
  std::string req = request->request();
  std::cout << "Received request: " << req << std::endl;

  // set response
  std::string res = std::string("Response: ") + req;
  response->set_response(res);

  if (done) {
    done->Run();
  }
}