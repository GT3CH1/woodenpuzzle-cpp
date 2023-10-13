//
// Created by Pease, Gavin C on 10/12/23.
//

#include <gtest/gtest.h>
#include "Driver.h"
#include "Pieces.h"


TEST(Puzzle, Solution1) {
    auto piece_list = Driver::shuffle_piece_list()[0];
    auto p = puzzle::Puzzle(piece_list);
    auto sol = p.solve();
    ASSERT_TRUE(std::get<0>(sol));
    ASSERT_EQ(std::get<1>(sol).hash, 30087697);
}

TEST(Puzzle, Solution2) {
    auto piece_list = Driver::shuffle_piece_list()[3];
    auto p = puzzle::Puzzle(piece_list);
    auto sol = p.solve();
    ASSERT_TRUE(std::get<0>(sol));
    ASSERT_EQ(std::get<1>(sol).hash, 27193113);
}

TEST(Board, AddLPiece) {
    auto board = puzzle::Board();
    auto piece = LPiece();
    ASSERT_TRUE(board.add_piece(0, 0, piece));
    ASSERT_FALSE(board.add_piece(0, 0, piece));
    ASSERT_TRUE(board.piece_placed(piece.get_symbol()));
}

TEST(Board, AddPiece) {
    auto board = puzzle::Board();
    auto piece = UPiece();
    ASSERT_TRUE(board.add_piece(8, 0, piece.rotate().rotate().rotate()));
}

TEST(Board, CheckBoardValid) {
    auto board = puzzle::Board();
    auto piece = UPiece();
    ASSERT_TRUE(board.add_piece(8, 0, piece.rotate().rotate().rotate()));
    ASSERT_FALSE(board.is_invalid());
}

TEST(Board, CheckBoardInvalid) {
    auto board = puzzle::Board();
    auto piece = UPiece();
    ASSERT_TRUE(board.add_piece(6, 0, piece.rotate().rotate().rotate()));
    ASSERT_TRUE(board.is_invalid());
}

TEST(Board, CheckBoardContainsPiece) {
    auto board = puzzle::Board();
    auto piece = UPiece();
    ASSERT_TRUE(board.add_piece(8, 0, piece.rotate().rotate().rotate()));
    ASSERT_TRUE(board.piece_placed(piece.get_symbol()));
}

TEST(Board, BoardNotSolved) {
    auto board = puzzle::Board();
    auto piece = UPiece();
    ASSERT_TRUE(board.add_piece(8, 0, piece.rotate().rotate().rotate()));
    ASSERT_FALSE(board.is_solved());
}

TEST(Board, BoardCantAddPiece) {
    auto board = puzzle::Board();
    auto piece = UPiece();
    board.add_piece(8, 0, piece.rotate().rotate().rotate());
    ASSERT_FALSE(board.can_add_piece(8, 0, UPiece().rotate().rotate().rotate()));
}

TEST(Board, BoardCanAddPiece) {
    auto board = puzzle::Board();
    auto piece = UPiece();
    ASSERT_TRUE(board.can_add_piece(8, 0, piece.rotate().rotate().rotate()));
}

TEST(Piece, SetBlock) {
    auto piece = PuzzlePiece('p');
    ASSERT_TRUE(piece.get_data()[0] == '_');
    piece.set_block(0, 0);
    ASSERT_TRUE(piece.get_data()[0] == 'p');
}

TEST(Piece, RotatePiece90) {
    auto piece = UtahPiece();
    auto rotated = piece.rotate().get_data();
    ASSERT_TRUE(rotated[0] == 'U');
    ASSERT_TRUE(rotated[1] == 'U');
    ASSERT_TRUE(rotated[2] == 'U');
    ASSERT_TRUE(rotated[5] == 'U');
    ASSERT_TRUE(rotated[6] == 'U');
}

TEST(Piece, PieceRotateable) {
    auto piece = UtahPiece();
    ASSERT_TRUE(piece.can_rotate());
}

TEST(Piece, PieceNotRotatable) {
    auto piece = PlusPiece();
    ASSERT_FALSE(piece.can_rotate());
}

TEST(Piece, PieceFlipable) {
    auto piece = UtahPiece();
    ASSERT_FALSE(piece.is_symmetric());
}

TEST(Piece, PieceNotFlipable) {
    auto piece = PlusPiece();
    ASSERT_TRUE(piece.is_symmetric());
}

TEST(Driver, SetWriteMode) {
    Driver::set_write_mode();
    ASSERT_TRUE(Driver::is_write_mode());
}

TEST(Driver, SetPrintSteps) {
    Driver::set_print_steps();
    ASSERT_TRUE(Driver::is_print_steps());
}

TEST(Driver, SetAllSolutions) {
    Driver::set_all_solutions();
    ASSERT_TRUE(Driver::is_all_solutions());
}

TEST(Driver, SetMultiThread) {
    Driver::set_multi_thread();
    ASSERT_TRUE(Driver::is_multi_thread());
}

TEST(Driver, SetNumThreads) {
    Driver::set_num_threads(4);
    ASSERT_EQ(Driver::get_num_threads(), 4);
}

TEST(Driver, SetStartIdx) {
    Driver::set_start_idx(4);
    ASSERT_EQ(Driver::get_start_idx(), 4);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}