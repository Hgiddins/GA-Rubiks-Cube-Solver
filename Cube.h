#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <array>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

class Solver;

class Cube {
public:
    friend class Solver;
    using Face = std::array<std::array<std::string, 3>, 3>;
    std::unordered_map<std::string, Face> faces;

    using MoveFunction = void (Cube::*)();
    std::unordered_map<std::string, MoveFunction> moves_lookup;
    std::vector<std::vector<std::string>> move_history;
    int fitness = 0;

    const int CLOCKWISE = 1;
    const int COUNTERCLOCKWISE = -1;

    void rotate90(std::array<std::array<std::string, 3>, 3>& face, int direction);
    void copy_stickers(std::array<std::string, 3>& destination, const std::array<std::string, 3>& origin);
    void copy_stickers_flip(std::array<std::string, 3>& destination, const std::array<std::string, 3>& origin);
    

    Cube();

    void execute(const std::vector<std::string>& moves);
    void calculate_fitness();
    bool is_solved() const;

    // X Axis movements
    void D();
    void D_prime();
    void D2();
    void E();
    void E_prime();
    void E2();
    void U();
    void U_prime();
    void U2();
    void swap_x(const std::pair<std::string, int>& t1, 
               const std::pair<std::string, int>& t2, 
               const std::pair<std::string, int>& t3, 
               const std::pair<std::string, int>& t4);

    // Y Axis movements
    void L();
    void L_prime();
    void L2();
    void M();
    void M_prime();
    void M2();
    void R();
    void R_prime();
    void R2();
    void swap_y(const std::tuple<std::string, int, bool>& t1, 
                const std::tuple<std::string, int, bool>& t2, 
                const std::tuple<std::string, int, bool>& t3, 
                const std::tuple<std::string, int, bool>& t4);

    // Z Axis movements
    void B();
    void B_prime();
    void B2();
    void F();
    void F_prime();
    void F2();
    void S();
    void S_prime();
    void S2();
    void swap_z(const std::tuple<std::string, int, bool>& t1, 
                const std::tuple<std::string, int, bool>& t2, 
                const std::tuple<std::string, int, bool>& t3, 
                const std::tuple<std::string, int, bool>& t4);
    
    // Full Rotations
    void x_full();
    void x_prime_full();
    void x2_full();
    void y_full();
    void y_prime_full();
    void y2_full();
    void z_full();
    void z_prime_full();
    void z2_full();

    // Additional methods
    std::string get_face_as_str(const std::string& face) const;
    std::vector<std::string> get_scramble() const;
    std::string get_scramble_str() const;
    std::vector<std::string> get_algorithm() const;
    std::string get_algorithm_str() const;
    static std::string join(const std::vector<std::string>& vec, const std::string& delimiter);

    // Overloaded operators
    friend std::ostream& operator<<(std::ostream& os, const Cube& cube);
};
