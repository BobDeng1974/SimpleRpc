#include "SimpleRpcServer.h"

#include "utils.h"

srpc::SimpleRpcServer::SimpleRpcServer()
    : socket(AF_SP, NN_REP) {
}

srpc::SimpleRpcServer::~SimpleRpcServer() {
  RemoveAllServices();
}

int srpc::SimpleRpcServer::Bind(const char* url) { return socket.Bind(url); }

void srpc::SimpleRpcServer::Start() {
  while (true) {
    char* buf = nullptr;
    int bytes = socket.Recv(&buf, NN_MSG, 0);
    if (bytes <= 0) {
      continue;
    }

    // head size
    int head_size_bigedian = 0;
    memcpy(&head_size_bigedian, buf, sizeof(head_size_bigedian));
    int head_size = srpc::FromBigEdian(head_size_bigedian);

    // head
    SimpleRPC::SimpleHead head;
    head.ParseFromArray(buf + sizeof(head_size), head_size);

    // get meta
    auto iter_service = services.find(head.service());
    if (iter_service == services.end()) {
      continue;
    }
    ServiceMeta* meta = iter_service->second;
    
    // get service
    google::protobuf::Service* service = meta->service;
    
    // get method
    auto iter_method = meta->mds.find(head.method());
    if (iter_method == meta->mds.end()) {
      continue;
    }
    const google::protobuf::MethodDescriptor* method = iter_method->second;

    // create request and response
    google::protobuf::Message* request =
        service->GetRequestPrototype(method).New();
    google::protobuf::Message* response =
        service->GetResponsePrototype(method).New();

    // get request
    int request_start = sizeof(head_size) + head_size;
    request->ParseFromArray(buf + request_start, bytes - request_start + 1);
    nn::FreeMsg(buf);

    // call method
    service->CallMethod(method, nullptr, request, response, nullptr);

    // send response
    int response_size = response->ByteSize();
    buf = static_cast< char* >(nn::AllocMsg(response_size, 0));
    response->SerializeToArray(buf, response_size);
    socket.Send(buf, response_size, 0);

    // release buffer
    nn::FreeMsg(buf);
    delete request;
    delete response;
  }
}

void srpc::SimpleRpcServer::AddService(google::protobuf::Service* service) {
  const google::protobuf::ServiceDescriptor* descriptor =
      service->GetDescriptor();
  if (services.find(descriptor->name()) == services.end()) {
    ServiceMeta* meta = new ServiceMeta;
    meta->service = service;

    for (int i = 0; i < descriptor->method_count(); ++i) {
      const google::protobuf::MethodDescriptor* method = descriptor->method(i);
      if (meta->mds.find(method->name()) == meta->mds.end()) {
        meta->mds[method->name()] = method;
      }
    }

    services[descriptor->name()] = meta;
  }
}

void srpc::SimpleRpcServer::RemoveAllServices() {
  for (const auto& iter : services) {
    ServiceMeta* meta = iter.second;
    delete meta;
  }
}

int srpc::SimpleRpcServer::Shutdown(int eid) { return socket.Shutdown(eid); }