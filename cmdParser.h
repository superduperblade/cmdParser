#pragma once
#include <map>
#include <string>
#include <any>
#include <vector>
#include <iostream>
#include <format>

using namespace std;


enum IS_REQUIRED {
    ARG_REQUIRED = 1,
    ARG_OPTIONAL = 0,

};
enum IS_SUBTYPE {
    NEEDS_SUBTYPE = 1,
    SINGULAR_ARG = 0
};

class cmdParser
{
   
    struct argument {
        string identifier = "";
        string helpMessage = "";
        bool required = false;
        bool subtype = true;
        string defaultValue = "";
        argument(string identifierArg, string helpMessageArg, IS_REQUIRED requiredArg, IS_SUBTYPE subtypeArg) :identifier(identifierArg), helpMessage(helpMessageArg), required(requiredArg), subtype(subtypeArg) {}
        argument(string identifierArg, string helpMessageArg, IS_REQUIRED requiredArg) :identifier(identifierArg), helpMessage(helpMessageArg), required(requiredArg) {}
        argument(string identifierArg, string helpMessageArg) :identifier(identifierArg), helpMessage(helpMessageArg) {}
        
        argument(string identifierArg, string helpMessageArg, IS_REQUIRED requiredArg, IS_SUBTYPE subtypeArg, string defualtValue) :identifier(identifierArg), helpMessage(helpMessageArg), required(requiredArg), subtype(subtypeArg), defaultValue(defualtValue) {}
        argument(string identifierArg, string helpMessageArg, IS_REQUIRED requiredArg,string defualtValue) :identifier(identifierArg), helpMessage(helpMessageArg), required(requiredArg), defaultValue(defualtValue) {}
        argument(string identifierArg, string helpMessageArg,string defualtValue) :identifier(identifierArg), helpMessage(helpMessageArg) ,defaultValue(defualtValue) {}
        
        
        argument() = default;
    };
private:
    /* data */
    std::vector<argument> arguments;
    std::map<string, string> userArgument_values;
    bool exit_On_Fail;
    int numberOfArgs;
    char* argv[];
public:

    cmdParser(bool exit_If_Failed) {
        this->exit_On_Fail = exit_If_Failed;
    }


    //You MUST have defined all your options before doing this!
    bool passArguments(int numberOfArgs, char* argv[]) {

        int numberOfRequiredArgs = getNumberOfRequiredArguments();

        if (numberOfRequiredArgs > numberOfArgs - 1) {
            error("All of the required arguments where not put!");
            return false;
        }
      
        //starts at 1 instead of position 0 as the first argument is the executable
        for (int i = 1; i < numberOfArgs; i++) {
            string u_arg = argv[i];
            bool was_found = false;


            for (argument arg : arguments) {
                if (arg.identifier == u_arg) {
                    if (arg.subtype) {
                        if (i + 1 != numberOfArgs) {
                            this->userArgument_values[arg.identifier] = argv[i + 1];

                            //skips the next provided argument as thats the value the user put
                            i++;
                            was_found = true;
                        }
                        else {
                            error("No value provided next to argument: " + arg.subtype);
                            return false;
                        }
                    }
                    else {
                        //just puts the identifier itself
                        userArgument_values[arg.identifier] = argv[i];
                        was_found = true;
                    }
                }

            }

            if (!was_found) {
                error("No argument was found for: " + u_arg);
            }
        }
        return false;
    }

    void addOption(string identifier, string helpMessage, IS_REQUIRED required, IS_SUBTYPE subtype) {
        arguments.push_back(argument(identifier, helpMessage, required, subtype));
    }
    void addOption(string identifier, string helpMessage, IS_REQUIRED required) {
        arguments.push_back(argument(identifier, helpMessage, required));
    }
    void addOption(string identifier, string helpMessage) {
        arguments.push_back(argument(identifier, helpMessage));
    }

    string getArgument(std::string identifier) {
        return userArgument_values[identifier];
    }
    map<string, string> getArguments() {
        return  this->userArgument_values;
    }

    void error() {
        cerr << this->getHelpMessage();
        if (exit) {
            cout << "Exiting \n";
            exit(-1);
        }
    }

    void error(string message) {
        cerr << "Encountered error: " << message << '\n';
        cerr << this->getHelpMessage();
        if (exit) {
            cout << "Exiting \n";
            exit(-1);
        }
    }
    //Only use this if userarguments have been inputed to the class
    void giveArgDefualts() {
        for (argument arg : arguments) {
              if (userArgument_values.count(arg.identifier)) {
                  if (arg.defaultValue != "") {
                      if (userArgument_values[arg.identifier] == "") {
                          userArgument_values[arg.identifier] = arg.defaultValue;
                     }
                  }
             }
            
        }
    }


    //displays the contents of the arguments passed into this libary 
    string getHelpMessage() {
        string helpMessage = "This program uses the following command line arguments: \n";
        for (argument arg : arguments) {
            helpMessage += std::format("Identifier: {} , Required: {}, Help: {} \n", arg.identifier, arg.required, arg.helpMessage);
        }
        return helpMessage;
    }

    void displayHelpMessage() {
        cout << getHelpMessage();
    }

    int getNumberOfRequiredArguments() {
        int counter = 0;
        for (argument arg : arguments) {
            if (arg.required) counter++;
        }
        return counter;
    }

    bool doesArgExist(string identifier) {
        for (argument arg : arguments) {
            if (arg.identifier == identifier) {
                return true;
            }
        }
        return false;
    }

};