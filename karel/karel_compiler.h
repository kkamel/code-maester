#ifndef KAREL_KAREL_COMPILER_H
#define KAREL_KAREL_COMPILER_H

#include <map>
#include <string>
#include <vector>

namespace karel {

class KarelCompiler {
  private:
    // Karel's world to be provided as input. It is implemented
    // using a 2D grid of booleans.
    //bool *world;      
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
    // Dimentions of the square 2D world that Karel can move inside.
    static const int world_dim = 8;
    // Holds current location of Karel in Karel's world. 
    point location;
    std::string program_code;
    std::vector <std::string> instructions;
    
    void SyntaxAnalyzer ();
    // Tokenizes input code.
    void Tokenizer (std::string s, std::vector<std::string> &tokens);
    // Executes Karels commands.
    void CodeGenerator (std::map<std::string, std::string> &user_procedures);
     // Implements Karel's Move() command. 
    void Move ();
    // Implements Karel's TurnLeft() command. 
    void TurnLeft ();
    // Implements Karel;s TurnOff() command.
    void TurnOff ();
    // Returns x axis of Karel's location.
    int GetCurrentX () {return location.x;}
    // Returns y axis of Karel's location.
    int GetCurrentY () {return location.y;}
    // Prints final postion of Karel.
  
  public:
    // Initialize Karel.
    KarelCompiler ();
    // Run KarelCompiler.
    void Run(const std::string &input_code);
    // Prints the state of Karel in the world.
    void PrintState () const;
    // Prints visualization of Karel in the world.
    void PrintWorld () const;
};
} // namespace Karel.
#endif // KAREL_KAREL_COMPILER_H
