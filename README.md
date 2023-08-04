# Rubik's Cube Genetic Solver

This project implements a genetic algorithm to solve a scrambled Rubik's Cube. The core logic revolves around Cube permutations, mutations, and the fitness of each candidate solution.

## Features
- **Evolutionary Mechanics**: The algorithm simulates evolution through generations of possible solutions to the scrambled state, refining solutions with each generation.
- **Dynamic Mutation Rate**: The mutation rate is adjusted based on the progress of the solution, allowing for dynamic responses to stagnation.
- **Multithreading**: The algorithm utilizes multiple threads to speed up the solving process, distributing the evolution and mutation tasks across different threads.

## How It Works

1. **Initialization**:
    - The population of `Cube` objects is initialized, each representing a potential solution to the scramble.
    - Each cube starts with a random series of moves, on top of the scramble.

2. **Fitness Evaluation**:
    - Fitness is determined by the number of stickers that are out of place. A lower fitness score is better.

3. **Evolution and Mutation**:
    - The algorithm evolves solutions through a set of predetermined permutations. A cube's move sequence may be altered through:
        - A random permutation from the predefined set.
        - A single random move.
        - A full cube rotation.
        - An orientation change.
    - If a solution has not improved over a set number of generations (stagnation), the mutation rate increases to try and find a better solution.

4. **Checking for Solutions**:
    - After each generation, the cubes are checked for a solution (a fitness of 0).
    - If a solution is found, the algorithm prints the solution and stops.

5. **Reset Mechanism**:
    - If the algorithm doesn't find a solution within the maximum number of generations, it resets and starts over. This process repeats for a set number of times.


## Usage
To use the solver:
1. Compile the code.
2. Execute the binary.
3. By default, a hardcoded scramble sequence is used. You can replace this with your desired scramble sequence.
4. If a solution is found, it will be printed on the console. Otherwise, a message indicating the failure to find a solution will be shown.

## Sample Output

**World: 1**

- Generation: 1   Incorrect stickers: 35
- Generation: 2   Incorrect stickers: 33
- Generation: 3   Incorrect stickers: 30
- Generation: 4   Incorrect stickers: 28
- Generation: 5   Incorrect stickers: 27
- Generation: 6   Incorrect stickers: 24
- Generation: 7   Incorrect stickers: 22
- Generation: 8   Incorrect stickers: 21
- Generation: 9   Incorrect stickers: 17
- Generation: 10  Incorrect stickers: 16
- Generation: 11  Incorrect stickers: 12
- Generation: 12  Incorrect stickers: 12
- Generation: 13  Incorrect stickers: 8
- Generation: 14  Incorrect stickers: 8
- Generation: 15  Incorrect stickers: 6
- Generation: 16  Incorrect stickers: 6
- Generation: 17  Incorrect stickers: 6
- Generation: 18  Incorrect stickers: 4
- Generation: 19  Incorrect stickers: 4
- Generation: 20  Incorrect stickers: 4
- Generation: 21  Incorrect stickers: 3
- Generation: 22  Incorrect stickers: 3
- Generation: 23  Incorrect stickers: 3
- Generation: 24  Incorrect stickers: 3
- Generation: 25  Incorrect stickers: 3
- Generation: 26  Incorrect stickers: 3
- Generation: 27  Incorrect stickers: 3
- Generation: 28  Incorrect stickers: 3
- Generation: 29  Incorrect stickers: 3
- Generation: 30  Incorrect stickers: 3
- Generation: 31  Incorrect stickers: 3
- Generation: 32  Incorrect stickers: 0

---------------------------------------


**SOLUTION FOUND**


**World: 1 - Generation: 32**

**Scramble**: 
D2 B' D' L2 F' U B D U2 B2 R F2 D2 L D2 B2 R' B2 D2


**Solution**: 
F L D' R' D R2 U' R B2 L U' L' B2 U R2 F U' B' U F' U' B U y' F' U B U' F U B' U' y z R' U L' U2 R U' L R' U L' U2 R U' L U' z F U' B' U F' U' B U U' B2 D2 L' F2 D2 B2 R' U' D L D' L2 U L' B2 R' U R B2 U' L2 z U B2 D2 R F2 D2 B2 L U x F R B L U L' U B' R' F' L' U' L U' z x' F U' B' U F' U' B U D' R' D R2 U' R B2 L U' L' B2 U R2 D L D' L2 U L' B2 R' U R B2 U' L2 F' L' B' R' U' R U' B L F R U R' U x U' B2 D2 L' F2 D2 B2 R' U' z' U B2 D2 R F2 D2 B2 L U z' L' U2 L R' F2 R z' U B2 D2 R F2 D2 B2 L U y' M2 U M2 U2 M2 U M2 D' R' D R2 U' R B2 L U' L' B2 U R2

**Moves**: 298
**Time taken**: 2.00 seconds
