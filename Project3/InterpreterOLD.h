#pragma once


//This class will:
//Might not have to do this if I create it in database.
/* Takes a DatalogProgram (the vectors of schemes, facts, rules, and queries)
Stores the DatalogProgram as a data member
Makes a Database using the schemes and the facts, and stores it as a data member
Will evaluate the queries in Part B and the rules in project 4 */

class Interpreter {

private:


public:
    //evaluate schemes: creates empty database, empty table for each scheme. Each value in the vector of schemes will be a column.
    //evaluate facts: fill out the columns with tuples from facts.

//Pseudocode:
/*
Input: DatalogProgram
Store the DatalogProgram as a data member
Make a Relation for each scheme-Predicate, and put that Relation in the Database data member
Make a Tuple for each fact-Predicate, and put that Tuple in the appropriate Relation in the Database
*/

//So basically, does the database object just hold all the variables in a large table, and has basic get and set functions?
//DO we set the variables to from the datalog program to the databse here?
//Do we evaluate the Queries here?

//Querie will look through the facts in a relation seeing if any of them match it. We do this by accessing the relation name.



//For evaluating queries, see Project3 help slides, slides 17,19,20,and 25 for flow chart.
}