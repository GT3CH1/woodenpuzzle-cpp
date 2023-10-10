#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H

#include <cstddef>
#include <vector>

namespace puzzle {
    /**
     * @brief Represents a generic puzzle piece.
     * @author GT3CH1
     */
    class PuzzlePiece {
    public:
        /**
         * @brief Construct a new Puzzle Piece object.
         * All puzzle available_pieces are assumed to fit within a 5x5 grid. The grid is initialized with the "empty" block,
         * which is represented by the underscore character.
         * @param symbol The symbol used to represent the piece.
         */
        explicit PuzzlePiece(char symbol);

        /**
         * Copy constructor
         * @param other The other PuzzlePiece to copy from.
         */
        PuzzlePiece(const PuzzlePiece &other);

        ~PuzzlePiece();

        /**
         * @brief Gets whether the piece is symmetrical.
         * @return True if the piece is symmetrical, false otherwise.
         */
        [[nodiscard]] bool is_symmetric() const;

        /**
         * @brief Gets whether the piece can be rotated.
         * @return True if the piece can be rotated, false otherwise.
         */
        [[nodiscard]] bool can_rotate() const;

        /**
         * @brief Gets the symbol used to represent the piece.
         * @return The symbol used to represent the piece.
         */
        [[nodiscard]] char get_symbol() const;

        /**
         * @brief Rotates the piece 90 degrees clockwise.
         * @return The rotated piece.
         */
        PuzzlePiece rotate();

        /**
         * @brief Flips the piece along the y-axis.
         * @return The flipped piece.
         */
        PuzzlePiece flip_horizontal();

        /**
         * Sets whether the piece has a block at the given row and column.
         * @param row The row to set.
         * @param col The column to set.
         */
        void set_block(int row, int col);

        /**
         * Returns the data of the piece.
         * @return
         */
        std::vector<char> get_data();

        /**
         * Pretty-prints the piece.
         */
        void print();

        /**
         * Checks whether the piece is equal to another piece by comparing their symbols.
         * @param other The other piece to compare to.
         * @return True if the available_pieces are equal, false otherwise.
         */
        bool operator==(PuzzlePiece &other) const;

        /**
         * Checks whether the piece is less than another piece by comparing their symbols.
         * @param other The other piece to compare to.
         * @return True if the piece is less than the other piece, false otherwise.
         */
        bool operator<(const PuzzlePiece &other) const;

    private:
        /**
         * The dimension of the piece.
         */
        int dimension = 5;

        /**
         * The symbol used to represent the piece.
         */
        char symbol;

        /**
         * The data of the piece.
         */
        std::vector<char> data;

        /**
         * Crops the piece so that the minimum bounding box is used and the piece begins at (0, 0).
         */
        void resize_shape();
    };
}
#endif
