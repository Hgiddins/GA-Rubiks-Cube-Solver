#include "Cube.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

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
    int last_printed_world = -1;
    int population_size;
    int max_generations;
    int max_resets;
    int elitism_num;
    
    // Additional utility functions
    Cube copyCube(const Cube& cube_from) {
        Cube cube_to;
        cube_to.faces = cube_from.faces;
        cube_to.move_history = cube_from.move_history;
        cube_to.fitness = cube_from.fitness;
        return cube_to;
    }

    std::string rnd_single_move() {
        return SINGLE_MOVES[rand() % SINGLE_MOVES.size()];
    }

    std::vector<std::string> rnd_permutation() {
        return PERMUTATIONS[rand() % PERMUTATIONS.size()];
    }

    std::string rnd_full_rotation() {
        return FULL_ROTATIONS[rand() % FULL_ROTATIONS.size()];
    }

    std::string rnd_orientation() {
        return ORIENTATIONS[rand() % ORIENTATIONS.size()];
    }

public:
    Solver(int population_size, int max_generations, int max_resets, int elitism_num)
        : population_size(population_size), max_generations(max_generations),
          max_resets(max_resets), elitism_num(elitism_num) {}

    void solve(const std::vector<std::string>& scramble, bool verbose = false) {
        time_t start_time = time(nullptr);

        if (verbose) {
            std::cout << "Starting..." << std::endl;
        }

        for (int r = 0; r < max_resets; ++r) {
            // Initialize population
            std::vector<Cube> cubes;
            for (int i = 0; i < population_size; ++i) {
                Cube cube;
                cube.execute(scramble);
                cube.execute({rnd_single_move()});
                cube.execute({rnd_single_move()});
                cubes.push_back(cube);
            }

            for (int g = 0; g < max_generations; ++g) {
                // Sort by fitness
                std::sort(cubes.begin(), cubes.end());

                if (verbose) {
                    if (last_printed_world != r + 1) { // Only print when the world changes
                        std::cout << "World: " << r+1 << std::endl;
                        last_printed_world = r + 1;
                    }
                    std::cout << "\tGeneration: " << g + 1 
                            << "\tIncorrect stickers: " << cubes[0].fitness << std::endl;
                }


                for (int i = 0; i < cubes.size(); ++i) {
                    if (cubes[i].fitness == 0) {
                        std::cout << "" << std::endl;
                        std::cout << "====================================" << std::endl;
                        std::cout << "SOLUTION FOUND" << std::endl;
                        std::cout << "====================================" << std::endl;
                        std::cout << "" << std::endl;
                        std::cout << "World: " << r + 1 << " - Generation: " << g + 1 << std::endl;
                        std::cout << "" << std::endl;
                        std::cout << "Scramble: " << cubes[i].get_scramble_str() << std::endl;
                        std::cout << "" << std::endl;
                        std::cout << "Solution: " << cubes[i].get_algorithm_str() << std::endl;
                        std::cout << "" << std::endl;
                        std::cout << "Moves: " << cubes[i].get_algorithm().size() << std::endl;
                        std::cout << "Time taken: " << difftime(time(nullptr), start_time) << " seconds" << std::endl;
                        return;
                    }

                    if (i > elitism_num) {
                        cubes[i] = copyCube(cubes[rand() % (elitism_num + 1)]);
                        int evolution_type = rand() % 6;
                        switch (evolution_type) {
                            // Your evolution types translated to C++ switch-case
                            // You may need to adjust as per actual behavior
                            case 0:
                                cubes[i].execute(rnd_permutation());
                                break;
                            case 1:
                                cubes[i].execute(rnd_permutation());
                                cubes[i].execute(rnd_permutation());
                                break;
                            case 2:
                                cubes[i].execute({rnd_full_rotation()});
                                cubes[i].execute(rnd_permutation());
                                break;
                            case 3:
                                cubes[i].execute({rnd_orientation()});
                                cubes[i].execute(rnd_permutation());
                                break;
                            case 4:
                                cubes[i].execute({rnd_full_rotation()});
                                cubes[i].execute({rnd_orientation()});
                                cubes[i].execute(rnd_permutation());
                                break;
                            case 5:
                                cubes[i].execute({rnd_orientation()});
                                cubes[i].execute({rnd_full_rotation()});
                                cubes[i].execute(rnd_permutation());
                                break;
                            default:
                                break;
                        }
                    }
                }
                
                }
                if (verbose) {
                    std::cout << "------------------------------------" << std::endl;
                    std::cout << "Resetting the world" << std::endl;
            }
        }
        std::cout << "Solution not found" << std::endl;
        std::cout << "Time taken: " << difftime(time(nullptr), start_time) << " seconds" << std::endl;
    }
};

int main() {
    srand(time(nullptr));
    // Remove the comment when you use the desired scramble sequence
    // std::vector<std::string> scramble = {"R'", "U'", "L2", "B2", "U2", "F", "L2", "B'", "L'", "B", "D", "R", "B", "F2", "L", "F", "R'", "B2", "F'", "L", "B'", "D", "B2", "R2", "D'", "U", "B2", "F'", "D", "R2"};
    // std::vector<std::string> scramble = {"U2", "B'", "F", "L", "B'", "F2", "D'", "U", "B2", "R'", "U", "B'", "F", "U", "F'", "R'", "U2", "L'", "R'", "D", "F2", "R'", "F'", "D2", "L'", "R2", "B'", "D", "L", "U2"};
    std::vector<std::string> scramble = {"B'", "R'", "U2", "B'", "F", "D2", "R2", "B", "F'", "L2", "R'", "B2", "D2", "L2", "F'", "U", "L", "B2", "D", "F", "L'", "F", "R", "B2", "D'", "U'", "B'", "L'", "B'", "F2"};
    // std::vector<std::string> scramble = {"D'", "B2", "D2", "L2", "U'", "L", "R'", "F", "L2", "R2", "U'", "L2", "B'", "L", "D'", "B2", "R2", "B'", "R", "F", "U2", "R", "B2", "F'", "L'", "B2", "L2", "R", "F2", "L'"};

    int population_size = 500;
    int max_generations = 300;
    int max_resets = 10;
    int elitism_num = 50;

    Solver solver(population_size, max_generations, max_resets, elitism_num);
    // Uncomment the loop if you want to run the solver multiple times
    // for (int i = 0; i < 5; ++i) {
    //     solver.solve(scramble, false);
    // }
    solver.solve(scramble, true);

    return 0;
}

