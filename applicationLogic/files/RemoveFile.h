//
// Created by marcin on 18.05.18.
//

#ifndef TIN_REMOVEFILE_H
#define TIN_REMOVEFILE_H


#include "../commands/Command.hpp"

class RemoveFile: public Command {
private:
    std::string fileName;
public:
    RemoveFile(std::string _fileName): fileName(_fileName) {}
    virtual ~RemoveFile() = default;

    void execute();
    bool reqSeparateThread() {return false;}
};


#endif //TIN_REMOVEFILE_H
