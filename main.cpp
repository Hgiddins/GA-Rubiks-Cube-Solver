#include "Cube.h"
#include <iostream>
#include <vector>
#include <string>

int main() {
    Cube cube;

    // Scramble
    std::vector<std::string> shufflemoves = {"R'", "L", "U'", "D2", "B", "R", "F", "B2", "L", "F2", "D'", "F2", "U'", "L2", "U'", "L2", "F2", "R2", "U2", "F2", "U"};
    cube.execute(shufflemoves);
    
    // Print the cube state post-scramble
    std::cout << "\nPost-scramble state:" << std::endl;
    std::cout << cube << std::endl;

    // Print the scramble sequence 
    std::cout << "Scramble sequence (string): " << cube.get_scramble_str() << std::endl;
    
    // Solution
    std::vector<std::string> solvemoves = {"U'", "F2", "U2", "R2", "F2", "L2", "U", "L2", "U", "F2", "D", "F2", "L'", "B2", "F'", "R'", "B'", "D2", "U", "L'", "R"};
    cube.execute(solvemoves);
    
    // Print the cube state post-solution
    std::cout << "\nPost-solution state:" << std::endl;
    std::cout << cube << std::endl;

    std::cout << "Solution algorithm (string): " << cube.get_algorithm_str() << std::endl;

    return 0;
}
