#pragma once

#include <cctype>
#include <string>
#include "Token.h"


class Scanner {
    private:
        std::string input;
        int line;
    public:
        Scanner(const std::string& input) : input(input), line(1) { }

         Token scanToken() {         
            /*TokenType type = COMMA;
            std::string value = " ,";
            int line = 4;*/

            //remove white space
                //use .isspace
            while (isspace(input.at(0))){
                input = input.substr(1); //this returns a string with the first character removed.
            }
            

            if (input.at(0) == ','){
                input = input.substr(1);
                return Token(COMMA, ",", line);
            } else if (){//UNFINISHED, see lab1 part 3 on how to complete it:
                
            } else if () {
                
            }

                '''
                    Add scanning of other token types to 'scanToken' (Scanner.h)
Use separate functions for STRING, COMMENT, ID, etc.
Design these functions using state machines.

Add code to keep track of line numbers, so each Token is created with the correct line number.

Add reading from a file into the input string in the main function (main.cpp)
                ''' 
            
  }
};