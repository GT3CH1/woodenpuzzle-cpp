#include "Puzzle.h"
#include <map>

using namespace puzzle;

std::map<uint, puzzle::Board> solutions_map;
static std::set<uint> solutions;

Puzzle::Puzzle() {
    solutions_map = std::map<uint, puzzle::Board>();
    solutions = std::set<uint>();
    kill_switch = false;
    all_solutions = false;
    print_steps = false;
    write_to_file = false;

    begin = end = 0;
}

std::tuple<bool, Board> Puzzle::solve() {
    begin = clock();
    auto pieces = std::vector<PuzzlePiece>();
    pieces.clear();
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
    return solve(Board(), pieces, std::set<PuzzlePiece>());
}

std::tuple<bool, Board>
Puzzle::solve(Board board, const std::vector<PuzzlePiece> &pieces, const std::set<PuzzlePiece> &placed) {
    if (kill_switch) {
        return std::make_tuple(false, board);
    }
    // iterate over all available Pieces
    for (const auto &piece: pieces) {
        if (board.piece_placed(piece.get_symbol())) {
            continue;
        }
        auto placed_copy = std::set<PuzzlePiece>(placed);
        auto piece_copy = PuzzlePiece(piece);
        if (solutions.find(board.hash) != solutions.end()) {
            continue;
        }
        Board copy = Board(board);
        for (int flip = 0; flip < 1; flip++) {
            for (int rotate = 0; rotate < 4; rotate++) {
                for (int y = 0; y < 6; y++) {
                    for (int x = 0; x < 10; x++) {
                        if (copy.add_piece(x, y, piece_copy)) {
                            if (copy.is_invalid()) {
                                copy = Board(board);
                                continue;
                            }
                            placed_copy.insert(piece_copy);
                            if (print_steps) {
                                copy.print_board();
                            }
                            if (copy.is_solved()) {
                                if (!solutions.empty() && solutions.find(copy.hash) != solutions.end())
                                    break;
                                if (!all_solutions) {
                                    return std::make_tuple(true, copy);
                                } else {
                                    copy.print_board();
                                    printf("Solution hash: %u\n", copy.hash);
                                    end = clock();
                                    copy.set_time_to_solve((double) (end - begin) / CLOCKS_PER_SEC);
                                    printf("Time elapsed: %.2f seconds\n\n", copy.get_time_to_solve());
                                    std::cout << std::flush;
                                    begin = clock();
                                    solutions.insert(copy.hash);
                                    solutions_map.insert({copy.hash, Board(copy)});
                                    if (write_to_file && !kill_switch) {
                                        std::ofstream myfile;
                                        myfile.open("solutions.txt", std::ios::app);
                                        myfile << copy.get_pretty_data() << "\n";
                                        myfile << "Solution hash: " << copy.hash << "\n";
                                        myfile << "Time elapsed: " << copy.get_time_to_solve()
                                               << " seconds\n";
                                        myfile << "\n";
                                        myfile.close();
                                    }
                                    return std::make_tuple(false, copy);
                                }

                            }
                            auto sol = solve(Board(copy), pieces, placed_copy);
                            if (all_solutions) {
                                copy = Board(board);
                                break;
                            }
                            if (std::get<0>(sol)) {
                                return sol;
                            }
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
    return std::make_tuple(false, board);
}

std::map<uint, puzzle::Board> Puzzle::get_solutions() {
    return solutions_map;
}

void Puzzle::set_all_solutions() {
    this->all_solutions = true;
}

void Puzzle::set_print_steps() {
    print_steps = true;
}

void Puzzle::set_write_to_file() {
    write_to_file = true;
}

void Puzzle::kill() {
    kill_switch = true;
}
