#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
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
    //std::cout << "RElation: " << out.str() << std::endl;
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

  Relation selectType2(int index1, int index2) {
    Relation result(name, scheme);
    for (const auto& tuple : tuples) {
        if (tuple.at(index1) == tuple.at(index2)) {
            result.addTuple(tuple);
        }
    }
    return result;  // return the resulting relation
  }


  
    Relation project(const std::vector<int>& indices) const {
      std::vector<std::string> newAttributes;
      for (int index : indices) {
          newAttributes.push_back(scheme.at(index));
      }
      Scheme newScheme(newAttributes);

      Relation result(name, newScheme);

      // Iterate over each tuple in the current relation
      for (const Tuple& oldTuple : tuples) {
          std::vector<std::string> newValues;

          //  add the value at that index to new tuple values
          for (int index : indices) {
              newValues.push_back(oldTuple.at(index));
          }

          //add the new tuple to the result relation
          Tuple newTuple(newValues);
          result.addTuple(newTuple);
      }

      return result;
  }

  Relation rename(const Scheme& newScheme) const {
      //New relation with same name+tuples, but new scheme.
      Relation result(this->name, newScheme);
      for (const Tuple& t : this->tuples) {
          result.addTuple(t);
      }

      return result;
  }


};