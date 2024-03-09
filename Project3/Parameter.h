#pragma once
#include <string>


class Parameter {
public:
    std::string value; //given parameter
    bool val_id;
    //constructor with given parameter
    Parameter(const std::string& value, const bool val_id) : value(value), val_id(val_id){}

    //ID = false;
    //string = true;

    //returning it as a string
    std::string toString() const {
        return value;
    }
};