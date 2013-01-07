/*
 * Karel Compiler Implementation file
 * Author: Kareem Kamel kamel.kareem@gmail.com
 */

#include "karel_compiler.h"
#include "lexical_analyzer.h"

#include <iostream>
#include <map>
#include <cmath>
#include <cstdio>
#include <cstdlib>
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

} // KarelCompiler.

void KarelCompiler :: Run(const string &input_code) {

  program_code = input_code;
  //printf("%s", program_code.c_str());
  SyntaxAnalyzer();
} // Run.

void KarelCompiler :: Tokenizer(string s, vector<string>& tokens) {
  // Split into instructions.
  //printf("%s\n", program_code.c_str());
  const string delimiters = "\n ;";
  string::size_type lastPos = s.find_first_not_of(delimiters, 0);
  // Find first "non-delimiter".
  string::size_type pos = s.find_first_of(delimiters, lastPos);
  while (string::npos != pos || string::npos != lastPos) {
    // Found a token, add it to the vector.
    if (s.substr(lastPos, pos - lastPos) != " ") {
      tokens.push_back(s.substr(lastPos, pos - lastPos));
      //printf("%s\n", (s.substr(lastPos, pos - lastPos)).c_str());
    } 
      // Skip delimiters. Note the "not_of"
    lastPos = s.find_first_not_of(delimiters, pos);
    // Find next"non-delimiter"
    pos = s.find_first_of(delimiters, lastPos);
  }
} // LexAnalyzer.

void KarelCompiler :: SyntaxAnalyzer() {
  
  map <string, string> user_procedures;
  string code_to_preprocess = program_code;
  LexicalAnalyzer lex_analyzer;
  lex_analyzer.Run(code_to_preprocess, user_procedures);

  if (lex_analyzer.Get_NumOfSyntaxErrors() > 0) {
    lex_analyzer.Display_SyntaxErrors();
    return;
  }
 
  Tokenizer(program_code, instructions);
  CodeGenerator(user_procedures);
  
} // SyntaxAnalyzer.

void KarelCompiler :: CodeGenerator(map<string, string> &procedures) {
  
  int n = instructions.size();
  string current_instruction;
  vector<string>::iterator it;
  
  for (it = instructions.begin() ; it != instructions.end(); it++)
    if(*it == "BEGINNING-OF-EXECUTION")
      break;

  for (it; it != instructions.end(); it++) {
        // TODO: Add the remaining instructions to the switch-case 
        // statement.

    current_instruction = *it;
    
    if (procedures.find(current_instruction) != procedures.end()) {
      
      string procedure_code = procedures.find(current_instruction)->second;
      //printf("%s\n", procedure_code.c_str());
     
      vector <string> procedure_tokens;
      Tokenizer(procedure_code, procedure_tokens);
      
      for (int i = 0; i < procedure_tokens.size(); i++) {
        if (procedure_tokens[i] == "move") {
          printf("%s\n", "move");
          Move();
        }
        else if(procedure_tokens[i] == "turnleft") {
          TurnLeft();
          printf("%s\n", "turnleft");
        }
        else if (procedure_tokens[i] == "turnoff") {
          TurnOff();
          printf("%s\n", "turnoff");
        } // end else if.
        PrintWorld();
      } // end for.
    } // if case preocedures.
    else {
      if (current_instruction == "move") {
        printf("%s\n", "move");
        Move();
      }
      else if(current_instruction == "turnleft") {
        TurnLeft();
        printf("%s\n", "turnleft");  
      }
      else if (current_instruction == "turnoff") {
        TurnOff();
        printf("%s\n", "turnoff");
      } // else if.
      PrintWorld();
    } // else.

  }
} // CodeGenerator.

// Implements Move() command in Karel
void KarelCompiler :: Move() {
  // Check direction of travel.
  bool border = 0;
  switch (direction) {
    // Karel pointing East.
    case 0:
      // TODO: Check for obstacles ahead. 
      if (location.x < world_dim)
        ++location.x;
      else
        border = true;
      break;
    // Karel pointing North.
    case 1:
      // TODO: Check for obstacles ahead. 
      if (location.y < world_dim)
        ++location.y;
      else
        border = true;
      break;
    // Karel pointing West.
    case 2:
      // TODO: Check for obstacles ahead.
      if(location.x > 1)
        --location.x;
      else 
        border = true;
      printf("column%i, row %i\n", location.x, location.y);
      break;
    // Karel pointing South.
    case 3:
      // TODO: Check for obstacles ahead.
      if (location.y > 1)
        --location.y;
      else
        border = true;
      printf("column %i, row %i\n", location.x, location.y);
      break;
  }
  if(border)
    printf ("Ouch, you just walked into a wall!\n");
} // Move.

void KarelCompiler :: TurnLeft() {
  // If direction = South (3pi/2 rad) the 
  // next pi/2 is the same as 0.
    // Turn left => 90 degrees.
    ++direction;
    direction = direction % 4;

} // TurnLeft.

void KarelCompiler :: TurnOff() {
  // The Karel program has finished executing.
} // TurnOff.

void KarelCompiler :: PrintState() const {
   printf("\nPosition of robot: < %i,%i >", location.x, location.y);
   printf(" facing ");

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

void KarelCompiler :: PrintWorld() const {

  int karel_location = location.y * world_dim - location.x; 
  printf("%i\n", karel_location);     
  for (int i = world_dim; i > 0; i--) {
    //printf("%i\n", i);
    for (int j = 1; j <= world_dim; j++) {
      int square_num;
      square_num = i * world_dim - j; 
      
      if (square_num == karel_location) {
         switch (direction) {
           case 0:
             printf("%c", '>');  
             break;
           case 1:
             printf("%c", '^');  
             
             break;
           case 2:
             printf("%c", '<');
             break;
           case 3:
             printf("%c", 'v');
             break;
         }
      }
      else
        printf("%c", '.');
    }
    printf("\n");
  }
  printf("\n");
} // PrintWorld.
} // namespace Karel. 
