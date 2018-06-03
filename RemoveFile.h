//
// Created by marcin on 18.05.18.
//

#ifndef TIN_REMOVEFILE_H
#define TIN_REMOVEFILE_H


#include "Command.hpp"

class RemoveFile: public Command {
private:
    std::string param;
public:
    RemoveFile(std::string _param): param(_param) {}
    virtual ~RemoveFile() = default;

    void execute(void);
    bool reqSeparateThread(void) {return false;}
};


#endif //TIN_REMOVEFILE_H
