#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "Token.h"
#include "DatalogProgram.h"

using namespace std;

class Parser {
 private:
  vector<Token> tokens;
  DatalogProgram createdDatalogProgram; //from datalog object
 public:
  Parser(const vector<Token>& tokens) : tokens(tokens) { }
  TokenType tokenType() const {
    return tokens.at(0).getType();
  }
  void advanceToken() {
    tokens.erase(tokens.begin());
  }
  void throwError() {
    //see notes for how to implement this correctly
    //throw "Failure!", tokens.at(0).getType(), tokens.at(0).getValue();// tokens.at(0).getLine());

    //needs to throw token
    //throw tokens.at(0);
    throw std::runtime_error("Failure!\n   (" + tokens.at(0).typeName(tokens.at(0).getType()) + ",\"" + tokens.at(0).getValue() + "\"," + tokens.at(0).getLine() + ")");
  }

  void match(TokenType t) {
    //cout << "match: " << tokens.at(0).getValue() << ": " << tokenType() << ": " << endl;
    // add code for matching token type t
    
    //if token = eofile & qieroesList.size() == 0, throw error
    //if token = facts & schemesList.size() == 0, throw error
    //cout << "SIZE OF SCHEMES LIST:" << createdDatalogProgram.schemes.size() << endl; //On test 27, this isnt working? When match is called.
    if (tokens.at(0).getType() == FACTS && createdDatalogProgram.schemes.size() == 0) {
      throwError();
    }
    if (tokens.at(0).getType() == EOFILE && createdDatalogProgram.queries.size() == 0) {
      throwError();
    }
    while (tokenType() == COMMENT) {
      //cout << "COMMENT SKIPPED" << endl;
      advanceToken();
    }
    if (!tokens.empty() && tokenType() == t) {
      advanceToken();
      //cout << "test1" << endl;
    } else {
      throwError();
    }
  }

    void idList(Predicate &scheme_pred) {
      if (tokenType() == COMMA) {
          match(COMMA);
          if (tokenType() == ID) { //make sure its an ID
              string parameterValue = tokens.at(0).getValue();
              scheme_pred.addParameter(Parameter(parameterValue, true));  
              match(ID); 
              idList(scheme_pred); 
          }
      } else {
        //nada
      }
    }


    void stringList(Predicate &fact_pred) {
      if (tokenType() == COMMA) {
        match(COMMA);
        string value = tokens.at(0).getValue(); //getting string parameter...
        match(STRING);
        fact_pred.addParameter(Parameter(value, false)); //adds value to predicate list, but first needs to specify the string is now a parameter object.
        stringList(fact_pred);
      } else {
        // lambda
      }
    }

    Parameter parameter() {
      bool val_id;
      string value;
      if (tokenType() == STRING) { //parameter
        value = tokens.at(0).getValue();
        val_id = false; //If string, return false
        match(STRING);
      } else if (tokenType() == ID) {
        value = tokens.at(0).getValue();
        val_id = true; //If ID, return true
        match(ID);
      }
      Parameter param(value, val_id);
      return param;
    }

    void parameterList(Predicate& pred) {
    if (tokenType() == COMMA) {
        match(COMMA);
        Parameter param = parameter(); 
        pred.addParameter(param);
        parameterList(pred);
    } else {
        //lambda, END
    }
  }

    Predicate predicate() { //DONE
      Predicate pred("bean");
      if (tokenType() == ID) {
        string value = tokens.at(0).getValue();
        match(ID);
        pred = Predicate(value);
        match(LEFT_PAREN);
        Parameter parem = parameter();
        pred.addParameter(parem);
        parameterList(pred);
        match(RIGHT_PAREN);
      }
      return pred;
    }

    void predicateList(std::vector<Predicate>& predicates) { //predicates from rule
      if (tokenType() == COMMA) {
        match(COMMA);
        Predicate nextPredicate = predicate();
        predicates.push_back(nextPredicate);
        predicateList(predicates); 
    } else {
      }
    }

    Predicate headPredicate() {
      Predicate head("bean"); //empty predicate (cant be NULL)
      if (tokenType() == ID) {
          string name = tokens.at(0).getValue();
          match(ID);
          head = Predicate(name);
          match(LEFT_PAREN);
          if (tokenType() == STRING || tokenType() == ID) {
              Parameter param = parameter(); //1st paramter
              head.addParameter(param); //add to head
              parameterList(head); //go through recursively
          }
          match(RIGHT_PAREN);
      }
      return head; 
      }

    void fact() {
      if (tokenType() == ID) {
        string factName = tokens.at(0).getValue(); // Capture the fact name
        match(ID); // Consume the fact name token
        Predicate fact_pred(factName);
        match(LEFT_PAREN);
        // Now proceed to parse parameters as before
        string value = tokens.at(0).getValue();
        match(STRING);
        fact_pred.addParameter(Parameter(value, false));
        stringList(fact_pred);
        match(RIGHT_PAREN);
        match(PERIOD);
        createdDatalogProgram.addFact(fact_pred);
      }
    }

    void scheme() {
      if (tokenType() == ID) {
          string predicateName = tokens.at(0).getValue();
          match(ID); // actual predicate name
          Predicate scheme_pred(predicateName);
          match(LEFT_PAREN);
          string firstParameter = tokens.at(0).getValue();
          scheme_pred.addParameter(Parameter(firstParameter, true)); 
          match(ID);
          idList(scheme_pred);
          match(RIGHT_PAREN);

          createdDatalogProgram.addScheme(scheme_pred);
          //cout << scheme_pred.parameters.size() << endl;
      } else {
        throwError();
      }
    } 


    void rule() {
      if (tokenType() == ID) {
        Predicate head = headPredicate();
        match(COLON_DASH);
        std::vector<Predicate> bodyPredicates;
        Predicate firstBodyPredicate = predicate();
        bodyPredicates.push_back(firstBodyPredicate);
        predicateList(bodyPredicates);
        match(PERIOD);
        Rule current_rule(head, bodyPredicates);
        createdDatalogProgram.addRule(current_rule);
    }
      }
    

    void query() {
    if (tokenType() == ID) {
        Predicate query_pred = predicate();
        match(Q_MARK);
        createdDatalogProgram.addQuery(query_pred);
    }
  }

    void queryList() {
      if (tokenType() == ID) {
        query();
        queryList();
      } else {
        // lambda
      }
    }

    void ruleList() {
      if (tokenType() == ID) {
        rule();
        ruleList();
      } else {
        // lambda
      }
    }

    void factList() {
      if (tokenType() == ID) {
        fact();
        factList();
      } else {
        // lambda
      }
    }

    void schemeList() {
      if (tokenType() == ID) {
        scheme();
        schemeList();
      } else {
        // lambda
      }
    }

    DatalogProgram datalogProgram() {
      //all of this should be in a try section
      /* pseudo
      try { 
        ...
      }
      catch (Token t){
        cout << t.toString or t.getValue
      }
      basically, if we have an error we should just output current token we are stopped
      */
     try {
      
        match(SCHEMES);
        match(COLON);
        //scheme(); //do I need this? Prob not.
        schemeList();
        match(FACTS);
        match(COLON);
        factList();
        match(RULES);
        match(COLON);
        ruleList();
        match(QUERIES);
        match(COLON);
        //query(); // do I need this? Proably not, as it is also in my queryList.
        queryList();
        match(EOFILE);
        //
        
      } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        exit(1); // or handle the error without exiting, if preferred
    }
      return createdDatalogProgram;
    } //catch will be after. It will catch the exception thrown
  
};
