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

    Relation evaluateQueries() {
        //where selects, projects, renames are done. Need to use all three.
        //Select correct tuples for this query, project for the format, rename
        /*You may assume the following about the Datalog program:
        All schemes, facts, rules, and queries with the same name will have the same number of parameters.
        No two attributes in the same scheme will have the same value.
        No two schemes in the scheme list will have the same name.
        Every relation referenced in a fact, rule, or query will have been defined in the scheme section.
        */
        //take predicate as input, loop through all paramters in predicate
        //Check if predicate is constant or ID (from predicate, predicate.)
            //if constant, do select(type 1)
            //if variable, have we seen this variable before? (select_match function?)
                //if yes, do a select(type 2)
                //if no, mark it to keep for the project and rename.
        
        //grab relation from database
        
        //loop predicates, then loop parameters (double nested loop)
        Parameter p = //P.;
        if (p.ID == true){
            //is constant
            .select(index, stringval);
        } else {
            //is variable
            //if not seen before:
                //Mark a variable as a column and an attribute you want to keep if it's the first time you've seen the variable
                //Using a map<string, int> is one idea, representing the name of the variable and the index where you first found it
            //else
                //select type 2, pass in indexes of matching variables.
            
        }

        //return finalRelation;
    } //What is difference between select type 1 and select type 2? Is select type 2 ONLY determining if we have seen a variable before?

    void evaluateAllQueries() {
        for (const Predicate& query : datalogProgram.queries) {
            Relation result = evaluateQuery(query);

        }
    }
    //Do we need evaluatePredicate?

};