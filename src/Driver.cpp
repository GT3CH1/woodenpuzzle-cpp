//
// Created by Pease, Gavin C on 10/8/23.
//

#include "Driver.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <pthread.h>

std::vector<pthread_t> Driver::threads = std::vector<pthread_t>();
TimeHelper Driver::time_helper = TimeHelper();
void Driver::multithread_driver(void *args) {
    auto pieces = ((struct thread_args *) args)->pieces;
    auto thread_id = ((struct thread_args *) args)->thread_id;
    auto p = Puzzle(pieces);
    p.set_thread_id(thread_id);
    Driver::setup_puzzle(&p);
    p.solve();
}

void Driver::print_all_solutions() {
    // print all solutions from Puzzle::solutions_map
    time_helper.set_end_time();
    printf("--------------------\n");
    double elapsed = Driver::time_helper.calculate_time();
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


std::vector<std::vector<PuzzlePiece>> Driver::shuffle_piece_list() {
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

void Driver::setup_arguments(int argc, char *const *argv) {
    for (int i = 0; i < argc; i++) {
        auto arg = std::string(argv[i]);
        if (arg == "-h") {
            printf("Usage: ./solve_puzzle [-c] [-p] [-w]\n");
            printf("Options:\n");
            printf("  -c: All solutions mode\n");
            printf("  -p: Print steps mode\n");
            printf("  -w: Write solutions to file `solutions.txt`\n");
            printf("  -t: Multi-threading mode\n");
            printf("  -n: Number of threads to use (1-11)\n");
            printf("  -s: Start at a specific piece set (0-11)\n");
            printf("  -h: Print this help message\n");
            printf("Made by Gavin Pease (@GT3CH1)\n");
            exit(0);
        }
        if (arg == "-c") {
            std::cout << "All solutions mode\n";
            Driver::set_all_solutions();
        }
        if (arg == "-p") {
            std::cout << "Print steps mode\n";
            Driver::set_print_steps();
        }
        if (arg == "-t") {
            std::cout << "Multi-threading mode\n";
            Driver::set_multi_thread();
        }
        if (arg == "-w") {
            // clear file
            std::ofstream myfile;
            myfile.open("solutions.txt", std::ios::trunc);
            myfile.close();
            std::cout << "Writing to file `solutions.txt`\n";
            Driver::set_write_mode();
        }
        if (arg == "-n") {
            // check if next argument is a number
            if (i + 1 < argc) {
                try {
                    int num = std::stoi(argv[i + 1]);
                    if (num > 0) {
                        Driver::set_num_threads(num);
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
                        Driver::set_start_idx(num);
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
}

void Driver::set_write_mode() {
    mode = mode | 0b1000;
}

void Driver::set_print_steps() {
    mode = mode | 0b0100;
}

void Driver::set_all_solutions() {
    mode = mode | 0b0010;
}

void Driver::set_multi_thread() {
    mode = mode | 0b0001;
}

bool Driver::is_write_mode() {
    return (mode & 0b1000) == 0b1000;
}

bool Driver::is_print_steps() {
    return (mode & 0b0100) == 0b0100;
}

bool Driver::is_all_solutions() {
    return (mode & 0b0010) == 0b0010;
}

bool Driver::is_multi_thread() {
    return (mode & 0b0001) == 0b0001;
}

void Driver::handle_single_thread() {
    Driver::time_helper.set_start_time();
    auto puzzle = Puzzle(pieces_list);
    if (start_idx > 0)
        puzzle = Puzzle(shuffle_piece_list()[start_idx]);
    Driver::setup_puzzle(&puzzle);
    auto sol = puzzle.solve();
    Driver::time_helper.set_end_time();
    double elapsed = Driver::time_helper.calculate_time();
    printf("Total time elapsed: %.2f seconds\n", elapsed);
    auto valid = std::get<0>(sol);
    auto new_board = std::get<1>(sol);
    if (valid) {
        new_board.print_board();
    } else {
        printf("No solution found!\n");
    }
}

void Driver::handle_multi_thread() {
    Driver::time_helper.set_start_time();
    auto shuffled_pieces = shuffle_piece_list();
    for (int j = 0; j < num_threads; j++) {
        pthread_t thread;
        auto args = new struct thread_args;
        args->thread_id = j;
        args->pieces = shuffled_pieces[j + start_idx];
        pthread_create(&thread, nullptr, (void *(*)(void *)) Driver::multithread_driver, args);
        pthread_detach(thread);
        Driver::threads.push_back(thread);
    }
    // busy loop to keep the program running
    while (1) { ;;
    }
}

void Driver::set_num_threads(int num_threads) {
    Driver::num_threads = num_threads;
}

int Driver::get_num_threads() {
    return Driver::num_threads;
}

void Driver::set_start_idx(int start_idx) {
    Driver::start_idx = start_idx;
}

int Driver::get_start_idx() {
    return Driver::start_idx;
}

void Driver::setup_puzzle(puzzle::Puzzle *puzzle) {
    if (Driver::is_print_steps())
        puzzle->set_print_steps();
    if (Driver::is_all_solutions())
        puzzle->set_all_solutions();
    if (Driver::is_write_mode())
        puzzle->set_write_to_file();
}