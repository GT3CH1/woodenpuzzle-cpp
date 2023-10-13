#include "Puzzle.h"
#include <map>

using namespace puzzle;

std::map<uint, puzzle::Board> Puzzle::solutions_map;

std::set<uint> Puzzle::solutions;

Puzzle::Puzzle() {
    solutions_map = std::map<uint, puzzle::Board>();
    solutions = std::set<uint>();
    kill_switch = false;
    all_solutions = false;
    print_steps = false;
    write_to_file = false;
}

std::tuple<bool, Board> Puzzle::solve() {
	time_helper.set_start_time();
    auto board = Board();
    board.set_thread_id(thread_id);
    return solve(board, available_pieces, std::set<PuzzlePiece>());
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
        int flip = 0;
        int rotate = 0;
        int x = 0;
        int y = 0;
	/*
	 * This loop is what drives rotating, flipping, and moving the puzzle
	 * pieces across the board until the piece is in a valid location.
	 * It essentially is a condensed nested for loop.
	 */
        while (flip < 1 || rotate < 4 || y < 6 || x < 10) {
            if (copy.add_piece(x, y, piece_copy) && !copy.is_invalid()) {
                placed_copy.insert(piece_copy);
                if (!copy.is_solved()) {
                    auto sol = solve(Board(copy), pieces, placed_copy);
                    if (!all_solutions && std::get<0>(sol)) {
                        return sol;
                    }
                    copy = Board(board);
                    break;
                }
                pthread_mutex_lock(&lock);
                if (!solutions.empty() && solutions.find(copy.hash) != solutions.end()) {
                    pthread_mutex_unlock(&lock);
                    break;
                }
                pthread_mutex_unlock(&lock);
                if (!all_solutions)
                    return std::make_tuple(true, copy);
                pthread_mutex_lock(&lock);
		time_helper.set_end_time();
                copy.set_time_to_solve(time_helper.calculate_time());
		if (print_steps) {
			copy.print_board();
			std::cout << std::flush;
		}
		time_helper.set_start_time();
                solutions.insert(copy.hash);
                solutions_map.insert({copy.hash, Board(copy)});
                pthread_mutex_unlock(&lock);
                if (write_to_file && !kill_switch) {
                    pthread_mutex_lock(&lock);
                    std::ofstream myfile;
                    myfile.open("solutions.txt", std::ios::app);
                    myfile << copy.get_pretty_data() << "\n";
                    myfile.close();
                    pthread_mutex_unlock(&lock);
                }
                return std::make_tuple(false, copy);
            }
            copy = Board(board);
            if (rotate < 4 && piece_copy.can_rotate()) {
                piece_copy = piece_copy.rotate();
                rotate++;
                continue;
            } else if (flip < 1 && !piece_copy.is_symmetric()) {
                piece_copy = piece_copy.flip_horizontal();
                rotate = 0;
                flip++;
                continue;
            } else if (x < 10) {
                x++;
                rotate = 0;
                flip = 0;
                continue;
            } else if (y < 6) {
                y++;
                x = 0;
                rotate = 0;
                flip = 0;
                continue;
            } else {
                break;
            }
        }
    }
    return std::make_tuple(false, board);
}

std::map<uint, puzzle::Board> Puzzle::get_solutions() {
    return Puzzle::solutions_map;
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

Puzzle::Puzzle(std::vector<PuzzlePiece> &pieces) {
    solutions_map = std::map<uint, puzzle::Board>();
    solutions = std::set<uint>();
    kill_switch = false;
    all_solutions = false;
    print_steps = false;
    write_to_file = false;
    available_pieces = pieces;
}

void Puzzle::set_thread_id(int id) {
    thread_id = id;
}

int Puzzle::get_thread_id() {
    return thread_id;
}
