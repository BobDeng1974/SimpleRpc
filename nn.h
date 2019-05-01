#ifndef SIMPLE_RPC_NN_H
#define SIMPLE_RPC_NN_H

#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

namespace nn {

class Socket {
 public:
  Socket(int domain, int protocol);

  Socket(const Socket&) = delete;
  Socket& operator=(const Socket&) = delete;

  ~Socket();

  int SetSocketOpt(int level, int option, const void* optval, size_t optvallen);

  int GetSocketOpt(int level, int option, void* optval, size_t* optvallen);

  int Bind(const char* addr);

  int Connect(const char* addr);

  int Shutdown(int how);

  int Send(const void* buf, size_t len, int flags);

  int Recv(void* buf, size_t len, int flags);

  int SendMsg(const nn_msghdr* msghdr, int flags);

  int RecvMsg(nn_msghdr* msghdr, int flags);

 private:
  int socket_id;
};

void* AllocMsg(size_t size, int type);

void* ReallocMsg(void* msg, size_t size);

int FreeMsg(void* msg);

const char* Symbol(int i, int* value);

int Errno();

}  // namespace nn

#endif  // SIMPLE_RPC_NN_H