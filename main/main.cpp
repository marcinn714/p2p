#include <stdio.h>
#include <stdlib.h>
#include "../applicationLogic/commands/Command.hpp"
#include "../applicationLogic/threads/NetMainThread.h"
#include "../applicationLogic/files/AddFile.hpp"
#include "../applicationLogic/files/GetFile.h"
#include "../applicationLogic/files/RemoveFile.h"
#include "../applicationLogic/fileTables/ListFilesRequest.h"
#include "../applicationLogic/commands/Leave.h"
#include "../applicationLogic/commands/PrintStats.h"


std::string availableCommands = "Type:\n\
\tjoin\t to join or build P2P network\n\
\tadd\t <filename> to add file to P2P network\n\
\tget\t <hash> to get file from P2P network\n\
\tremove\t <hash> to remove file from P2P network\n\
\tlist\t to get list of all available files in P2P network\n\
\tstat\t to get information about current P2P network\n\
\tinfo\t to get available commands\n\
\tleave\t to leave from P2P network\n\
\texit\t to force leaving from P2P network\n";

Command * newTerminalCommand(std::string textCommand)
{
    Command * outCommand;
    std::string comm, param;
    std::stringstream ss(textCommand);
    ss >> comm >> param;
    if(comm == "add")
        outCommand = new AddFile(param);
    else if(comm == "get")
        outCommand = new GetFile(param);
    else if(comm == "remove")
        outCommand = new RemoveFile(param);
    else if(textCommand == "join")
        outCommand = new NetMainThread();
    else if(textCommand == "list")
        outCommand = new ListFilesRequest();
    else if (textCommand == "leave")
        outCommand = new Leave();
    else if(textCommand == "stat")
        outCommand = new PrintStats();
    else if(textCommand == "info") {
        std::cout << availableCommands;
        outCommand = nullptr;
    }
    else if (textCommand == "exit")
        exit(0);
    else {
        std::cout << "Type 'info' to see available commands" << std::endl;
        outCommand = nullptr;
    }
    return outCommand;
}


int main(void)
{
    std::string userCommand;
    pthread_t thread, netThread;
    std::cout << availableCommands << std::endl;
    // Get user commands from terminal
    while(1)
    {
        std::string userCommand;
        std::cout << "> ";
        getline(std::cin, userCommand);
        Command * command = newTerminalCommand(userCommand);
        if(command != nullptr)
        {
            if(command->reqSeparateThread())
            {
                if (userCommand == "join" && NetMainThread::getNodeInfo() == nullptr)
                    pthread_create(&netThread, NULL, Command::commandExeWrapper, static_cast<void *>(command));
                else {
                    pthread_create(&thread, NULL, Command::commandExeWrapper, static_cast<void *>(command));
                    pthread_detach(thread);
                }
            }
            else
            {
                command->execute();
                delete command;
                if (userCommand == "leave") {
                    std::cout << "Leaving from network... ";
                    if (NetMainThread::getNodeInfo() != nullptr)
                        pthread_join(netThread, NULL);
                    std::cout << "Completed" << std::endl;
                    return 0;
                }
            }
        }
    }

    return 0;
}