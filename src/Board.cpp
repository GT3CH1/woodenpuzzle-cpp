#include "Board.h"

using namespace puzzle;
int Board::width = 10;
int Board::height = 6;

Board::Board() {
    this->hash = 0;
    data = std::vector<char>();
    data.resize(60);
    std::fill(data.begin(), data.end(), '_');
    pieces = std::set<char>();
    pieces.clear();
    time_to_solve = 0;
}

Board::~Board() = default;

Board::Board(const Board &other) {
    hash = other.hash;
    data = std::vector<char>(other.data);
    time_to_solve = other.time_to_solve;
    pieces.clear();
    pieces = std::set<char>(other.pieces);
    set_thread_id(other.thread_id);
}

bool Board::piece_placed(char symbol) {
    return pieces.find(symbol) != pieces.end();
}

std::vector<char> Board::get_data() {
    return this->data;
}

bool Board::can_add_piece(int x, int y, PuzzlePiece piece) {
    if (x < 0 || x > 9 || y < 0 || y > 5 || this->piece_placed(piece.get_symbol())) {
        return false;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (piece.get_data().at(i * 5 + j) != '_') {
                try {
//                    char curr_data = this->data[(y + i) * 10 + (x + j)];
                    char curr_data = this->data.at((y + i) * 10 + (x + j));
                    if (curr_data == '\0')
                        continue;
                    if (curr_data != '_') {
                        return false;
                    }
                } catch (std::exception &e) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Board::add_piece(int x, int y, PuzzlePiece piece) {
    if (!this->can_add_piece(x, y, piece)) {
        return false;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (piece.get_data()[i * 5 + j] != '_')
                this->data[(y + i) * 10 + (x + j)] = piece.get_symbol();
        }
    }
    this->hash += piece.get_symbol() * 37 * ((x ^ 3) + (y ^ 3)) * 127;
    this->pieces.insert(piece.get_symbol());
    return true;
}


bool Board::is_invalid() {
    for (int y = 0; y < 6; y++) {
        bool found_piece = false;
        for (int x = 0; x < 10; x++) {
            char curr_data = this->data[y * 10 + x];
            if (curr_data != '_') {
                if (!found_piece)
                    found_piece = true;
                continue;
            }
            if (curr_data == '_' && found_piece)
                return true;
            else if (x == 0 && y == 0) {
                if (this->data[1] != '_' && this->data[10] != '_') {
                    return true;
                }
            } else if (x == 9 && y == 0) {
                if (this->data[8] != '_' && this->data[19] != '_')
                    return true;
            } else if (x == 0 && y == 5) {
                if (this->data[1] != '_' && this->data[10] != '_')
                    return true;
            } else if (x == 9 && y == 5) {
                if (this->data[58] != '_' && this->data[49] != '_')
                    return true;
            }
                // if 1<=x<9 and y == 0
            else if (x > 0 && x < 9 && y == 0) {
                if (this->data[y * 10 + x - 1] != '_' && this->data[y * 10 + x + 1] != '_' &&
                    this->data[(y + 1) * 10 + x] != '_')
                    return true;
            }
                // if 1<=x<9 and 1<=y<5
            else if (x > 0 && x < 9 && y > 0 && y < 5) {
                if (this->data[y * 10 + x - 1] != '_' && this->data[y * 10 + x + 1] != '_' &&
                    this->data[(y + 1) * 10 + x] != '_' && this->data[(y - 1) * 10 + x] != '_')
                    return true;
            }

                // if 1<=x<9 and y == 5
            else if (x > 0 && x < 9 && y == 5) {
                if (this->data[y * 10 + x - 1] != '_' && this->data[y * 10 + x + 1] != '_' &&
                    this->data[(y - 1) * 10 + x] != '_')
                    return true;
            }

        }
    }
//    // check corners if they are empty but have a piece next to them
//    if (this->data[0] == '_' && this->data[1] != '_' && this->data[10] != '_') {
//        return true;
//    }
//    if (this->data[9] == '_' && this->data[8] != '_' && this->data[19] != '_') {
//        return true;
//    }
//    if (this->data[50] == '_' && this->data[51] != '_' && this->data[40] != '_') {
//        return true;
//    }
//    if (this->data[59] == '_' && this->data[58] != '_' && this->data[49] != '_') {
//        return true;
//    }
    return false;
}


void Board::print_board() {
    // top border

    std::cout << get_pretty_data() << std::endl;
}

std::string Board::get_pretty_data() {
    std::string pretty_data;
    pretty_data += "Solution hash: " + std::to_string(hash) + "\n";
    pretty_data += "Generated by thread #" + std::to_string(thread_id) + "\n";
    // format time elapsed as .## seconds
    std::string time_elapsed = std::to_string((int(time_to_solve * 100)) / 100.0);
    // remove trailing zeros
    time_elapsed.erase(time_elapsed.find_last_not_of('0') + 1, std::string::npos);
    if(time_elapsed != "0.")
        pretty_data += "Time elapsed: " + time_elapsed + " seconds\n";
    std::string top_border = "+";
    for (int i = 0; i < puzzle::Board::width; i++) {
        top_border += "-";
    }
    top_border += "+";
    std::string row;
    for (int i = 0; i < puzzle::Board::height; i++) {
        row += "|";
        for (int j = 0; j < puzzle::Board::width; j++) {
            row += this->data[i * 10 + j];
        }
        row += "|\n";
    }
    pretty_data += top_border + "\n" + row + top_border + "\n";
    return pretty_data;
}

bool Board::operator==(const Board &other) const {
    return this->hash == other.hash;
}

bool Board::operator<(const Board &other) const {
    return this->hash < other.hash;
}

bool Board::is_solved() {
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 10; x++) {
            if (this->data[y * 10 + x] == '_') {
                return false;
            }
        }
    }
    return true;
}

Board &Board::operator=(const Board &other) {
    if (this == &other)
        return *this;
    this->hash = other.hash;
    for (int i = 0; i < 60; i++) {
        if (other.data[i])
            data[i] = other.data[i];
        else
            data[i] = '_';
    }
    this->pieces = std::set<char>(other.pieces);
    time_to_solve = other.time_to_solve;
    thread_id = other.thread_id;
    return *this;
}

double Board::get_time_to_solve() const {
    return time_to_solve;
}

void Board::set_time_to_solve(double time) {
    this->time_to_solve = time;
}

void Board::set_thread_id(int id) {
    thread_id = id;
}

int Board::get_thread_id() {
    return thread_id;
}
