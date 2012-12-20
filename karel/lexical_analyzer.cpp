/* 
 * Lexical Analyzer Implemntation file
 * Author: Kareem Kamel kamel.kareem@gmail.com.
 */

#include "lexical_analyzer.h"

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <set>
#include <string>
#include <vector>


using namespace std;

namespace karel {

LexicalAnalyzer :: LexicalAnalyzer ()  {
}

void LexicalAnalyzer :: Run(const string &raw_code, map <string, string> &new_instructions) {
  code = raw_code;
  Language_Universe();
  Lexemes();
  TokenAnalyzer(new_instructions);
}

void LexicalAnalyzer :: Language_Universe() {
  // Insert reserved word as key and previous token as value.
  reserved.insert(std::make_pair("BEGINNING-OF-PROGRAM", "reserved"));
  reserved.insert(std::make_pair("DEFINE-NEW-INSTRUCTION", "instruction definition"));
  reserved.insert(std::make_pair("AS", "reserved"));
  reserved.insert(std::make_pair("BEGIN", "scope"));
  reserved.insert(std::make_pair("END", "scope"));
  reserved.insert(std::make_pair("BEGINNING-OF-EXECUTION", "reserved"));
  reserved.insert(std::make_pair("END-OF-EXECUTION", "reserved"));
  reserved.insert(std::make_pair("END-OF-PROGRAM", "reserved"));
  reserved.insert(std::make_pair("move", "command"));
  reserved.insert(std::make_pair("IF", "conditional"));
  reserved.insert(std::make_pair("THEN", "reserved"));
  reserved.insert(std::make_pair("turnleft", "command"));
  reserved.insert(std::make_pair("turnoff", "command"));
  reserved.insert(std::make_pair(";", "reserved"));
}

void LexicalAnalyzer :: Lexemes() {
 
  const string delimiters = " \n";
  string::size_type lastPos = code.find_first_not_of(delimiters, 0);
  // Find first "non-delimiter".
  string::size_type pos = code.find_first_of(delimiters, lastPos);
  while (string::npos != pos || string::npos != lastPos) {
    // Found a token, add it to the vector.

    if (code.substr(lastPos, pos - lastPos) != " ") {
      lexemes.push_back(code.substr(lastPos, pos - lastPos));
      //printf("%s\n", (code.substr(lastPos, pos - lastPos)).c_str());
    } 
      // Skip delimiters. Note the "not_of"
    lastPos = code.find_first_not_of(delimiters, pos);
    // Find next"non-delimiter"
    pos = code.find_first_of(delimiters, lastPos);
  } // While.
} // LexicalAnalyzer().

void LexicalAnalyzer :: TokenAnalyzer(map <string, string>  &new_instructions) {
  
  int line_num = 1;
  
  if (lexemes.front() != "BEGINNING-OF-PROGRAM") 
       syntax_errors.insert(std::make_pair("missing BEGINNING-OF-PROGRAM", line_num));
  bool contains_begin_execution = false;
  bool contains_end_execution = false;

  for (int i = 0; i < lexemes.size(); i++) {
    //printf("%s,%i\n", lexemes[i].c_str(), 0);
    if (lexemes[i] == "BEGINNING-OF-EXECUTION")
      contains_begin_execution = true;
    if (lexemes[i] == "END-OF-EXECUTION")
      contains_end_execution = true; 
    
    // Case A.
    if (reserved.find(lexemes[i]) == reserved.end() &&
      new_instructions.find(lexemes[i]) == new_instructions.end() && 
      lexemes[i-1] == "DEFINE-NEW-INSTRUCTION") {
      
      int procedure_name_index = i;
      bool add_succeeded =  AddNewInstruction(procedure_name_index, new_instructions);
      
      if(!add_succeeded)
        syntax_errors.insert(std::make_pair("undefined procedure", line_num));
      
      lexemes.erase(lexemes.begin() + i);
      //printf("%s\n", "in"); 
    }
    // Case B.
    else if (reserved.find(lexemes[i]) == reserved.end() &&
      new_instructions.find(lexemes[i]) == new_instructions.end()) {
      //printf("%s,%i\n", lexemes[i].c_str(), 2);
      syntax_errors.insert(std::make_pair(lexemes[i], line_num));
    }
    // Case C.
    else if (lexemes[i] == ";"){ 
      ++line_num;
    }
  }
    if (lexemes[lexemes.size() - 2] != "END-OF-PROGRAM")
      syntax_errors.insert(std::make_pair("missing END-OF-PROGRAM", line_num));

    if (!contains_begin_execution)
      syntax_errors.insert(std::make_pair("missing BEGINNING-OF-EXECUTION", line_num));
    if (!contains_end_execution)
      syntax_errors.insert(std::make_pair("missing END-OF-EXECUTION", line_num));
 
  //printf("new instructions: %i\n", new_instructions.size());
} // Lookup().

bool LexicalAnalyzer :: AddNewInstruction(int label_loc, map <string, string> &new_instructions) {

  string implementation;
  int start_index = label_loc + 3;
  for (int i = start_index; lexemes[i] != "END"; ++i) {

      if(reserved.find(lexemes[i]) != reserved.end()) {
        implementation += string(lexemes[i]);
      }
      else if (new_instructions.find(lexemes[i]) != new_instructions.end()) {
        string lexeme = lexemes[i];
        string token =  (new_instructions.find(lexeme))->second;
        implementation = implementation + " " + token;
      }
      else
        return false;
  }
  new_instructions.insert(std::make_pair(lexemes[label_loc], implementation));
  
  return true;
}

void LexicalAnalyzer :: Display_SyntaxErrors() {
  printf("Number of syntax errors: %i\n", syntax_errors.size());
  
  map<string, int>::iterator it;
 
  for (it = syntax_errors.begin(); it != syntax_errors.end(); ++it) {
    string value = it->first;
    int line = it->second;
    printf("statement #: %i, %s\n", line, value.c_str());
  }
} // Display_SyntaxErrors.
} // namespace karel.
