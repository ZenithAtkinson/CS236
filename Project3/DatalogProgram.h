#pragma once
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include "Predicate.h"
#include "Rule.h"
/* Datalog needs: vector for schemes(made of predicates), facts(made of predicates), rule(made of rules), queries(made of predicates), and a set for the domain. 
Also needs functions to add each of these to the vector and push them back based on the predicate given, and fact needs to update domain with strings. Finally, see project
specs for how the toSTring needs to look based on these vectors.*/
class DatalogProgram {
private:
      

public:
std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Rule> rules;
    std::vector<Predicate> queries;
    std::set<std::string> domain;  //wat domain? holds each unique string available. 
    DatalogProgram() = default;

    void addScheme(const Predicate& scheme) {
        schemes.push_back(scheme);
    }

    void addFact(const Predicate& fact) {
        facts.push_back(fact);
        
        for (size_t i = 0; i < fact.parameters.size(); ++i) {
            const auto& param = fact.parameters[i];//see: (what is auto& doing exactly?) creates i-th reference of parameters, and moves it for each variable. Stays constant.
            domain.insert(param.toString()); //returns the string representation of the parameter
                }
            }   

    void addRule(const Rule& rule) {
        rules.push_back(rule);
    }

    void addQuery(const Predicate& query) {
        queries.push_back(query);
    }

    std::string toString() const {      
            //awhy no
        std::stringstream ss;
        ss << "Success!\n";
         ss << "Schemes(" << schemes.size() << "):\n";
        for (size_t i = 0; i < schemes.size(); ++i) {
            ss << "  " << schemes[i].toString() << "\n";
        }   
        ss << "Facts(" << facts.size() << "):\n";
        for (size_t i = 0; i < facts.size(); ++i) {
            ss << "  " << facts[i].toString() << ".\n";
            }
        ss << "Rules(" << rules.size() << "):\n";
        for (size_t i = 0; i < rules.size(); ++i) {
            ss << "  " << rules[i].toString() << "\n";
        }
        ss << "Queries(" << queries.size() << "):\n";
        for (size_t i = 0; i < queries.size(); ++i) {
            ss << "  " << queries[i].toString() << "?\n";
        }
        ss << "Domain(" << domain.size() << "):\n";
        for (const auto& str : domain) { //does this work? See: stack overflow.
            ss << "  " << str << "\n";
            }
        return ss.str();
    }
};
