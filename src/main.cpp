#include "Driver.h"
#include "Puzzle.h"
#include <iostream>
#include <csignal>
void signal_handler(int sig) {
    Puzzle::kill();
    for (pthread_t thread: Driver::threads) {
        pthread_kill(thread, sig);
    }
    printf("Signal %d caught, printing all solutions\n", sig);
    Driver::time_helper.set_end_time();
    Driver::print_all_solutions();
    exit(sig);
}


int main(int argc, char **argv) {
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    Driver::setup_arguments(argc, argv);
    if (Driver::is_multi_thread())
        Driver::handle_multi_thread();
    Driver::handle_single_thread();
}
