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

int main() {

  Scheme scheme1( { "A", "B" } );
  Scheme scheme2( { "B", "C" } );

  Tuple tuple1( {"'1'", "'2'"} );
  Tuple tuple2( {"'3'", "'4'"} );

  Relation::joinable(scheme1, scheme2, tuple1, tuple2);

}
 