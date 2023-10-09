#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H

#include <cstddef>
#include <vector>

namespace puzzle {
    class PuzzlePiece {
    public:
        explicit PuzzlePiece(char symbol);

        PuzzlePiece(const PuzzlePiece &other);

        ~PuzzlePiece();

        [[nodiscard]] bool is_symmetric() const;

        [[nodiscard]] bool can_rotate() const;

        [[nodiscard]] char get_symbol() const;

        PuzzlePiece rotate();

        PuzzlePiece flip_horizontal();

        void set_block(int row, int col);

        std::vector<char> get_data();

        void print();

        bool operator==(PuzzlePiece &other) const;

        bool operator<(const PuzzlePiece &other) const;

    private:
        int dimension = 5;
        char symbol;
        std::vector<char> data;

        void resize_shape();
    };
}
#endif
