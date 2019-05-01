#ifndef SIMPLE_RPC_UTILS_H
#define SIMPLE_RPC_UTILS_H

namespace srpc {

bool IsBigEdian();
int ChangeEdian(int i);
int ToBigEdian(int i);
int FromBigEdian(int i);

}  // namespace srpc

#endif  // SIMPLE_RPC_UTILS_H