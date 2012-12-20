/*
 * LexicalAnalyzer Class
 *    Does lexical and syntax analysis and keeps track of errors in the
 *    programmers code.
 * Author: Kareem Kamel kamel.kareem@gmail.com
 */

#ifndef KAREL_LEXICAL_ANALYZER_H
#define KAREL_LEXICAL_ANALYZER_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace karel {

class LexicalAnalyzer {
  
  private:
    // Stores the preprocessed raw karel code written by the programmer.
    std::string code;
    // Stores and keeps track of syntax errors and their corresponding line
    // number.
    std::map <std::string, int> syntax_errors;
    // Stores the lexemes generated from the code.
    std::vector< std::string> lexemes;
    // Stores reserved words in the Karel language.
    std::map <std::string, std::string> reserved;
    
    // Stores user defined procedures and their implementations.
    // This is then returned to execute the code.
    bool AddNewInstruction(int index, std::map < std::string, 
        std::string >  &user_defined_instructions );
    // Checks the syntax of tokens and reserved words.
    void TokenAnalyzer (std::map <std::string, std::string>  &user_defined_instructions);
    // Splits the incoming karel code into lexemes.
    void Lexemes ();
    // Defines and populates reserved words in the Karel language.
    void Language_Universe ();
  
  public:
    LexicalAnalyzer();
    // Returns number of syntax errors.
    int Get_NumOfSyntaxErrors () { return syntax_errors.size(); }
    // Prints syntax errors and the corresponding line number on which the
    // occur.
    void Display_SyntaxErrors ();
    // Runs LexicalAnalyzer.
    void Run(const std::string &raw_code, std::map<std::string, std::string> &user_defined_instructions );
};
} // namespace karel
#endif // KAREL_LEXICAL_ANALYZER_H
