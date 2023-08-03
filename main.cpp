#include "Cube.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>

const std::vector<std::string> SINGLE_MOVES = {"U", "U'", "U2", "D", "D'", "D2", 
                                               "R", "R'", "R2", "L", "L'", "L2", 
                                               "F", "F'", "F2", "B", "B'", "B2"};

const std::vector<std::string> FULL_ROTATIONS = {"x", "x'", "x2", "y", "y'", "y2"};

const std::vector<std::string> ORIENTATIONS = {"z", "z'", "z2"};

const std::vector<std::vector<std::string>> PERMUTATIONS = {
    // Permutes two edges: U face, bottom edge and right edge
    {"F'", "L'", "B'", "R'", "U'", "R", "U'", "B", "L", "F", "R", "U", "R'", "U"},
    
    // Permutes two edges: U face, bottom edge and left edge
    {"F", "R", "B", "L", "U", "L'", "U", "B'", "R'", "F'", "L'", "U'", "L", "U'"},
    
    // Permutes two corners: U face, bottom left and bottom right
    {"U2", "B", "U2", "B'", "R2", "F", "R'", "F'", "U2", "F'", "U2", "F", "R'"},
    
    // Permutes three corners: U face, bottom left and top left
    {"U2", "R", "U2", "R'", "F2", "L", "F'", "L'", "U2", "L'", "U2", "L", "F'"},
    
    // Permutes three centers: F face, top, right, bottom
    {"U'", "B2", "D2", "L'", "F2", "D2", "B2", "R'", "U'"},
    
    // Permutes three centers: F face, top, right, left
    {"U", "B2", "D2", "R", "F2", "D2", "B2", "L", "U"},
    
    // U face: bottom edge <-> right edge, bottom right corner <-> top right corner
    {"D'", "R'", "D", "R2", "U'", "R", "B2", "L", "U'", "L'", "B2", "U", "R2"},
    
    // U face: bottom edge <-> right edge, bottom right corner <-> left right corner
    {"D", "L", "D'", "L2", "U", "L'", "B2", "R'", "U", "R", "B2", "U'", "L2"},
    
    // U face: top edge <-> bottom edge, bottom left corner <-> top right corner
    {"R'", "U", "L'", "U2", "R", "U'", "L", "R'", "U", "L'", "U2", "R", "U'", "L", "U'"},
    
    // U face: top edge <-> bottom edge, bottom right corner <-> top left corner
    {"L", "U'", "R", "U2", "L'", "U", "R'", "L", "U'", "R", "U2", "L'", "U", "R'", "U"},
    
    // Permutes three corners: U face, bottom right, bottom left and top left
    {"F'", "U", "B", "U'", "F", "U", "B'", "U'"},
    
    // Permutes three corners: U face, bottom left, bottom right and top right
    {"F", "U'", "B'", "U", "F'", "U'", "B", "U"},
    
    // Permutes three edges: F face bottom, F face top, B face top
    {"L'", "U2", "L", "R'", "F2", "R"},
    
    // Permutes three edges: F face top, B face top, B face bottom
    {"R'", "U2", "R", "L'", "B2", "L"},
    
    // H permutation: U Face, swaps the edges horizontally and vertically
    {"M2", "U", "M2", "U2", "M2", "U", "M2"}
};

class Solver {
private:
    int population_size;
    int max_generations;
    int max_resets;
    int elitism_num;

    // Presuming these constants are somewhere defined in your program.
    // If not, they need definitions as well.
    const std::vector<std::string> SINGLE_MOVES;
    const std::vector<std::vector<std::string>> PERMUTATIONS;
    const std::vector<std::string> FULL_ROTATIONS;
    const std::vector<std::string> ORIENTATIONS;
    
    std::mt19937 rng;  // Mersenne twister random engine
    
    void copy(Cube& cube_to, const Cube& cube_from) {
        for (const auto& [faceName, face] : cube_from.faces) { // Assuming Cube::faces is public or Cube is a friend
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    cube_to.faces[faceName][i][j] = face[i][j];
                }
            }
        }
        cube_to.move_history = cube_from.move_history; // Assuming move_history is public or Cube is a friend
        cube_to.fitness = cube_from.fitness; // Assuming fitness is public or Cube is a friend
    }

    std::vector<std::string> rnd_single_move() {
        std::uniform_int_distribution<int> dist(0, SINGLE_MOVES.size() - 1);
        return { SINGLE_MOVES[dist(rng)] };
    }

    std::vector<std::string> rnd_permutation() {
        std::uniform_int_distribution<int> dist(0, PERMUTATIONS.size() - 1);
        return PERMUTATIONS[dist(rng)];
    }

    std::vector<std::string> rnd_full_rotation() {
        std::uniform_int_distribution<int> dist(0, FULL_ROTATIONS.size() - 1);
        return { FULL_ROTATIONS[dist(rng)] };
    }

    std::vector<std::string> rnd_orientation() {
        std::uniform_int_distribution<int> dist(0, ORIENTATIONS.size() - 1);
        return { ORIENTATIONS[dist(rng)] };
    }

public:
    Solver(int population_size, int max_generations, int max_resets, int elitism_num)
        : population_size(population_size), max_generations(max_generations),
          max_resets(max_resets), elitism_num(elitism_num), rng(std::random_device()()) {
    }

    // You can add more public functions or integrate this into your program
};







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
