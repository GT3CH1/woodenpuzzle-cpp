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
bool all_solutions = false;
bool write_mode = false;
bool print_steps = false;
std::chrono::system_clock::time_point begin_time;
std::chrono::system_clock::time_point end_time;
struct thread_args {
    int thread_id;
    std::vector<PuzzlePiece> pieces;
};
std::vector<PuzzlePiece> pieces_list = std::vector<PuzzlePiece>(
        {
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

void multithread_driver(void *args) {
    auto pieces = ((struct thread_args *) args)->pieces;
    auto thread_id = ((struct thread_args *) args)->thread_id;
    auto p = Puzzle(pieces);
    p.set_thread_id(thread_id);
    if (all_solutions)
        p.set_all_solutions();
    if (write_mode)
        p.set_write_to_file();
    if(print_steps)
        p.set_print_steps();
    p.solve();
}

void Driver::print_all_solutions() {
    // print all solutions from Puzzle::solutions_map
    end_time = std::chrono::system_clock::now();
    printf("--------------------\n");
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count() / 1000.0;
    int solution_count = 0;
    std::vector<int> solution_per_thread = std::vector<int>(num_threads);
    for (auto &solution: Puzzle::get_solutions()) {
        solution.second.print_board();
        solution_count++;
        auto thread_id = solution.second.get_thread_id();
        if (thread_id != -1)
            solution_per_thread[thread_id]++;
    }

    printf("Total solutions: %lu\n", Puzzle::get_solutions().size());
    printf("Total time elapsed: %.2f seconds\n", elapsed);
    printf("Average time per solution: %.2f seconds\n", elapsed / solution_count);
    printf("Solutions per thread:\n");
    for (int i = 0; i < num_threads; i++) {
        printf("Thread #%d: %d\n", i, solution_per_thread[i]);
    }
}

void signal_handler(int sig) {
    Puzzle::kill();
    for (pthread_t thread: threads) {
        pthread_kill(thread, sig);
    }
    printf("Signal %d caught, printing all solutions\n", sig);
    end_time = std::chrono::system_clock::now();
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
    // insert original list at the beginning of the vector
    shuffled_pieces.insert(shuffled_pieces.begin(), pieces_list);
    return shuffled_pieces;
}


int main(int argc, char **argv) {
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-h") {
            printf("Usage: ./solve_puzzle [-c] [-p] [-w]\n");
            printf("Options:\n");
            printf("  -c: All solutions mode\n");
            printf("  -p: Print steps mode\n");
            printf("  -w: Write solutions to file `solutions.txt`\n");
            printf("  -t: Multi-threading mode\n");
            printf("  -n: Number of threads to use\n");
            printf("  -h: Print this help message\n");
            printf("Made by Gavin Pease (@GT3CH1)\n");
            exit(0);
        }
        if (std::string(argv[i]) == "-c") {
            std::cout << "All solutions mode\n";
            all_solutions = true;
        }
        if (std::string(argv[i]) == "-p") {
            std::cout << "Print steps mode\n";
            print_steps = true;
        }
        if (std::string(argv[i]) == "-t") {
            std::cout << "Multi-threading mode\n";
            multi_thread = true;
        }
        if (std::string(argv[i]) == "-w") {
            // clear file
            std::ofstream myfile;
            myfile.open("solutions.txt", std::ios::trunc);
            myfile.close();
            std::cout << "Writing to file `solutions.txt`\n";
            write_mode = true;
        }
        if (std::string(argv[i]) == "-n") {
            // check if next argument is a number
            if (i + 1 < argc) {
                try {
                    int num = std::stoi(argv[i + 1]);
                    if (num > 0) {
                        num_threads = num;
                        printf("Number of threads: %d\n", num);
                    }
                    i++;
                    continue;
                } catch (std::exception &e) {
                    printf("Invalid number of threads\n");
                    exit(1);
                }
            }
        }
        if (std::string(argv[i]) == "-s") {
            // start at a specific piece idx
            if (i + 1 < argc) {
                try {
                    int num = std::stoi(argv[i + 1]);
                    if (num > 0) {
                        start_idx = num;
                        printf("Starting at piece set idx: %d\n", num);
                    }
                    if (num > 11) {
                        printf("Invalid piece set\n");
                        exit(1);
                    }
                    i++;
                    continue;
                } catch (std::exception &e) {
                    printf("Invalid piece set\n");
                    exit(1);
                }
            }
        }
    }

    if (multi_thread) {
        begin_time = std::chrono::system_clock::now();
        auto shuffled_pieces = shuffle_piece_list();
        for (int j = 0; j < num_threads; j++) {
            pthread_t thread;
            auto args = new struct thread_args;
            args->thread_id = j;
            args->pieces = shuffled_pieces[j + start_idx];
            pthread_create(&thread, nullptr, (void *(*)(void *)) multithread_driver, args);
            if (all_solutions)
                pthread_detach(thread);
            threads.push_back(thread);
        }
        if (all_solutions) {
            while (true) { ;;
            }
        } else {
            for (pthread_t thread: threads) {
                pthread_join(thread, nullptr);
            }
        }
        end_time = std::chrono::system_clock::now();
    }
    begin_time = std::chrono::system_clock::now();
    auto puzzle = Puzzle(pieces_list);
    if (start_idx > 0)
        puzzle = Puzzle(shuffle_piece_list()[start_idx]);
    
    if(print_steps)
        puzzle.set_print_steps();
    if (all_solutions)
        puzzle.set_all_solutions();
    if (write_mode)
        puzzle.set_write_to_file();

    auto sol = puzzle.solve();
    end_time = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count() / 1000.0;
    printf("Total time elapsed: %.2f seconds\n", elapsed);
    auto valid = std::get<0>(sol);
    auto new_board = std::get<1>(sol);
    if (valid) {
        new_board.print_board();
    } else {
        printf("No solution found!\n");
    }
}
