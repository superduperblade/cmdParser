#include <iostream>
#include "cmdParser.h"
int main(int argc, char* argv[]){


    

    cmdParser parser(true);

    parser.addOption("-help","provides a help message",true,true);
    parser.addOption("-cool","cools you out",true,true);
    parser.getNumberOfRequiredArguments();
    parser.passArguments(argc,argv);
    
    return 0;
}