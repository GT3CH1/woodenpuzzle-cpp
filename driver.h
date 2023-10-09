//
// Created by Pease, Gavin C on 10/8/23.
//

#ifndef WOODENPUZZLE_CPP_DRIVER_H
#define WOODENPUZZLE_CPP_DRIVER_H

#include <map>
#include <vector>
#include "Board.h"
#include "Puzzle.h"
using namespace puzzle;
namespace puzzle {
    class Driver {
    public:
        static void print_all_solutions();


    };
}
static bool write_to_file = false;
static clock_t begin;
static clock_t end;
#endif //WOODENPUZZLE_CPP_DRIVER_H
