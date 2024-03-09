#pragma once
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
private:
    DatalogProgram datalogProgram;
    Database database;
    std::string relationName;
    std::vector<string> schemeNames;
    std::vector<string> factNames;

public:
     Interpreter(const DatalogProgram& program) : datalogProgram(program) {}

     Database& getDatabase() {
        return database;
    }


    void evaluateSchemes() {
        for (const auto& scheme : datalogProgram.schemes) {
            relationName = scheme.name;
            schemeNames = {};
            
            std::cout << "Relation Name:" << relationName << std::endl; //Name of predicate(scheme). This will be the name of the relation.
                                                    //how do we access its parameters?. These will be the names of the schemes in the relation.
            /*for(const auto& pred : datalogProgram.schemes){
            } */
            for (const auto& param : scheme.parameters){
                 std::cout << "  Scheme name: " << param.toString() << std::endl;
                 schemeNames.push_back(param.toString());
            }
            database.addRelation(relationName, schemeNames);
        }
    }

    //e('A', 'B', 'C', 'D', 'E'). == relation e with the columns x, y, z, w, v which are filled with the facts 'A', 'B', 'C', 'D', 'E'

    void evaluateFacts() {
        for (const auto& fact_list : datalogProgram.facts) {
        factNames = {};
        std::cout << "Fact name(relation name): " << fact_list.getName() << std::endl;
            for (const auto& fact : fact_list.parameters){
                std::cout << "  Fact value: " << fact.toString() << std::endl;
                factNames.push_back(fact.toString());
                
            }
            //Turn vector into a tuple:
            Tuple factTuple(factNames);
            database.addTuples(fact_list.getName(), factNames);
        }
    }

    void evaluateQueries() {
        //where selects, projects, renames are done. Need to use all three.
        //Select correct tuples for this query, project for the format, rename
        /*You may assume the following about the Datalog program:
        All schemes, facts, rules, and queries with the same name will have the same number of parameters.
        No two attributes in the same scheme will have the same value.
        No two schemes in the scheme list will have the same name.
        Every relation referenced in a fact, rule, or query will have been defined in the scheme section.
        */

    }

};





/*
 // For each scheme in datalogProgram, create an empty Relation in the database
    }

    void evaluateFacts() {
        // For each fact in datalogProgram, create a Tuple and insert it into the corresponding Relation in the database
    }

    // Method to evaluate queries (to be implemented)
    void evaluateQueries() {
        // For each query in datalogProgram, find matching tuples in the database
    }

    // Placeholder for future rule evaluation method*/