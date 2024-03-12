#pragma once
#include <string>


class Parameter {
public:
    std::string value; //given parameter
    bool isConstant;
    //constructor with given parameter
    Parameter(const std::string& value, const bool isConstant) : value(value), isConstant(isConstant){}

    //ID = false;
    //string = true;

    //returning it as a string
    std::string toString() const {
        return value;
    }
};