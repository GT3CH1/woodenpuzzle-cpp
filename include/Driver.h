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
         * Helper to handle the arguments passed to the program.
         * @param argc - The number of arguments passed to the program.
         * @param argv - The list of arguments passed to the program.
         */
        static void setup_arguments(int argc, char *const *argv);

        /**
         * Helper method to help when multi-threading is enabled.
         */
        static void handle_multi_thread();

        /**
         * Helper method to help when multi-threading is disabled.
         */
        static void handle_single_thread();

        /**
         * Sets write mode to true.
         */
        static void set_write_mode();

        /**
         * Sets print steps to true.
         */
        static void set_print_steps();

        /**
         * Sets all solutions mode to true.
         */
        static void set_all_solutions();

        /**
         * Sets multi-threading mode to true.
         */
        static void set_multi_thread();

        /**
         * Gets whether write mode is enabled.
         * @return True if write mode is enabled.
         */
        static bool is_write_mode();

        /**
         * Gets whether print steps mode is enabled.
         * @return True if printing steps should be enabled.
         */
        static bool is_print_steps();

        /**
         * Gets whether all solutions mode is enabled.
         * @return True if all solutions mode is enabled.
         */
        static bool is_all_solutions();

        /**
         * Gets whether multi-threading mode is enabled.
         * @return True if multi-threading mode is enabled.
         */
        static bool is_multi_thread();

        /**
         * Sets the number of threads to use if multi-threading mode is enabled.
         * @param num_threads The number of threads to use.
         */
        static void set_num_threads(int num_threads);

        /**
         * Gets the number of threads to use if multi-threading mode is enabled.
         * @return The number of threads.
         */
        static int get_num_threads();

        /**
         * Sets the starting shuffled piece set to use.
         * @param start_idx The starting shuffle index.
         * @see shuffle_piece_list()
         */
        static void set_start_idx(int start_idx);

        /**
         * Gets the starting piece set index.
         * @return The starting piece set index.
         * @see shuffle_piece_list()
         */
        static int get_start_idx();

        /**
         * Helper method to configure the puzzle algorithm based on driver configuration.
         * @param puzzle
         */
        static void setup_puzzle(puzzle::Puzzle *puzzle);

        /**
         * Shuffles the list of pieces to use for the puzzle. This is done by moving the first piece to the end of the list.
         * This is done 12 times, and the original list is inserted at the beginning of the vector.
         * @return A vector containing the shuffled lists of pieces.
         */
        static std::vector<std::vector<PuzzlePiece>> shuffle_piece_list();

        static std::vector<pthread_t> threads;

        /**
         * The time helper used to calculate the time taken to solve the puzzle.
         */
        static TimeHelper time_helper;
    private:
        /**
         * The mode of the driver.
         */
        static inline int mode = 0;
        /**
         * The number of threads to use.
         */
        static inline int num_threads = 1;
        /**
         * The starting index for the shuffled piece set.
         */
        static inline int start_idx = 0;

        /**
         * The driver function for when multi-threading is enabled.
         */
        static void multithread_driver(void *args);

        /**
         * The list of pieces to use for the puzzle.
         */
        static inline std::vector<PuzzlePiece> pieces_list = std::vector<PuzzlePiece>(
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


#endif //WOODENPUZZLE_CPP_DRIVER_H
