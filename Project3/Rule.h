#pragma once
#include <vector>
#include <string>
#include <sstream>
#include "Parameter.h"
#include "Predicate.h"

using namespace std;

class Rule {
    public:
    Predicate headPredicate;
    std::vector<Predicate> bodyPredicates;

//constructing
    Rule(const Predicate &headPredicate, const std::vector<Predicate> &bodyPredicates) 
    : headPredicate(headPredicate), bodyPredicates(bodyPredicates) {}

    void addBODYPredicate(const Predicate& bodyPredicate) {
            bodyPredicates.push_back(bodyPredicate);
        }
    
    //"hread :- body1, body2, ..., bodN."
    std::string toString() const {
    std::stringstream ss;
    ss << headPredicate.toString() << " :- ";
    for (size_t i = 0; i < bodyPredicates.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << bodyPredicates[i].toString();
    }
    ss << ".";
    return ss.str();
}

};