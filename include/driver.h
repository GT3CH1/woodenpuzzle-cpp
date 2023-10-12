#ifndef WOODENPUZZLE_CPP_DRIVER_H
#define WOODENPUZZLE_CPP_DRIVER_H

#include <map>
#include <vector>
#include "Board.h"
#include "Puzzle.h"

using namespace puzzle;
namespace puzzle {
    /**
     * The driver class used to solve the puzzle.
     * @author GT3CH1
     */
    class Driver {
    public:
        /**
         * Prints all solutions to the puzzle discovered by the driver.
         */
        static void print_all_solutions();
    };
}
/**
 * The start time of the program.
 */
static clock_t begin;

/**
 * The end time of the program.
 */
static clock_t end;
static int num_threads = 1;
static int start_idx = 0;
#endif //WOODENPUZZLE_CPP_DRIVER_H
