//
// Created by marcin on 15.05.18.
//

#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>

class Command
{
public:
    Command() {}
    virtual ~Command()	{}

    virtual void execute(void) = 0;
    virtual bool reqSeparateThread(void) = 0;


    static void * commandExeWrapper(void * command)
    {
        Command * cmd = static_cast<Command *>(command);
        cmd->execute();
        delete cmd;
        return 0;
    }

    static void exitCommand(Command * cmd)
    {
        delete cmd;
        pthread_exit((void*)nullptr);
    }
};

#endif /* COMMAND_H_ */
