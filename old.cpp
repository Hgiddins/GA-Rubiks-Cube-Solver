#include <string>
#include <unordered_map>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm> 
#include <iomanip>   
#include <sstream>


const std::string GREEN = "G";
const std::string ORANGE = "O";
const std::string RED = "R";
const std::string WHITE = "W";
const std::string YELLOW = "Y";
const std::string BLUE = "B";

const std::string FRONT = "FRONT";
const std::string LEFT = "LEFT";
const std::string BACK = "BACK";
const std::string RIGHT = "RIGHT";
const std::string TOP = "TOP";
const std::string BOTTOM = "BOTTOM";

using Rotation = std::pair<int, int>;
const Rotation CLOCKWISE = {1, 0};
const Rotation COUNTERCLOCKWISE = {0, 1};

class Cube {
private:
    using Face = std::array<std::array<std::string, 3>, 3>;
    std::unordered_map<std::string, Face> faces;

    using MoveFunction = void (Cube::*)();
    std::unordered_map<std::string, MoveFunction> moves_lookup;

    std::vector<std::vector<std::string>> move_history;
    int fitness = 0;  // less is better, it means 0 misplaced sticker

    const int CLOCKWISE = 1;
    const int COUNTERCLOCKWISE = -1;

public:

    // Constructor initialises faces and the move references in moves_lookup
    Cube() {
        // Initialize all faces to their respective colors
        faces[FRONT] = {{{GREEN, GREEN, GREEN}, {GREEN, GREEN, GREEN}, {GREEN, GREEN, GREEN}}};
        faces[LEFT] = {{{ORANGE, ORANGE, ORANGE}, {ORANGE, ORANGE, ORANGE}, {ORANGE, ORANGE, ORANGE}}};
        faces[RIGHT] = {{{RED, RED, RED}, {RED, RED, RED}, {RED, RED, RED}}};
        faces[TOP] = {{{WHITE, WHITE, WHITE}, {WHITE, WHITE, WHITE}, {WHITE, WHITE, WHITE}}};
        faces[BOTTOM] = {{{YELLOW, YELLOW, YELLOW}, {YELLOW, YELLOW, YELLOW}, {YELLOW, YELLOW, YELLOW}}};
        faces[BACK] = {{{BLUE, BLUE, BLUE}, {BLUE, BLUE, BLUE}, {BLUE, BLUE, BLUE}}};

         // Horizontal moves
        moves_lookup["D"] = &Cube::D;
        moves_lookup["D'"] = &Cube::D_prime;
        moves_lookup["D2"] = &Cube::D2;

        moves_lookup["E"] = &Cube::E;
        moves_lookup["E'"] = &Cube::E_prime;
        moves_lookup["E2"] = &Cube::E2;

        moves_lookup["U"] = &Cube::U;
        moves_lookup["U'"] = &Cube::U_prime;
        moves_lookup["U2"] = &Cube::U2;

        // Vertical moves
        moves_lookup["L"] = &Cube::L;
        moves_lookup["L'"] = &Cube::L_prime;
        moves_lookup["L2"] = &Cube::L2;

        moves_lookup["R"] = &Cube::R;
        moves_lookup["R'"] = &Cube::R_prime;
        moves_lookup["R2"] = &Cube::R2;

        moves_lookup["M"] = &Cube::M;
        moves_lookup["M'"] = &Cube::M_prime;
        moves_lookup["M2"] = &Cube::M2;

        // Z moves
        moves_lookup["B"] = &Cube::B;
        moves_lookup["B'"] = &Cube::B_prime;
        moves_lookup["B2"] = &Cube::B2;

        moves_lookup["F"] = &Cube::F;
        moves_lookup["F'"] = &Cube::F_prime;
        moves_lookup["F2"] = &Cube::F2;

        moves_lookup["S"] = &Cube::S;
        moves_lookup["S'"] = &Cube::S_prime;
        moves_lookup["S2"] = &Cube::S2;

        // Full rotations
        moves_lookup["x"] = &Cube::x_full;
        moves_lookup["x'"] = &Cube::x_prime_full;
        moves_lookup["x2"] = &Cube::x2_full;

        moves_lookup["y"] = &Cube::y_full;
        moves_lookup["y'"] = &Cube::y_prime_full;
        moves_lookup["y2"] = &Cube::y2_full;

        moves_lookup["z"] = &Cube::z_full;
        moves_lookup["z'"] = &Cube::z_prime_full;
        moves_lookup["z2"] = &Cube::z2_full;
        
        
    }
    
// ---------------------------------------------------------------------------
// Core Functions
// ---------------------------------------------------------------------------

    void execute(const std::vector<std::string>& moves) {
        for (const auto& m : moves) {
            if (moves_lookup.find(m) != moves_lookup.end()) {
                (this->*moves_lookup[m])(); // Call the move function using a member function pointer
            } else {
                // Handle invalid move here, if necessary
                // e.g., std::cerr << "Invalid move: " << m << std::endl;
            }
        }

        move_history.push_back(moves);
        calculate_fitness();
    }

    void calculate_fitness() {
        int misplaced_stickers = 0;

        for (const auto& face_pair : faces) {
            const Face& face = face_pair.second;
            // centers are fixed in a Rubik cube
            std::string center = face[1][1];

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (face[i][j] != center) {
                        misplaced_stickers++;
                    }
                }
            }
        }

    fitness = misplaced_stickers;
    }

    bool is_solved() const {
        return fitness == 0;
    }



    // Rotate a face 90 degrees
    void rotate90(Face& face, int direction) {
        Face temp = face;
        if (direction == CLOCKWISE) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    face[j][2 - i] = temp[i][j];
                }
            }
        } else { // COUNTERCLOCKWISE
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    face[2 - j][i] = temp[i][j];
                }
            }
        }
    }
// ---------------------------------------------------------------------------
// X Axis movements - D, E and U
// ---------------------------------------------------------------------------

    void D() {
        rotate90(faces["BOTTOM"], CLOCKWISE);
        swap_x({"FRONT", 2}, {"RIGHT", 2}, {"BACK", 2}, {"LEFT", 2});
    }

    void D_prime() {
        rotate90(faces["BOTTOM"], COUNTERCLOCKWISE);
        swap_x({"FRONT", 2}, {"LEFT", 2}, {"BACK", 2}, {"RIGHT", 2});
    }

    void D2() {
        D();
        D();
    }

    void E() {
        swap_x({"FRONT", 1}, {"RIGHT", 1}, {"BACK", 1}, {"LEFT", 1});
    }

    void E_prime() {
        swap_x({"FRONT", 1}, {"LEFT", 1}, {"BACK", 1}, {"RIGHT", 1});
    }

    void E2() {
        E();
        E();
    }

    void U() {
        rotate90(faces["TOP"], CLOCKWISE);
        swap_x({"FRONT", 0}, {"LEFT", 0}, {"BACK", 0}, {"RIGHT", 0});
    }

    void U_prime() {
        rotate90(faces["TOP"], COUNTERCLOCKWISE);
        swap_x({"FRONT", 0}, {"RIGHT", 0}, {"BACK", 0}, {"LEFT", 0});
    }

    void U2() {
        U();
        U();
    }

    void swap_x(const std::pair<std::string, int>& t1, 
            const std::pair<std::string, int>& t2, 
            const std::pair<std::string, int>& t3, 
            const std::pair<std::string, int>& t4) {
        // Create a backup array
        std::array<std::string, 3> backup;
        
        // Perform the copying/swapping operations
        copy_stickers(backup, faces[t4.first][t4.second]);
        copy_stickers(faces[t4.first][t4.second], faces[t3.first][t3.second]);
        copy_stickers(faces[t3.first][t3.second], faces[t2.first][t2.second]);
        copy_stickers(faces[t2.first][t2.second], faces[t1.first][t1.second]);
        copy_stickers(faces[t1.first][t1.second], backup);
    }

    void copy_stickers(std::array<std::string, 3>& destination, const std::array<std::string, 3>& origin) {
            destination[0] = origin[0];
            destination[1] = origin[1];
            destination[2] = origin[2];
        }

// ---------------------------------------------------------------------------
// Y Axis movements - L, M and R
// ---------------------------------------------------------------------------

    void L() {
        rotate90(faces["LEFT"], CLOCKWISE);
        swap_y({"BOTTOM", 0, true}, {"BACK", 2, true}, {"TOP", 0, false}, {"FRONT", 0, false});
    }

    void L_prime() {
        rotate90(faces["LEFT"], COUNTERCLOCKWISE);
        swap_y({"BOTTOM", 0, false}, {"FRONT", 0, false}, {"TOP", 0, true}, {"BACK", 2, true});
    }

    void L2() {
        L();
        L();
    }

    void M() {
        swap_y({"BOTTOM", 1, true}, {"BACK", 1, true}, {"TOP", 1, false}, {"FRONT", 1, false});
    }

    void M_prime() {
        swap_y({"BOTTOM", 1, false}, {"FRONT", 1, false}, {"TOP", 1, true}, {"BACK", 1, true});
    }

    void M2() {
        M();
        M();
    }

    void R() {
        rotate90(faces["RIGHT"], CLOCKWISE);
        swap_y({"BOTTOM", 2, false}, {"FRONT", 2, false}, {"TOP", 2, true}, {"BACK", 0, true});
    }

    void R_prime() {
        rotate90(faces["RIGHT"], COUNTERCLOCKWISE);
        swap_y({"BOTTOM", 2, true}, {"BACK", 0, true}, {"TOP", 2, false}, {"FRONT", 2, false});
    }

    void R2() {
        R();
        R();
    }

void swap_y(const std::tuple<std::string, int, bool>& t1, 
            const std::tuple<std::string, int, bool>& t2, 
            const std::tuple<std::string, int, bool>& t3, 
            const std::tuple<std::string, int, bool>& t4) {
    
    std::array<std::string, 3> backup;
    
    // Fetch column and possibly flip it
    if (std::get<2>(t1)) {
        for (int i = 0; i < 3; ++i) {
            backup[2-i] = faces[std::get<0>(t1)][i][std::get<1>(t1)];
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            backup[i] = faces[std::get<0>(t1)][i][std::get<1>(t1)];
        }
    }
    
    // Swap columns
    if (std::get<2>(t4)) {
        for (int i = 0; i < 3; ++i) {
            faces[std::get<0>(t1)][i][std::get<1>(t1)] = faces[std::get<0>(t4)][2-i][std::get<1>(t4)];
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            faces[std::get<0>(t1)][i][std::get<1>(t1)] = faces[std::get<0>(t4)][i][std::get<1>(t4)];
        }
    }

    if (std::get<2>(t3)) {
        for (int i = 0; i < 3; ++i) {
            faces[std::get<0>(t4)][i][std::get<1>(t4)] = faces[std::get<0>(t3)][2-i][std::get<1>(t3)];
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            faces[std::get<0>(t4)][i][std::get<1>(t4)] = faces[std::get<0>(t3)][i][std::get<1>(t3)];
        }
    }

    if (std::get<2>(t2)) {
        for (int i = 0; i < 3; ++i) {
            faces[std::get<0>(t3)][i][std::get<1>(t3)] = faces[std::get<0>(t2)][2-i][std::get<1>(t2)];
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            faces[std::get<0>(t3)][i][std::get<1>(t3)] = faces[std::get<0>(t2)][i][std::get<1>(t2)];
        }
    }
    
    // Assign backup to the last face
    for (int i = 0; i < 3; ++i) {
        faces[std::get<0>(t2)][i][std::get<1>(t2)] = backup[i];
    }
}

    void copy_stickers_flip(std::array<std::string, 3>& destination, const std::array<std::string, 3>& origin) {
        destination[0] = origin[2];
        destination[1] = origin[1];
        destination[2] = origin[0];
    }
// ---------------------------------------------------------------------------
// Z Axis movements - B and F
// ---------------------------------------------------------------------------
    
    void B() {
        rotate90(faces["BACK"], CLOCKWISE);
        swap_z({"BOTTOM", 2, true}, {"RIGHT", 2, false}, {"TOP", 0, true}, {"LEFT", 0, false});
    }

    void B_prime() {
        rotate90(faces["BACK"], COUNTERCLOCKWISE);
        swap_z({"BOTTOM", 2, false}, {"LEFT", 0, true}, {"TOP", 0, false}, {"RIGHT", 2, true});
    }

    void B2() {
        B();
        B();
    }

    void F() {
        rotate90(faces["FRONT"], CLOCKWISE);
        swap_z({"BOTTOM", 0, false}, {"LEFT", 2, true}, {"TOP", 2, false}, {"RIGHT", 0, true});
    }

    void F_prime() {
        rotate90(faces["FRONT"], COUNTERCLOCKWISE);
        swap_z({"BOTTOM", 0, true}, {"RIGHT", 0, false}, {"TOP", 2, true}, {"LEFT", 2, false});
    }

    void F2() {
        F();
        F();
    }

    void S() {
        swap_z({"BOTTOM", 1, false}, {"LEFT", 1, true}, {"TOP", 1, false}, {"RIGHT", 1, true});
    }

    void S_prime() {
        swap_z({"BOTTOM", 1, true}, {"RIGHT", 1, false}, {"TOP", 1, true}, {"LEFT", 1, false});
    }

    void S2() {
        S();
        S();
    }

void swap_z(const std::tuple<std::string, int, bool>& t1,
            const std::tuple<std::string, int, bool>& t2,
            const std::tuple<std::string, int, bool>& t3,
            const std::tuple<std::string, int, bool>& t4) {
    std::array<std::string, 3> backup;

    auto extract_data = [&](const std::tuple<std::string, int, bool>& t) -> std::array<std::string, 3> {
        auto& face = faces[std::get<0>(t)];
        int index = std::get<1>(t);
        std::array<std::string, 3> values;

        if(std::get<0>(t) == "LEFT" || std::get<0>(t) == "RIGHT") {
            values[0] = face[0][index];
            values[1] = face[1][index];
            values[2] = face[2][index];
        } else {
            values = face[index];
        }

        if (std::get<2>(t)) { // If flip is needed
            std::reverse(values.begin(), values.end());
        }
        return values;
    };

    auto set_data = [&](const std::tuple<std::string, int, bool>& t, const std::array<std::string, 3>& values) {
        auto& face = faces[std::get<0>(t)];
        int index = std::get<1>(t);
        std::array<std::string, 3> set_values = values;

        if(std::get<0>(t) == "LEFT" || std::get<0>(t) == "RIGHT") {
            face[0][index] = set_values[0];
            face[1][index] = set_values[1];
            face[2][index] = set_values[2];
        } else {
            face[index] = set_values;
        }
    };

    // Backup t4
    backup = extract_data(t4);

    // t3 to t4
    set_data(t4, extract_data(t3));

    // t2 to t3
    set_data(t3, extract_data(t2));

    // t1 to t2
    set_data(t2, extract_data(t1));

    // backup to t1
    set_data(t1, backup);
}

// ---------------------------------------------------------------------------
// Full Rotations
// ---------------------------------------------------------------------------
    void x_full() {
        L_prime();
        M_prime();
        R();
    }

    void x_prime_full() {
        L();
        M();
        R_prime();
    }

    void x2_full() {
        x_full();
        x_full();
    }

    void y_full() {
        U();
        E_prime();
        D_prime();
    }

    void y_prime_full() {
        U_prime();
        E();
        D();
    }

    void y2_full() {
        y_full();
        y_full();
    }

    void z_full() {
        F();
        S();
        B_prime();
    }

    void z_prime_full() {
        F_prime();
        S_prime();
        B();
    }

    void z2_full() {
        z_full();
        z_full();
    }


// ---------------------------------------------------------------------------
// Utilities
// ---------------------------------------------------------------------------

    std::string get_face_as_str(const std::string& face) {
        const Face& m = faces[face];
        std::ostringstream oss;
        oss << m[0][0] << " " << m[0][1] << " " << m[0][2] << " - "
            << m[1][0] << " " << m[1][1] << " " << m[1][2] << " - "
            << m[2][0] << " " << m[2][1] << " " << m[2][2];
        return oss.str();
    }

    std::vector<std::string> get_scramble() const {
        return move_history[0];
    }

    std::string get_scramble_str() const {
        return join(get_scramble(), " ");
    }

    std::vector<std::string> get_algorithm() const {
        std::vector<std::string> flat_list;
        for (size_t i = 1; i < move_history.size(); ++i) {
            for (const auto& item : move_history[i]) {
                flat_list.push_back(item);
            }
        }
        return flat_list;
    }

    std::string get_algorithm_str() const {
        return join(get_algorithm(), " ");
    }

    friend std::ostream& operator<<(std::ostream& os, const Cube& cube) {
        os << "Scramble: " << cube.get_scramble_str() << "\n";
        os << "Algorithm: " << cube.get_algorithm_str() << "\n";
        
        std::vector<std::pair<std::string, Face>> faces_sorted(cube.faces.begin(), cube.faces.end());
        std::sort(faces_sorted.begin(), faces_sorted.end());
        
        for (const auto& pair : faces_sorted) {
            std::string face_name = pair.first;
            const Face& face = pair.second;
            os << std::setw(8) << std::left << (face_name + ":") << face[0][0] << " " << face[0][1] << " " << face[0][2] << "\n";
            os << std::setw(8) << std::left << "" << face[1][0] << " " << face[1][1] << " " << face[1][2] << "\n";
            os << std::setw(8) << std::left << "" << face[2][0] << " " << face[2][1] << " " << face[2][2] << "\n";
        }
        
        return os;
    }

    static std::string join(const std::vector<std::string>& vec, const std::string& delimiter) {
        std::ostringstream oss;
        for (size_t i = 0; i < vec.size(); ++i) {
            oss << vec[i];
            if (i < vec.size() - 1) oss << delimiter;
        }
        return oss.str();
    }
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