#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H

#include <cstddef>

namespace puzzle {
    class PuzzlePiece {
    public:
        PuzzlePiece(char symbol);

        PuzzlePiece(const PuzzlePiece &other);

        ~PuzzlePiece();

        bool is_symmetric() const;

        bool can_rotate() const;

        char get_symbol() const;

        PuzzlePiece rotate();

        PuzzlePiece flip_horizontal();

        void set_block(int row, int col);

        char *get_data();

        void print();

        bool operator==(PuzzlePiece &other);

        bool operator<(const PuzzlePiece &other) const;

        size_t operator()(const PuzzlePiece &other) const;

    private:
        int dimension = 5;
        char symbol;
        char data[25];

        void resize_shape();
    };
}
#endif
