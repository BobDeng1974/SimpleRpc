#include "nn.h"

#include <cassert>

nn::Socket::Socket(int domain, int protocol) {
  socket_id = nn_socket(domain, protocol);
  assert(socket_id >= 0);
}

nn::Socket::~Socket() {
  int rc = nn_close(socket_id);
  assert(rc == 0);
}

int nn::Socket::SetSocketOpt(int level, int option, const void* optval,
                             size_t optvallen) {
  return nn_setsockopt(socket_id, level, option, optval, optvallen);
}

int nn::Socket::GetSocketOpt(int level, int option, void* optval,
                             size_t* optvallen) {
  return nn_getsockopt(socket_id, level, option, optval, optvallen);
}

int nn::Socket::Bind(const char* addr) { return nn_bind(socket_id, addr); }

int nn::Socket::Connect(const char* addr) {
  return nn_connect(socket_id, addr);
}

int nn::Socket::Shutdown(int how) { return nn_shutdown(socket_id, how); }

int nn::Socket::Send(const void* buf, size_t len, int flags) {
  return nn_send(socket_id, buf, len, flags);
}

int nn::Socket::Recv(void* buf, size_t len, int flags) {
  return nn_recv(socket_id, buf, len, flags);
}

int nn::Socket::SendMsg(const nn_msghdr* msghdr, int flags) {
  return nn_sendmsg(socket_id, msghdr, flags);
}

int nn::Socket::RecvMsg(nn_msghdr* msghdr, int flags) {
  return nn_recvmsg(socket_id, msghdr, flags);
}

void* nn::AllocMsg(size_t size, int type) { return nn_allocmsg(size, type); }

void* nn::ReallocMsg(void* msg, size_t size) {
  return nn_reallocmsg(msg, size);
}

int nn::FreeMsg(void* msg) { return nn_freemsg(msg); }

const char* nn::Symbol(int i, int* value) { return nn_symbol(i, value); }

int nn::Errno() { return nn_errno(); }