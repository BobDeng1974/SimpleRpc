#include "utils.h"

bool srpc::IsBigEdian() {
  static const int endian = 1;
  static const bool ret = ((*(char *)&endian) == 0);
  return ret;
}

int srpc::ChangeEdian(int i) {
  int ret = 0;
  while (i != 0) {
    ret = (ret << 8) | (i & 0xff);
    i = i >> 8;
  }

  return ret;
}

int srpc::ToBigEdian(int i) {
  if (IsBigEdian()) {
    return i;
  } else {
    return ChangeEdian(i);
  }
}

int srpc::FromBigEdian(int i) {
  if (IsBigEdian()) {
    return i;
  } else {
    return ChangeEdian(i);
  }
}