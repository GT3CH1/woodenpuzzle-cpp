//
// Created by Pease, Gavin C on 10/8/23.
//

#include "driver.h"
#include <iostream>
#include <fstream>
#include <csignal>
#include <algorithm>
#include <pthread.h>


std::vector<pthread_t> threads;
bool multi_thread = false;
std::vector<PuzzlePiece> pieces_list = std::vector<PuzzlePiece>({
                                                                        UtahPiece(),
                                                                        PlusPiece(),
                                                                        TPiece(),
                                                                        MPiece(),
                                                                        LongZPiece(),
                                                                        ShortTPiece(),
                                                                        ZPiece(),
                                                                        AwkwardTPiece(),
                                                                        LPiece(),
                                                                        LongLPiece(),
                                                                        IPiece(),
                                                                        UPiece(),
                                                                        T2Piece()
                                                                });

void multithread_driver(Puzzle &p) {
    p.solve();
}

void Driver::print_all_solutions() {
    // print all solutions from Puzzle::solutions_map
    printf("--------------------\n");
    double total_time = 0;
    int solution_count = 0;
    for (auto &solution: Puzzle::get_solutions()) {
        solution.second.print_board();
        printf("Solution hash: %u\n", solution.first);
        printf("Time elapsed: %.2f seconds\n\n", solution.second.get_time_to_solve());
        total_time += solution.second.get_time_to_solve();
        solution_count++;
    }
    printf("Total solutions: %lu\n", Puzzle::get_solutions().size());
    printf("Total time elapsed: %.2f seconds\n", total_time);
    printf("Average time per solution: %.2f seconds\n", total_time / solution_count);
    // flush buffer
    std::cout << std::flush;
}

void signal_handler(int sig) {
    Puzzle::kill();
    for (unsigned long thread: threads) {
        pthread_join(thread, nullptr);
    }
    printf("Signal %d caught, printing all solutions\n", sig);
    Driver::print_all_solutions();
    exit(sig);
}


std::vector<std::vector<PuzzlePiece>> shuffle_piece_list() {
    std::vector<std::vector<PuzzlePiece>> shuffled_pieces;
    // move the first piece to the end of the list, add the new list to the vector
    for (int i = 0; i < 12; i++) {
        std::vector<PuzzlePiece> new_list = std::vector<PuzzlePiece>();
        for (int j = 0; j < 12; j++)
            new_list.push_back(pieces_list[(j + i) % 13]);
        shuffled_pieces.push_back(new_list);
    }
    return shuffled_pieces;
}


int main(int argc, char **argv) {
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    auto puzzle = Puzzle(pieces_list);
    bool all_solutions = false;
    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-h") {
            printf("Usage: ./solve_puzzle [-c] [-p] [-w]\n");
            printf("Options:\n");
            printf("  -c: All solutions mode\n");
            printf("  -p: Print steps mode\n");
            printf("  -w: Write solutions to file `solutions.txt`\n");
            printf("  -h: Print this help message\n");
            printf("Made by Gavin Pease (@GT3CH1)\n");
            exit(0);
        }
        if (std::string(argv[i]) == "-c") {
            puzzle.set_all_solutions();
            std::cout << "All solutions mode\n";
            all_solutions = true;
        }
        if (std::string(argv[i]) == "-p") {
            puzzle.set_print_steps();
            std::cout << "Print steps mode\n";
        }
        if (std::string(argv[i]) == "-t") {
            multi_thread = true;
            std::cout << "Multi-threading mode\n";
            begin = clock();
            auto shuffled_pieces = shuffle_piece_list();
            for (int j = 0; j < 1; j++) {
                pthread_t thread;
                puzzle = Puzzle(shuffled_pieces[j]);
                puzzle.set_all_solutions();
                puzzle.set_print_steps();
                puzzle.set_thread_id(j);
                pthread_create(&thread, nullptr, (void *(*)(void *)) multithread_driver, &puzzle);
                if (all_solutions)
                    pthread_detach(thread);
                threads.push_back(thread);
            }
            if (all_solutions) {
                while (true) { ;;
                }
            } else {
                for (unsigned long thread: threads) {
                    pthread_join(thread, nullptr);
                }
            }
            end = clock();
        }
        if (std::string(argv[i]) == "-w") {
            puzzle.set_write_to_file();
            // clear file
            std::ofstream myfile;
            myfile.open("solutions.txt", std::ios::trunc);
            myfile.close();
            std::cout << "Writing to file `solutions.txt`\n";
        }
    }
    begin = clock();
    auto sol = puzzle.solve();
    end = clock();
    printf("Time elapsed: %.2f\n", (double) (end - begin) / CLOCKS_PER_SEC);
    auto valid = std::get<0>(sol);
    auto new_board = std::get<1>(sol);
    new_board.print_board();
    if (valid) {
        printf("Solved!\n");
    } else {
        printf("No solution found!\n");
    }
}
