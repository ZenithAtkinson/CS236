#include <iostream>
#include <fstream> 
#include <vector> 
#include "Scanner.h"
#include "DatalogProgram.h"
#include "Parser.h"
#include "Interpreter.h"

std::string readFile(const std::string& filename) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {//check if opened...
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }
 //reading line by line into a big file
    std::string line;
    std::string inputText;
    while (std::getline(inputFile, line)) {
        inputText += line + '\n'; 
    }

    inputFile.close();
    return inputText;
}

void printTokens(const std::vector<Token>& tokens) {
    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& token = tokens[i];
        std::cout << token.toString() << std::endl;
    }
}

int main(int argc, char *argv[]) {
    //getting input file and making it a .txt file
     if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string inputText = readFile(argv[1]);

    //scanner with .txt file as input
    Scanner scanner(inputText);

    //TOKENIZING, going ino EOFILE is reached. creating vector of tokens
    std::vector<Token> tokens;
    Token token;
    for (size_t i = 0; token.getType() != EOFILE; ++i) {
        tokens.push_back(token);
        token = scanner.scanToken();
    }
    //Add final EOFILE to the tokens.
    token = scanner.scanToken();
    tokens.push_back(token);

    // Print all tokens
    //printTokens(tokens);
    tokens.erase(tokens.begin());

    //parsing...

    Parser p(tokens);
    
    //cout << "SIZE OF THE TOKENS VECOTR:---------------" << tokens.size() << endl;
    DatalogProgram crdatalogProgram = p.datalogProgram();
    /*Fix error handling in the parser. (Throw an Exception in the 'throwError' function.) (Catch the Exception at the top of the parser and report the error.)
        Write classes for Parameter, Predicate, Rule, and Datalog Program.
        Add code to the parser to create Parameter, Predicate, and Rule objects while parsing, and construct a Datalog Program object that contains lists of Schemes, Facts, Rules, and Queries.*/
    //cout << "DatalogProgram function creation in parser" << endl;
    //DatalogProgram datalogProgram = ...?
    
    // Use the datalog program as needed
    //if... schemes(0) || Facts(0) || etc... throw error.
    
    //Print out entire relation:
    //std::cout << crdatalogProgram.toString();
    //cout << "END" << endl;

    //Print out scheme details:
       /*for (const auto& scheme : crdatalogProgram.schemes) {
        // If scheme's name is stored in parameters or another accessible member
        std::cout << "Scheme details: " << scheme.toString() << std::endl; // Adjust based on how you can access the scheme name or details
    }*/

    Interpreter interpreter(crdatalogProgram);
    interpreter.evaluateSchemes();
    interpreter.evaluateFacts();
    interpreter.evaluateAllQueries();
    
    //Database& db = interpreter.getDatabase();
    //db.printRelation(); 
    

    return 0;
}
 