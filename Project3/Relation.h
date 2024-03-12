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

  
  Relation select(int index, const std::string& value) const { //Selecting rows equal to given value
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
  //Can use a Map variable to see if we find it more than once?
  //Select 2: Selects the rows where 2 attributes in the tuple are the same. (variables). ONLY selects rows that are matching. Pass in 2 column indexes, and selects the rows where the values of both columns are the same.
  //Loop through columns
  //The given row ONLY belongs in the new relation if the values in both columns at that row are equal to eachother. Remember, it not for the headers, its the variables in the rows.
  //
  //Bool select_2(parameter)? 
  Relation selectType2(int index1, int index2) const {
    Relation result(name, scheme);
    for (const auto& tuple : tuples) {
        if (tuple.at(index1) == tuple.at(index2)) {
            result.addTuple(tuple);
        }
    }
    return result;
  }


  
  Relation project(const std::vector<int>& indices) const {
    std::vector<std::string> newSchemeNames;
    //New scheme
    for (int index : indices) {
        newSchemeNames.push_back(this->scheme.at(index));
    }
    Scheme newScheme(newSchemeNames); 

    Relation result(this->name, newScheme);
    for (const auto& tuple : this->tuples) {
        //New tuple
        std::vector<std::string> newTupleValues;
        for (int index : indices) {
            newTupleValues.push_back(tuple.at(index));
        }
        Tuple newTuple(newTupleValues);
        result.addTuple(newTuple);
    }
    return result;
  } 

    Relation rename(const Scheme& newScheme) const {
        //Assuming same length as old one
        Relation result(name, newScheme);
        for (const auto& tuple : tuples) {
            result.addTuple(tuple); //Just change scheme name.?
        }
        return result;
    }


};