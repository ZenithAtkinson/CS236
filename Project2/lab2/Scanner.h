#pragma once
#include <iostream> //debugging out only
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
            while (!input.empty() && std::isspace(input.front())) {
                //std::cout << "test" << input << std::endl;
            if (input.front() == '\n') {
                line++;
                //input = input.substr(1); //this returns a string with the first character removed. HOLY CRAP THIS CAUSED ME SO MANY PROBLEMS BUT I FOUND IT FINALLY
            }
            input.erase(0, 1);
            }

            if (input.empty()) {
                return Token(EOFILE, "", line);
            }

            if (input.at(0) == ','){
                input = input.substr(1);
                return Token(COMMA, ",", line);
            } else if (input.at(0) == '.'){             
                input = input.substr(1);
                return Token(PERIOD, ".", line);
            } else if (input.at(0) == '?') {
                input = input.substr(1);
                return Token(Q_MARK, "?", line);
            } else if (input.at(0) == '(') {
                input = input.substr(1);
                return Token(LEFT_PAREN, "(", line);
            } else if (input.at(0) == ')') {
                input = input.substr(1);
                return Token(RIGHT_PAREN, ")", line);
            } else if (input.at(0) == ':') {
                // Check for COLON_DASH
                if (input.size() > 1 && input.at(1) == '-') {
                    input = input.substr(2);
                    return Token(COLON_DASH, ":-", line);
                } else {
                    input = input.substr(1);
                    return Token(COLON, ":", line);
                }
            } else if (input.at(0) == '*') {
                input = input.substr(1);
                return Token(MULTIPLY, "*", line);
            } else if (input.at(0) == '+') {
                input = input.substr(1);
                return Token(ADD, "+", line);
            } else if (isalpha(input.at(0))) {
            //ID identifier
                size_t pos = 1;
                //while letter or digit...
                while (pos < input.length() && (isalpha(input.at(pos)) || isdigit(input.at(pos)))) {
                    pos++;
                }

                std::string idValue = input.substr(0, pos);//?
                input = input.substr(pos); 
                
                if (idValue == "Schemes") {
                    return Token(SCHEMES, idValue, line);
                } else if (idValue == "Facts") {
                    return Token(FACTS, idValue, line);
                } else if (idValue == "Rules") {
                    return Token(RULES, idValue, line);
                } else if (idValue == "Queries") {
                    return Token(QUERIES, idValue, line);
                } else {
                    return Token(ID, idValue, line);
                }
            //FOR STRINGS
            } else if(input.at(0) == '\''){
                int pos = 1;
                int originalLine = line;
                while (pos < input.length() && input.at(pos) != '\'') {
                    if (input.at(pos) == '\n') {
                        line++;
                    }
                    pos++;
                }
                if (pos >= input.length() || input.at(pos) != '\'') {
                    //MISSING STRING
                    std::string stringValue = input.substr(0, pos);
                    input.clear(); 
                    return Token(UNDEFINED, stringValue, originalLine);
                } else {
                    //we goooood
                    std::string stringValue = input.substr(0, pos + 1);
                    input = input.substr(pos + 1);
                    return Token(STRING, stringValue, line);
                }
            } else if (input.at(0) == '#') {
                //FOR BLOCK COMMENT
                if (input.size() > 1 && input.at(1) == '|'){
                    int pos = 2;
                    while (pos + 1 < input.size() && !(input.at(pos) == '|' && input.at(pos + 1) == '#')) {
                        if (input.at(pos) == '\n') {
                        line++; //for newlines
                        }
                        pos++;
                    }
                    if (pos + 1 >= input.size()) {
                        std::string commentValue = input;
                        input.clear();
                        return Token(UNDEFINED, commentValue, line); //in case it doesnt end...
                    } else {
                        std::string commentValue = input.substr(0, pos + 2);
                        input = input.substr(pos + 2);
                        return Token(COMMENT, commentValue, line);

                //FOR SINGLELINE CMMENT
                }} else {
                    size_t pos = 0;
                    while (pos < input.size() && input.at(pos) != '\n') {
                        pos++;
                    }

                    std::string commentValue = input.substr(0, pos);
                    input = (pos < input.size()) ? input.substr(pos) : "";
                    return Token(COMMENT, commentValue, line);

                }
                
                
            } else {
                //else... undefined:

                Token undefToken = Token(UNDEFINED, std::string(1, input.at(0)), line);
                input.erase(0,1);
                return undefToken;
            
        
            }
        }

};