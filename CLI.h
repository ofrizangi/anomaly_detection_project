//Ofri Zangi 207488305
//Ben Plosk 208290833

#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
    DefaultIO* dio;
    Command ** commands = nullptr;
    int size = 0;
//    CommandArrayMediator mediator;
public:
    CLI(DefaultIO* dio);
    void start();
    void printMenu();
    virtual ~CLI();
};

#endif /* CLI_H_ */
