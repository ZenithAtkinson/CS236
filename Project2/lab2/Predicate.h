#pragma once
#include <vector>
#include <string>
#include <sstream>
#include "Parameter.h"

using namespace std;

class Predicate {
  public:
    std::string name;
    std::vector<Parameter> parameters;

    Predicate(const string& name) : name(name) {}
      //funcion to add parameters
    void addParameter(const Parameter parameter) {
      parameters.push_back(parameter);
    }

    // changin to string: parent("John", "Doe")
    std::string toString() const {
      stringstream ss;
      ss << name << "(";
      for (int i = 0; i < parameters.size(); i++){
          if (i > 0){
            ss << ", ";
          }
            ss << parameters[i].toString();
      }
        ss << ")";
        return ss.str();
    }

};