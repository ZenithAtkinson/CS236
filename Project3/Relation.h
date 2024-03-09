#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include "Tuple.h"

class Relation {

 private:

  std::string name;
  Scheme scheme;
  std::set<Tuple> tuples;

 public:

  Relation(const std::string& name, const Scheme& scheme)
    : name(name), scheme(scheme) { }

  void addTuple(const Tuple& tuple) {
    tuples.insert(tuple);
  }

   std::string toString() const {
    std::stringstream out;
    for (auto it = tuples.begin(); it != tuples.end(); ++it) {
        out << it->toString(scheme) << "\n"; //it is a pointer accessing the function
    }
    return out.str();
  }

  
  Relation select(int index, const std::string& value) const {
    Relation result(name, scheme);
    for (auto it = tuples.begin(); it != tuples.end(); ++it) {
      if (it->at(index) == value){
        //std::cout << it->at(index);
        result.addTuple(*it);
      }
    }
    return result;  
  }
  //need a second select_match for matching values. If there is a query that is e(X,Y,X), its gotta check that the two X's match and are different than Y. If its X,Y,Z, it has to confirm these are different.

  //Needs additional functions for project and rename. When called, each function will:
    //Make an empty relation, fill the relation, return the relation.
    //So each time we call the function the change the relation, we just make a new relation with the changes and return it.



};