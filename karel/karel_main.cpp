/* 
 * Karel Main
 *
 * Author: Kareem Kamel kamel.kareem@gmai.com
 *
 * Reads input from the user and calls  KarelCompiler and LexicalAnalyzer and
 * displays output.
 */

#include "karel_compiler.h"

#include <fstream>
#include <iostream>
#include <cassert>
#include <sstream>
#include <string>

using std::string;


void Interpreter(const string &instructions); 
void ReadInputFile(char* filename, string &code);

int main(int argc, char* argv[]) {
  assert(argc > 1);
  // Read in Karel commands from external file.
  string karel_code;
  ReadInputFile(argv[1], karel_code);
  //  Step1: Instantiate a Karel object.
  //  Step2: Go through each Karel language command
  //         and call the appropriate implementation.
  Interpreter(karel_code);

  return 0;
} // Main
void ReadInputFile(char* filename, string &code) {
 
  try {
    // Read in entire file.
      // Save contents in karel_commands for later use.
    std::ifstream stream(filename);
    std::stringstream buffer;
    buffer << stream.rdbuf();
    // karel_commands is intialized with the contents of the text file.
    code  = buffer.str();
  } // Try.
  catch (std::ifstream::failure e) {
    std::cerr << "Exception opening or reading file." << std::endl;
  } // Catch.
   

}
void Interpreter(const string &in_code) {
  
  karel::KarelCompiler compiler;
  compiler.PrintState();
  compiler.Run(in_code);
  compiler.PrintState();
  
  return;
} // Interpreter.

