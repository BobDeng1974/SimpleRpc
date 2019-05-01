#ifndef SIMPLE_RPC_CHANNEL_H
#define SIMPLE_RPC_CHANNEL_H

#include "nn.h"

#include "SimpleRPC.pb.h"

namespace srpc {

class SimpleRpcChannel : public google::protobuf::RpcChannel {
 public:
  SimpleRpcChannel(const char* url);
  virtual ~SimpleRpcChannel();

  virtual void CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller,
                          const google::protobuf::Message* request,
                          google::protobuf::Message* response,
                          google::protobuf::Closure* done) override;
  int Close();

private:
  int socket_id;
  nn::Socket socket;
};

}  // namespace srpc

#endif  // SIMPLE_RPC_CHANNEL_H