cmake_minimum_required(VERSION 3.0)

project(SimpleRpc)

find_package(Protobuf REQUIRED)
find_package(nanomsg REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS SimpleRPC.proto)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)

set(RpcTools 
SimpleRpcChannel.cpp 
SimpleRpcChannel.h
SimpleRpcServer.cpp 
SimpleRpcServer.h 
SimpleRpcService.cpp 
SimpleRpcService.h 
nn.cpp 
nn.h 
utils.cpp 
utils.h 
)

set(client_name "${PROJECT_NAME}Client")
set(server_name "${PROJECT_NAME}Server")

if(MSVC)
    set(nanomsg_LIBS ${nanomsg_LIBDIR}/nanomsg.lib)
else()
	set(nanomsg_LIBS ${nanomsg_LIBDIR}/libnanomsg.so)
endif()

add_library(RPCLIB ${RpcTools} ${PROTO_SRCS} ${PROTO_HDRS})
target_compile_definitions(RPCLIB PUBLIC -DPROTOBUF_USE_DLLS)
target_include_directories(RPCLIB PUBLIC ${Protobuf_INCLUDE_DIRS} ${nanomsg_INCDIR} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(RPCLIB ${Protobuf_LIBRARIES} ${Protobuf_PROTOC_LIBRARIES} ${Protobuf_LITE_LIBRARIES} ${nanomsg_LIBS})

add_executable(${client_name} Client.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(${client_name} RPCLIB)

add_executable(${server_name} Server.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(${server_name} RPCLIB)