#include "Puzzle.h"
#include <map>

using namespace puzzle;

std::map<uint, puzzle::Board> solutions_map;
static std::set<uint> solutions;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

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
    pthread_mutex_lock(&lock);
    printf("Thread #%d started\n", thread_id);
    pthread_mutex_unlock(&lock);
    return solve(Board(), available_pieces, std::set<PuzzlePiece>());
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
        while (flip < 1 || rotate < 4 || y < 6 || x < 10) {
            if (print_steps) {
                pthread_mutex_lock(&lock);
                printf("Thread #%d\n", thread_id);
                copy.print_board();
                pthread_mutex_unlock(&lock);
            }
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
                if (!solutions.empty() && solutions.find(copy.hash) != solutions.end())
                    break;
                if (!all_solutions) {
                    pthread_mutex_lock(&lock);
                    printf("Thread #%d\n", thread_id);
                    printf("Solution hash: %u\n", copy.hash);
                    copy.print_board();
                    printf("Time elapsed: %.2f seconds\n\n", copy.get_time_to_solve());
                    pthread_mutex_unlock(&lock);
                    return std::make_tuple(true, copy);

                }
                pthread_mutex_lock(&lock);

                copy.print_board();
                printf("Thread #%d\n", thread_id);
                printf("Solution hash: %u\n", copy.hash);
                end = clock();
                copy.set_time_to_solve((double) (end - begin) / CLOCKS_PER_SEC);
                printf("Time elapsed: %.2f seconds\n\n", copy.get_time_to_solve());
                std::cout << std::flush;

                pthread_mutex_unlock(&lock);
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

Puzzle::Puzzle(std::vector<PuzzlePiece> &pieces) {
    solutions_map = std::map<uint, puzzle::Board>();
    solutions = std::set<uint>();
    kill_switch = false;
    all_solutions = false;
    print_steps = false;
    write_to_file = false;

    begin = end = 0;
    available_pieces = pieces;
    // initialize mutex
    pthread_mutex_init(&lock, nullptr);
}

void Puzzle::set_thread_id(int id) {
    thread_id = id;
}