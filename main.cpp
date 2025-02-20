#include <iostream>
#include "cmdParser.h"

int main(int argc, char* argv[]){

    //Value passed for if there is a error to quit the program
    cmdParser parser(true);

    //creates a argument that is  required  and has no subtype
    parser.addOption("-s", "this arg has no subtype", true,false);

    //Creates a argument is required and has no subtype
    parser.addOption("-help","provides a help message",false,false);

    //Creates a argument that is required and requires a subtype 
    parser.addOption("-cool","cools you out",true,true);

    //passses the arguments to the class they are now going to be indexed and values can now be retrived
    parser.passArguments(argc,argv);
   
    std::cout << parser.getArgument("-cool") << "\n";
    
    if(parser.doesArgExist("-help")){
        parser.displayHelpMessage();
    }

    return 0;
}