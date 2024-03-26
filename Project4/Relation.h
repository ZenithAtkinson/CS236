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

  Relation() {}

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
  
    Relation project(const std::vector<int>& indices) const { //How does this need to be modified? vvv
    //The project operation needs to be able to change the order of the columns in a relation to support evaluating rules.
      std::vector<std::string> newAttributes;
      for (int index : indices) {
          newAttributes.push_back(scheme.at(index));
      }
      Scheme newScheme(newAttributes);

      Relation result(name, newScheme);

      //Iterate over each tuple in the current relation
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

    //OVERLOADED PROJECT FUNCTION:
    Relation project(const Scheme& headerScheme) const { 
        std::vector<int> indices;
        // Find the indices of the attributes in the current scheme that match the headerScheme's order
        for (const auto& attr : headerScheme.getNames()) {
            auto it = std::find(scheme.getNames().begin(), scheme.getNames().end(), attr);
            if (it != scheme.getNames().end()) {
                indices.push_back(std::distance(scheme.getNames().begin(), it));
            }
        }

        // Proceed with the existing logic of the project using the found indices
        return this->project(indices);
    }


  Relation rename(const Scheme& newScheme) const {
      //New relation with same name+tuples, but new scheme.
      Relation result(this->name, newScheme);
      for (const Tuple& t : this->tuples) {
          result.addTuple(t);
      }

      return result;
  }
  

  static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme, const Tuple& leftTuple, const Tuple& rightTuple) {
    for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
        const std::string& leftName = leftScheme.at(leftIndex);
        const std::string& leftValue = leftTuple.at(leftIndex);
        //std::cout << "left name: " << leftName << " value: " << leftValue << std::endl;
        for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
            const std::string& rightName = rightScheme.at(rightIndex);
            const std::string& rightValue = rightTuple.at(rightIndex);
            //std::cout << "right name: " << rightName << " value: " << rightValue << std::endl;
            if (leftName == rightName && leftValue != rightValue) {
                return false;
            }
        }
    }
    return true; //no mismatches
  }

  Relation join(const Relation& right) { //This function will call joinSchemes(), joinable(), joinTuples().
      const Relation& left = *this;
      Scheme combinedScheme = joinSchemes(left.scheme, right.scheme);
      Relation result("JoinedRelation", combinedScheme);

      for (const auto& leftTuple : left.tuples) {
          for (const auto& rightTuple : right.tuples) {
              if (joinable(left.scheme, right.scheme, leftTuple, rightTuple)) {
                  Tuple combinedTuple = joinTuples(leftTuple, rightTuple, left.scheme, right.scheme);
                  result.addTuple(combinedTuple);
              } else {
                //std::cout << "Not joinable?" << std::endl;
              }
          }
      }

      return result;
  }


    Scheme joinSchemes(const Scheme& leftScheme, const Scheme& rightScheme) {
      std::vector<std::string> combinedNames;
      // Add all names from the left scheme
      for (size_t i = 0; i < leftScheme.size(); ++i) {
          combinedNames.push_back(leftScheme.at(i));
      }
      // Add names from the right scheme if they're not already present
      for (size_t i = 0; i < rightScheme.size(); ++i) {
          if (std::find(combinedNames.begin(), combinedNames.end(), rightScheme.at(i)) == combinedNames.end()) {
              combinedNames.push_back(rightScheme.at(i));
          }
      }
      return Scheme(combinedNames);
  }



  Tuple joinTuples(const Tuple& leftTuple, const Tuple& rightTuple, const Scheme& leftScheme, const Scheme& rightScheme) {
      std::vector<std::string> combinedValues;
      // Add all values from the left tuple
      for (size_t i = 0; i < leftTuple.size(); ++i) {
          combinedValues.push_back(leftTuple.at(i));
      }
      // Add values from the right tuple if the corresponding scheme attribute is not in the left scheme
      for (size_t i = 0; i < rightScheme.size(); ++i) {
          bool found = false;
          for (size_t j = 0; j < leftScheme.size(); ++j) {
              if (rightScheme.at(i) == leftScheme.at(j)) {
                  found = true;
                  break;
              }
          }
          if (!found) {
              combinedValues.push_back(rightTuple.at(i));
          }
      }
      return Tuple(combinedValues);
  }

    bool unionWith(const Relation& resultRelation) {
        
        /*
        It should: given a relation (rule relation), looks it up in the database the matching table(by header),((if im workign on rule cn it looks up relationship cn in the database))
        Given that new relation, for each tuple in the rule relation, add it to the database, and then stick that cn relationship back INTO the database.
        If anything is added to the database, return true.
        */
        
         bool addedNew = false;
        for (const auto& tuple : resultRelation.tuples) {
            //std::cout << "In unionWith" << std::endl;
            auto insertResult = tuples.insert(tuple);
            if (insertResult.second) {
                std::cout << " " << tuple.toString(this->scheme) << std::endl;
                addedNew = true;
            }
        }
        return addedNew;
        }






      //ALSO need functions for:
  /*joinSchemes: combines the schemes for the left and right relations into single scheme for the result relation.

  joinTuples: combines tuples from the left and right relations into single tuple for the result relation.*/
  


};