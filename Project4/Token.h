#pragma once
#include <vector>
#include <string>
#include <sstream>


enum TokenType {
  COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EOFILE
};

class Token {
 private:
  TokenType type;
   std::string value;
   int line;

 public:
    Token() : type(UNDEFINED), value(""), line(0) {} //default vals needed?
  Token(TokenType type, std::string value, int line) : type(type), value(value), line(line) { }
  
    std::string typeName(TokenType type) const {
        switch(type)
        {
            case COMMA : return "COMMA";            //0
            case PERIOD : return "PERIOD";          //1
            case Q_MARK : return "Q_MARK";          //2
            case LEFT_PAREN : return "LEFT_PAREN";  //3
            case RIGHT_PAREN : return "RIGHT_PAREN";//4
            case COLON : return "COLON";            //5
            case COLON_DASH : return "COLON_DASH";  //6
            case MULTIPLY : return "MULTIPLY";      //7
            case ADD : return "ADD";                //8
            case SCHEMES : return "SCHEMES";        //9
            case FACTS : return "FACTS";            //10
            case RULES : return "RULES";            //11
            case QUERIES : return "QUERIES";        //12
            case ID : return "ID";                  //13
            case STRING : return "STRING";          //14
            case COMMENT : return "COMMENT";        //15
            case UNDEFINED : return "UNDEFINED";    //16
            case EOFILE : return "EOF";             //17
            default: return "NA?";                  //18
        }
  }

  std::string toString() const {
    std::stringstream out;
    out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << line << ")";
    return out.str();
  }

  TokenType getType() const{
    return type;
  }
  std::string getValue() const {
        return value;
  }
  std::string getLine() const {
      return std::to_string(line);

  }
  
};


/*
COMMA	The ',' character	,
PERIOD	The '.' character	.
Q_MARK	The '?' character	?
LEFT_PAREN	The '(' character	(
RIGHT_PAREN	The ')' character	)
COLON	The ':' character	:
COLON_DASH	The string ":-"	:-
MULTIPLY	The '*' character	*
ADD	The '+' character	+
SCHEMES	The string "Schemes"	Schemes
FACTS	The string "Facts"	Facts
RULES	The string "Rules"	Rules
QUERIES	The string "Queries"	Queries
ID	An identifier is a letter followed by zero or more letters or digits, and is not a keyword (Schemes, Facts, Rules, Queries).
Note that for the input "1stPerson" the scanner would find two tokens: an 'undefined' token made from the character "1" and an 'identifier' token made from the characters "stPerson".	
Valid Identifiers	Invalid Identifiers
Identifier1	1stPerson
Person	Schemes
STRING	A string is a sequence of characters enclosed in single quotes. White space (space, tab) is not skipped when inside a string. Two adjacent single quotes within a string denote an apostrophe. The line number for a string token is the line where the string begins. If a string is not terminated (end of file is encountered before the end of the string), the token becomes an undefined token.

The 'value' of a token printed to the output is the sequence of input characters that form the token. For a string token this means that two adjacent single quotes in the input are printed as two adjacent single quotes in the output. (In other words, don't convert two adjacent single quotes in a string to just one apostrophe in the output.)	'This is a string'

'' -- (The empty string)

'This isn''t two strings'

COMMENT	A line comment starts with a hash character (#) and ends at the end of the line or end of the file.	# This is a comment
A block comment starts with #| and ends with |#. Block comments may cover multiple lines. Block comments can be empty and multiple comments can appear on the same line. The line number for a comment token is the line where the comment begins. If a block comment is not terminated (end of file is encountered before the end of the comment), the token becomes an undefined token.	#||#

#| This is a
multiline comment |#

#| This is an illegal block comment
because it ends with end of file
UNDEFINED	Any character not tokenized as a string, keyword, identifier, symbol, or white space is undefined. Additionally, any non-terminating string or non-terminating block comment is undefined. In both of the latter cases you reach EOF before finding the end of the string or the end of the comment.	$&^ (Three undefined tokens)

'a string that does not end

EOF	The end of the input file.	
*/