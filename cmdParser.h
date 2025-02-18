#include <map>
#include <string>
#include <any>
#include <vector>
#include <iostream>
#include <format>
using namespace std;

class cmdParser
{
    struct argument{
        string identifier = "";
        string helpMessage = "";
        bool required = false;
        bool subtype = true;
        argument(string identifierArg,string helpMessageArg,bool requiredArg,bool subtypeArg):identifier(identifierArg),helpMessage(helpMessageArg),required(requiredArg),subtype(subtypeArg){}
        argument(string identifierArg,string helpMessageArg,bool requiredArg):identifier(identifierArg),helpMessage(helpMessageArg),required(requiredArg){}
        argument(string identifierArg,string helpMessageArg):identifier(identifierArg),helpMessage(helpMessageArg){}
        argument() = default;
    };
private:
    /* data */
    std::vector<argument> arguments;
    std::map<string,string> userArgument_values;
    bool exit_On_Fail;
    int numberOfArgs;
    char* argv[];
public:

    cmdParser(bool exit_If_Failed){
        this->exit_On_Fail = exit_If_Failed;
    }


    //You MUST have defined all your options before doing this!
    bool passArguments(int numberOfArgs,char* argv[]){
        if(getNumberOfRequiredArguments()> numberOfArgs){
            error("All of the required arguments where not put!");
            return false;
        }
        for(int i = i; i < numberOfArgs;i++){
            string u_arg = argv[i];
            for (argument arg: arguments){
                if(arg.identifier == u_arg ){
                    if (arg.subtype){
                        if( i +1 != numberOfArgs ){
                            this->userArgument_values[arg.identifier] =  argv[i+1];
                           
                        //skips the next provided argument as thats the value the user put
                            i++;
                        }else {
                            error("No value provided next to argument: "+arg.subtype);
                            return false;
                        }
                    }else{
                        //just puts the identifier itself
                        userArgument_values[arg.identifier] = argv[i];
                    }
                }else{
                    error("Invalid arguement provided: "+u_arg +"\n");
                    return false;
                }
            }
        }
        return true;
    }

    void addOption(string identifier,string helpMessage, bool required,bool subtype){
        arguments.push_back(argument(identifier,helpMessage,required,subtype));
    }
    void addOption(string identifier,string helpMessage, bool required){
        arguments.push_back(argument(identifier,helpMessage,required));
    }
    void addOption(string identifier,string helpMessage){
        arguments.push_back(argument(identifier,helpMessage));
    }

    string getArgument(std::string identifier){
        return userArgument_values[identifier];
    }
    map<string ,string> getArguments(){
        return  this->userArgument_values;
    }

    void error(){
        cerr << this->displayHelpMessage();
        if(exit){
            cout << "Exiting \n";
            exit(-1);
        }
    }

    void error(string message){
        cerr <<"Encountered error: "<< message << '\n';
        cerr << this->displayHelpMessage();
        if(exit){
            cout << "Exiting \n";
            exit(-1);
        }
    }

//displays the contents of the arguments passed into this libary 
    string displayHelpMessage(){
        string helpMessage = "This program uses the following command line arguments: \n";
        for (argument arg : arguments){
            helpMessage += std::format("Identifier: {} , Help: {}, Required: {} \n",arg.identifier,arg.helpMessage,arg.required);      
        }
        return helpMessage;
    }

    int getNumberOfRequiredArguments(){
        int counter = 0;
        for (argument arg: arguments ){
            if(arg.required) counter++;
        }
        return counter;
    }

};