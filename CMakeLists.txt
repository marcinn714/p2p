cmake_minimum_required(VERSION 3.5)
project(tin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


add_executable(tin applicationLogic/main.cpp applicationLogic/Node/NodeInfo.cpp applicationLogic/Node/NodeInfo.h applicationLogic/commands/Command.hpp netCommunication/NetUtils.cpp netCommunication/NetUtils.h applicationLogic/threads/NetMainThread.cpp applicationLogic/threads/NetMainThread.h messages/InfoMessage.cpp messages/InfoMessage.h applicationLogic/threads/TcpMainService.cpp applicationLogic/threads/TcpMainService.h applicationLogic/files/ReceiveFileTcp.cpp applicationLogic/files/ReceiveFileTcp.h applicationLogic/files/AddFile.h applicationLogic/fileTables/FilesTableReceive.cpp applicationLogic/fileTables/FilesTableReceive.h applicationLogic/files/GetFile.cpp applicationLogic/files/GetFile.h applicationLogic/files/RemoveFile.cpp applicationLogic/files/RemoveFile.h applicationLogic/fileTables/ListFilesRequest.cpp applicationLogic/fileTables/ListFilesRequest.h applicationLogic/commands/Leave.cpp applicationLogic/commands/Leave.h applicationLogic/commands/PrintStats.cpp applicationLogic/commands/PrintStats.h applicationLogic/files/SendFileTcp.cpp applicationLogic/files/SendFileTcp.h applicationLogic/fileTables/FilesTableSend.cpp applicationLogic/fileTables/FilesTableSend.h netCommunication/TcpCommunication.cpp netCommunication/TcpCommunication.h netCommunication/UdpCommunication.cpp netCommunication/UdpCommunication.h applicationLogic/files/AddFile.cpp)

