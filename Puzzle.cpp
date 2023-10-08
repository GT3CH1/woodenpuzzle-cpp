#include "Puzzle.h"

using namespace puzzle;

auto visited = std::set<Board>();

bool all_solutions = false;
bool print_steps = false;

std::tuple<bool, Board> Puzzle::solve(Board board, std::vector<PuzzlePiece> available, std::set<PuzzlePiece> placed) {
    Board copy = Board(board);
    // iterate over all available Pieces
    for (const auto &piece: available) {
        if (placed.find(piece) != placed.end() && copy.piece_placed(piece.get_symbol())) {
            continue;
        }
        auto placed_copy = std::set<PuzzlePiece>(placed);
        auto piece_copy = PuzzlePiece(piece);
        for (int y = 0; y < 6; y++) {
            for (int x = 0; x < 10; x++) {
                for (int flip = 0; flip < 1; flip++) {
                    for (int rotate = 0; rotate < 4; rotate++) {
                        if(rotate == 2 && flip == 0 && x == 7 && y == 0 && piece_copy.get_symbol() == 'U') {
                            std::cout << "here" << std::endl;
                        }
                        if (copy.add_piece(x, y, piece_copy)) {
                            if (!copy.is_invalid()) {
                                if (print_steps)
                                    copy.print_board();
                                placed_copy.insert(piece_copy);
                                if (copy.is_solved()) {
                                    if (visited.find(Board(copy)) != visited.end()) {
                                        return std::make_tuple(false, board);
                                    }
                                    visited.insert(Board(copy));
                                    copy.print_board();
                                    return std::make_tuple(true, copy);
                                }
                                // remove piece from available pieces
                                auto available_copy = std::vector<PuzzlePiece>();
                                for (const auto &p: available) {
                                    if (p.get_symbol() != piece_copy.get_symbol()) {
                                        available_copy.push_back(p);
                                    }
                                }
                                auto sol = solve(Board(copy), available_copy, placed_copy);
                                if (std::get<0>(sol)) {
                                    visited.insert(Board(copy));
                                    if (all_solutions) {
                                        break;
                                    }
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

int main(int argc, char **argv) {
    // check if "-c" flag is present
    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-c") {
            all_solutions = true;
            std::cout << "All solutions mode";
        }
        if (std::string(argv[i]) == "-p") {
            print_steps = true;
            std::cout << "Print steps mode";
        }
    }
    std::cout << std::endl;
    std::vector<PuzzlePiece> pieces;
    auto placed = std::set<PuzzlePiece>();
    pieces.push_back(UtahPiece());
    pieces.push_back(PlusPiece());
    pieces.push_back(TPiece());
    pieces.push_back(MPiece());
    pieces.push_back(LongZPiece());
    pieces.push_back(ShortTPiece());
    pieces.push_back(ZPiece());
    pieces.push_back(AwkwardTPiece());
    pieces.push_back(LPiece());
    pieces.push_back(LongLPiece());
    pieces.push_back(IPiece());
    pieces.push_back(UPiece());
    pieces.push_back(T2Piece());
    for (auto piece: pieces) {
        std::cout << "Piece: " << piece.get_symbol() << std::endl;
        piece.print();
    }
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
