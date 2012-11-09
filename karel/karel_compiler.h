#ifndef KAREL_KAREL_COMPILER
#define KAREL_KAREL_COMPILER

#include <cstdlib>
#include <string>
#include <vector>

namespace karel {

class KarelCompiler {
  private:
    // Karel's world to be provided as input. It is implemented
    // using a 2D grid of booleans.
    bool *world;      
    // Karel first starts off pointing East. East is 
    // thus taken as Direction 0. Directions are enumerated 
    // in an anti-clockwise fashion. The directions are as 
    // follows:
    // 
    // East => 0
    // North => 1
    // West => 2
    // South => 3
    short direction; 
    // Define a pointin a 2D plane. 
    struct point {
      int x;
      int y;
    };

    // Holds current location of Karel in Karel's world. 
    point location; 
  
  public:
    // Initialize Karel.
    KarelCompiler();
    // Lexical Analyzer.
    void LexicalAnalyzer(std::string &commands, std::vector<std::string> *tokens);
    // Syntax Analyzer.
    void SyntaxAnalyzer(const std::vector<std::string> &instructions, std::vector<std::string> *errors);
    void CodeGenerator(const std::vector<std::string> &instructions);
    // Implements Karel's Move() command. 
    void Move();
    // Implements Karel's TurnLeft() command. 
    void TurnLeft();
    // Implements Karel;s TurnOff() command.
    void TurnOff();
    // Returns x axis of Karel's location.
    int GetCurrentX() {return location.x;}
    // Returns y axis of Karel's location.
    int GetCurrentY() {return location.y;}
    // Prints final postion of Karel.
    void PrintState()const;

};
} // namespace Karel.
#endif // KAREL_KAREL_COMPILER
