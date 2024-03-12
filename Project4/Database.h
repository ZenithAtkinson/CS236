#pragma once
#include <map>
#include <iostream>
#include "Relation.h"
#include "DatalogProgram.h"

class Database {
private:
    std::map<std::string, Relation> relations;

public:

   Database() {
    }
     
    void addRelation(std::string relationName, std::vector<std::string> schemeNames){ //what datatype is this schemes? is it the schemes object, or the parameters from datalog? call this for every scheme
        Relation rel(relationName, schemeNames);
        relations.insert({relationName, rel});
    }
    //We now have several relations that are all named and have a header of schemes, but dont have any tuples yet(no data yet).
    //Now, we must access each of these relations, and add the corresponding tuple to them below. We can access the correct location to place the tuple
        //by accessing the relation name and the scheme name(index?) of the respective tuple

    void addTuples(std::string relationName, const Tuple& tupleToAdd){
        /*for relation in relations, 
            if relationName == relations keyvalue
                add factValues to the relation   
                relations[i] = tuples?
        */
       auto it = relations.find(relationName); //confirming/finding given relationName in map
       if(it != relations.end()) {
        it->second.addTuple(tupleToAdd); //adding tuple?
        } else {
            //relation doesnt exist
        }    
    }

    void printRelation() {
    for (const auto& pair : relations) {
        std::string relationName = pair.first;
        const Relation& relation = pair.second;
        
        //Printing relation name
        std::cout << "Relation: " << relationName << std::endl;
        
        //Calling toString from relation.
        std::cout << relation.toString();
        std::cout << "--------------------------" << std::endl;
    }
}

    std::map<std::string, Relation>& getRelations() { //Returning map of Relations
        return relations;
    }

    Relation& getRelation(const std::string& relationName) { //Returning single Relation
        auto it = relations.find(relationName);
        if (it != relations.end()) {
            return it->second;
        } else {
            std::cout << "Error at getRelation" << std::endl;
            throw std::out_of_range("only doing this to avoid warning" + relationName);
        }
    }
    
    //needs to return a map of relations
};