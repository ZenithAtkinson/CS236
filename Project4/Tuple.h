//think of it as facts
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Scheme.h"

class Tuple {

private:

  std::vector<std::string> values;

public:

  Tuple(const std::vector<std::string>& values) : values(values) { }

  unsigned size() const {
    return values.size();
  }

  const std::string& at(int index) const {
    return values.at(index); 
  }

  bool operator<(const Tuple& t) const { 
    return values < t.values;
  }

  std::string toString(const Scheme& scheme) const {
    const Tuple& tuple = *this;
    std::stringstream out;

    size_t size = scheme.size();
    for (size_t i = 0; i < size; i++){
      out << scheme.at(i) << "=" << tuple.at(i);
      if (i < size - 1) { //Fixes extra commas
            out << ", ";
        }
    }
    
    return out.str();
  }

  // TODO: add more delegation functions as needed

};
