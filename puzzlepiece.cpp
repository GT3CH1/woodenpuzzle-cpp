#include "puzzlepiece.h"
#include <iostream>

using namespace puzzle;

PuzzlePiece::PuzzlePiece(char symbol) {
    this->symbol = symbol;
    this->data = new char[25];
    for (int i = 0; i < 25; i++) {
        this->data[i] = '_';
    }
}

PuzzlePiece::~PuzzlePiece() = default;

PuzzlePiece::PuzzlePiece(const PuzzlePiece &other) {
    this->symbol = other.symbol;
    this->data = new char[25];
    for (int i = 0; i < 25; i++) {
        this->data[i] = other.data[i];
    }
}

bool PuzzlePiece::is_symmetric() const {
    return this->symbol == 'T' || this->symbol == 'P' || this->symbol == '2' || this->symbol == 'u' ||
           this->symbol == 'B';
}

bool PuzzlePiece::can_rotate() const {
    return this->symbol != 'P';
}

char PuzzlePiece::get_symbol() const {
    return this->symbol;
}

PuzzlePiece PuzzlePiece::rotate() {
    PuzzlePiece copy(*this);
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            // copy.data[i][j] = this->data[dimension - j - 1][i];
            copy.data[i * dimension + j] = this->data[(dimension - j - 1) * dimension + i];
        }
    }
    copy.resize_shape();
    return copy;
}

void PuzzlePiece::resize_shape() {
    bool can_move = true;
    while (can_move) {
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                if (this->data[i * dimension + j] != '_') {
                    can_move = false;
                    break;
                }
            }
            // check if row is empty
            if (can_move) {
                for (int k = i; k < dimension - 1; k++) {
                    for (int j = 0; j < dimension; j++) {
                        this->data[k * dimension + j] = this->data[(k + 1) * dimension + j];
                    }
                }
                for (int j = 0; j < dimension; j++) {
                    this->data[(dimension - 1) * dimension + j] = '_';
                }
            }
        }
    }
    can_move = true;
    while (can_move) {
        for (int i = 0; i < dimension; i++) {
            if (this->data[i * dimension] != '_') {
                can_move = false;
                break;
            }
        }
        if (can_move) {
            for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension - 1; j++) {
                    this->data[i * dimension + j] = this->data[i * dimension + j + 1];
                }
                this->data[i * dimension + dimension - 1] = '_';
            }
        }
    }
}

PuzzlePiece PuzzlePiece::flip_horizontal() {
    PuzzlePiece copy(*this);
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            // copy.data[i][j] = this->data[i][dimension - j - 1];
            copy.data[i * dimension + j] = this->data[i * dimension + dimension - j - 1];
        }
    }
    copy.resize_shape();
    return copy;
}

void PuzzlePiece::set_block(int row, int col) {
    this->data[col * 5 + row] = this->symbol;
}

char *PuzzlePiece::get_data() {
    return this->data;
}

void PuzzlePiece::print() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            std::cout << this->data[i * dimension + j];
        }
        std::cout << std::endl;
    }
}

bool PuzzlePiece::operator==(PuzzlePiece &other) const {
    return this->get_symbol() == other.get_symbol();
}

bool PuzzlePiece::operator<(const PuzzlePiece &other) const {
    return symbol < other.symbol;
}
