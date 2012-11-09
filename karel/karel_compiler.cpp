#include "karel_compiler.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;
namespace karel {

// Karel Factory
KarelCompiler :: KarelCompiler() {
  // Step1: Initialize Karel's position.
  location.x = 1;
  location.y = 1;
  direction = 0;

  // TODO Step2: Read in world from file.
} // KarelCompiler.

void KarelCompiler :: LexicalAnalyzer(string &commands, vector<string> *tokens) {
  // Split into tokens.
  const string delimiters = "\n, ";
  string::size_type lastPos = commands.find_first_not_of(delimiters, 0);
  // Find first "non-delimiter".
  string::size_type pos = commands.find_first_of(delimiters, lastPos);
  while (string::npos != pos || string::npos != lastPos) {
    // Found a token, add it to the vector.
    if (commands.substr(lastPos, pos - lastPos) != " ")
      (*tokens).push_back(commands.substr(lastPos, pos - lastPos));
    // Skip delimiters. Note the "not_of"
    lastPos = commands.find_first_not_of(delimiters, pos);
    // Find next"non-delimiter"
    pos = commands.find_first_of(delimiters, lastPos);
  }
}

void KarelCompiler :: SyntaxAnalyzer(const vector<string> &instructions, vector<string> *syntax_errors) {
 
  //TODO: Strip instructions before evaluating their syntax.
  for (int i = 0; i < instructions.size(); i++)  {
    //cout << instructions[i] << endl;
      if (instructions[i] != "BEGIN" &&
          instructions[i] != "move" &&
          instructions[i] != "turnleft" &&
          instructions[i] != "turnoff" &&
          instructions[i] != "BEGINNING-OF-PROGRAM" &&
          instructions[i] != "BEGINNING-OF-EXECUTION" &&
          instructions[i] != "END-OF-PROGRAM" &&
          instructions[i] != "END-OF-EXECUTION" &&
          instructions[i] != "END" ) {
        (*syntax_errors).push_back(instructions[i]);
      }
  }
} // SyntaxAnalyzer.

void KarelCompiler :: CodeGenerator(const vector<string> &instructions) {
  for (int i = 0; i < instructions.size(); i++) {
        // TODO: Add the remaining instructions to the switch-case 
        // statement.
      if (instructions[i] == "move") {
        cout << "move" << endl;
        Move();
      }
      else if(instructions[i] == "turnleft") {
        TurnLeft();
        cout << "turnleft" << endl;
      }
      else if (instructions[i] == "turnoff") {
        TurnOff();
        cout << "turnoff" << endl;
      }
  }
} // CodeGenerator.

// Implements Move() command in Karel
void KarelCompiler :: Move() {
  // Check direction of travel.
  switch (direction) {
    // Karel pointing East.
    case 0:
      // TODO: Check for obstacles ahead. 
      ++location.x;
      break;
    // Karel pointing North.
    case 1:
      // TODO: Check for obstacles ahead. 
      ++location.y;
      break;
    // Karel pointing West.
    case 2:
      // TODO: Check for obstacles ahead.
      --location.x;
      break;
    // Karel pointing South.
    case 3:
      // TODO: Check for obstacles ahead.
      --location.y;
      break;
  }
} // Move.

void KarelCompiler :: TurnLeft() {
  // If direction = South (3pi/2 rad) the 
  // next pi/2 is the same as 0.
  if (direction < 4) {
    // Turn left => 90 degrees.
    ++direction;
  }
  else {
    // Turn back to East.
    direction = 0;
  }
} // TurnLeft.

void KarelCompiler :: TurnOff() {
  // The Karel program has finished executing.
} // TurnOff.

void KarelCompiler :: PrintState() const {
   printf("%i,%i\n", location.x, location.y);
   switch (direction) {
     case 0:
       printf("%s\n", "East");
       break;
     case 1:
       printf("%s\n", "North");
       break;
     case 2:
       printf("%s\n", "West");
       break;
     case 3:
       printf("%s\n", "South");
       break;
   }
} // PrintPosition.

} // namespace Karel. 
