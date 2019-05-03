#ifndef SIMPLE_RPC_SERVICE_H
#define SIMPLE_RPC_SERVICE_H

#include "SimpleRpc.pb.h"

namespace srpc {

class SimpleRpcServiceImpl : public SimpleRpc::SimpleService {
 public:
  virtual void SimpleCall(google::protobuf::RpcController* controller,
                          const SimpleRpc::SimpleRequest* request,
                          SimpleRpc::SimpleResponse* response,
                          google::protobuf::Closure* done) override;
};
}  // namespace srpc

#endif  // SIMPLE_RPC_SERVICE_H