#include "Puzzle.h"
using namespace puzzle;

auto visited = std::set<Board>();

std::tuple<bool, Board> Puzzle::solve(Board board, std::set<PuzzlePiece> available, std::set<PuzzlePiece> placed) {
    Board copy = Board(board);
    // iterate over all available Pieces
    for (auto piece: available) {
        if (placed.find(piece) != placed.end() && copy.piece_placed(piece.get_symbol())) {
            continue;
        }
        auto placed_copy = std::set<PuzzlePiece>(placed);
        auto piece_copy = PuzzlePiece(piece);
        for (int y = 6; y >= 0; y--) {
            for (int x = 9; x >= 0; x--) {
                for (int flip = 0; flip < 1; flip++) {
                    for (int rotate = 0; rotate < 4; rotate++) {
                        if (copy.add_piece(x, y, piece_copy)) {
                            if (!copy.is_invalid()) {
                                placed_copy.insert(piece_copy);
                                if (copy.is_solved()) {
                                    copy.print_board();
                                    return std::make_tuple(true, copy);
                                }
                                auto sol = solve(Board(copy), available, placed_copy);
                                if (std::get<0>(sol)) {
                                    return sol;
                                }
                            }
                        }
                        copy = Board(board);
                        if (piece_copy.can_rotate()) {
                            piece_copy = piece_copy.rotate();
                        } else {
                            break;
                        }
                    }
                    copy = Board(board);
                    if (!piece_copy.is_symmetric()) {
                        piece_copy = piece_copy.flip_horizontal();
                    } else {
                        break;
                    }
                }
            }
        }
    }

    return std::make_tuple(false, copy);
}

int main() {
    auto pieces = std::set<PuzzlePiece>();
    auto placed = std::set<PuzzlePiece>();
    pieces.insert(AwkwardTPiece());
    pieces.insert(LongLPiece());
    pieces.insert(ShortTPiece());
    pieces.insert(PlusPiece());
    pieces.insert(UtahPiece());
    pieces.insert(IPiece());
    pieces.insert(UPiece());
    pieces.insert(TPiece());
    pieces.insert(T2Piece());
    pieces.insert(LongZPiece());
    pieces.insert(ZPiece());
    pieces.insert(LPiece());
    pieces.insert(MPiece());
//    Board board = Board();
//    board.add_piece(7, 0, UtahPiece().rotate().rotate().rotate());
//    board.print_board();
//    std::cout << board.is_invalid() << std::endl;
    auto sol = (Puzzle::solve(Board(), pieces, placed));
    auto valid = std::get<0>(sol);
    auto new_board = std::get<1>(sol);
    new_board.print_board();
    if (valid) {
        std::cout << "Solved!" << std::endl;
    } else {
        std::cout << "Not Solved!" << std::endl;
    }
}
