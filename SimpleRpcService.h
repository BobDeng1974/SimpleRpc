#ifndef SIMPLE_RPC_SERVICE_H
#define SIMPLE_RPC_SERVICE_H

#include "SimpleRPC.pb.h"

namespace srpc {

class SimpleRpcServiceImpl : public SimpleRPC::SimpleService {
 public:
  virtual void SimpleCall(google::protobuf::RpcController* controller,
                          const SimpleRPC::SimpleRequest* request,
                          SimpleRPC::SimpleResponse* response,
                          google::protobuf::Closure* done) override;
};
}  // namespace srpc

#endif  // SIMPLE_RPC_SERVICE_H