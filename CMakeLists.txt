cmake_minimum_required(VERSION 3.5)
project(tin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(tin main.cpp NodeInfo.cpp NodeInfo.h Command.hpp netCommunication/NetUtils.cpp netCommunication/NetUtils.h NetMainThread.cpp NetMainThread.h messages/MessageFrames.cpp messages/MessageFrames.h TcpMainService.cpp TcpMainService.h ReceiveFileTcp.cpp ReceiveFileTcp.h AddFile.hpp FilesTableReceive.cpp FilesTableReceive.h GetFile.cpp GetFile.h RemoveFile.cpp RemoveFile.h ListFilesRequest.cpp ListFilesRequest.h Leave.cpp Leave.h PrintStats.cpp PrintStats.h SendFileTcp.cpp SendFileTcp.h FilesTableSend.cpp FilesTableSend.h netCommunication/TcpCommunication.cpp netCommunication/TcpCommunication.h netCommunication/UdpCommunication.cpp netCommunication/UdpCommunication.h)