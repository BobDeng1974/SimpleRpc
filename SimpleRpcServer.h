#ifndef SIMPLE_RPC_SERVER_H
#define SIMPLE_RPC_SERVER_H

#include "nn.h"

#include "SimpleRpc.pb.h"

#include <string>
#include <unordered_map>

namespace srpc {

class SimpleRpcServer {
public:
  SimpleRpcServer();
  virtual ~SimpleRpcServer();

  int Bind(const char* url);

  void Start();

  void AddService(google::protobuf::Service* service);

  void RemoveAllServices();

  int Shutdown(int eid);

 private:
  nn::Socket socket;

  struct ServiceMeta {
    google::protobuf::Service* service;
    std::unordered_map< std::string, const google::protobuf::MethodDescriptor* > mds;
  };

  std::unordered_map< std::string, ServiceMeta* > services;
};

}  // namespace srpc

#endif  // SIMPLE_RPC_SERVER_H