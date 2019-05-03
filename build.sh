#!/bin/sh
mkdir build
cd build
rm -rf *

cmake -DProtobuf_INCLUDE_DIRS=/usr/local/include -DProtobuf_LIBRARIES=/usr/local/lib/libprotobuf.a -DProtobuf_PROTOC_LIBRARIES=/usr/local/lib/libprotoc.a -DProtobuf_LITE_LIBRARIES=/usr/local/lib/libprotobuf-lite.a ..
cmake --build .
