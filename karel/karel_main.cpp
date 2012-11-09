#include "karel_compiler.h"

#include <fstream>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

using namespace karel;
using std::string;
using std::vector;


void Interpreter(string& instructions); 

int main(int argc, char* argv[]) {
  assert(argc > 1);
  // Read in Karel commands from external file.
  string karel_commands;
  try {
    // Read in entire file.
      // Save contents in karel_commands for later use.
    std::ifstream stream(argv[1]);
    std::stringstream buffer;
    buffer << stream.rdbuf();
    // karel_commands is intialized with the contents of the text file.
    karel_commands  = buffer.str();
  } // Try.
  catch (std::ifstream::failure e) {
    std::cerr << "Exception opening or reading file." << std::endl;
  } // Catch.

  // TODO: Step1: Instantiate a Karel object.
  //       Step2: Go through each Karel language command
  //              and call the appropriate implementation.

  Interpreter(karel_commands);

  return 0;
} // Main

void Interpreter(string &instructions) {
  // TODO: Step1: Run instructions through lexical analyzer.
  //       Step2: Validate instruction syntax.
  //       Step3: Instantiate Karel object.
  //       Step4:
  // Stores Karel language tokens.
  vector<string> tokens;
  // Stores syntax errors of Karel execution. 
  vector<string> syntax_errors; 
  // Check for correct syntax to start execution of program.
  // Instantiate KarelCompiler object.
  KarelCompiler karel_inst;
  karel_inst.LexicalAnalyzer(instructions, &tokens); 
  karel_inst.SyntaxAnalyzer(tokens, &syntax_errors);
  
  if (syntax_errors.empty()){
    karel_inst.CodeGenerator(tokens);
    karel_inst.PrintState();
  } 
  else {
    std::cout << "Errors: " << syntax_errors.size() <<std::endl;
    for(int i = 0; i < syntax_errors.size(); i++) {
      std::cout << "Syntax error: " << syntax_errors[i] << std::endl;
    }
  }

  return;
  
} // Interpreter.

