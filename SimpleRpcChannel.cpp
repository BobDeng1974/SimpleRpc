#include "SimpleRpcChannel.h"

#include "utils.h"

srpc::SimpleRpcChannel::SimpleRpcChannel(const char* url)
    : socket(AF_SP, NN_REQ) {
  eid = socket.Connect(url);
}

srpc::SimpleRpcChannel::~SimpleRpcChannel() { Shutdown(eid); }

void srpc::SimpleRpcChannel::CallMethod(
    const google::protobuf::MethodDescriptor* method,
    google::protobuf::RpcController* controller,
    const google::protobuf::Message* request,
    google::protobuf::Message* response, google::protobuf::Closure* done) {
  SimpleRPC::SimpleHead head;
  head.set_service(method->service()->name());
  head.set_method(method->name());

  int head_size = head.ByteSize();
  int msg_size = sizeof(head_size) + head_size + request->ByteSize();
  char* buf = static_cast< char* >(nn::AllocMsg(msg_size, 0));
  if (buf == nullptr) {
    // bad alloc
    return;
  }

  // copy head size
  int head_size_bigedian = srpc::ToBigEdian(head_size);
  memcpy(buf, &head_size_bigedian, sizeof(head_size));
  // copy head
  head.SerializeToArray(buf + sizeof(head_size), head.ByteSize());
  // copy request
  request->SerializeToArray(buf + sizeof(head_size) + head_size,
                            request->ByteSize());

  // send message
  socket.Send(buf, msg_size, 0);
  nn::FreeMsg(buf);

  // recv message
  int recv_size = socket.Recv(&buf, NN_MSG, 0);
  response->ParseFromArray(buf, recv_size);
  nn::FreeMsg(buf);
}

int srpc::SimpleRpcChannel::Shutdown(int _eid) { return socket.Shutdown(_eid); }