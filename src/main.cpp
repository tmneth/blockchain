#include "utils.h"
#include "blockchain.h"

void showHelpMessage() {

    std::cerr
            << std::endl << std::left << "Available commands: \n\n"
            << std::setw(23) << "help" << "Show this help message\n"
            << std::setw(23) << "test" << "Generate users & transactions to test blockchain\n"
            << std::setw(23) << "getblock <blockid>" << "Retrieve details of a mined block \n"
            << std::setw(23) << "omp" << "Get number of available threads\n"
            << std::setw(23) << "exit" << "exit the program\n\n";

}


int main(int argc, char *argv[]) {

//    omp_set_num_threads(THREAD_NUM);

    Blockchain chain;

    std::vector<Transaction> pool;
    std::vector<User> users;

    if (argc == 1) {
        showHelpMessage();
        return 1;
    }

    for (int i = 0; i < argc; i++) {

        std::string arg = argv[i];

        if (arg == "help") {
            showHelpMessage();
            return 1;
        } else if (arg == "test") {
            initBlockchain(chain, pool, users, true);
        } else if (arg == "getblock") {
            initBlockchain(chain, pool, users, false);
            chain.getBlockInfo(std::stoi(argv[i + 1]));
        } else if (arg == "exit") {
            return 0;
        } else if (arg == "omp") {
#           pragma omp parallel
            printf("Hello from thread %d out of %d threads\n", omp_get_thread_num(), omp_get_num_threads());
        }
    }


    return 0;

}