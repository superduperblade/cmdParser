#include <iostream>
#include "cmdParser.h"
int main(int argc, char* argv[]){


    std::cout << __cplusplus ;

    cmdParser parser(true);

    parser.addOption("-help","provides a help message",true,true);
    parser.addOption("-cool","cools you out",true,true);
    parser.getNumberOfRequiredArguments();

    
    return 0;
}