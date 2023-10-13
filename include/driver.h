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
	
	/**
	 * The driver function for when multi-threading is enabled.
	 */
	static void multithread_driver(void *args);
    };
}

/**
 * A struct containing the arguments for the multithreaded driver, such as the
 * thread id and the list of pieces to use.
 */
struct thread_args {
    int thread_id;
    std::vector<PuzzlePiece> pieces;
};

/**
 * The time helper used to calculate the time taken to solve the puzzle.
 */
static TimeHelper time_helper;

/**
 * The number of threads to use.
 */
static int num_threads = 1;

/**
 * The index of the first piece set to use.
 */
static int start_idx = 0;

#endif //WOODENPUZZLE_CPP_DRIVER_H
