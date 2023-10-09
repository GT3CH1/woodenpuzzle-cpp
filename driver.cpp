//
// Created by Pease, Gavin C on 10/8/23.
//

#include "driver.h"
#include <iostream>
#include <fstream>
#include <csignal>

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
}

void signal_handler(int sig) {
    Puzzle::kill();
    printf("Signal %d caught, printing all solutions\n", sig);
    Driver::print_all_solutions();
    exit(sig);
}


int main(int argc, char **argv) {
    signal(SIGINT, signal_handler);
    auto puzzle = Puzzle();
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
        }
        if (std::string(argv[i]) == "-p") {
            puzzle.set_print_steps();
            std::cout << "Print steps mode\n";
        }
        if (std::string(argv[i]) == "-w") {
            write_to_file = true;
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

