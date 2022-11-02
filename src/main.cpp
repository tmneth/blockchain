#include "utils.h"
#include "blockchain.h"

void showHelpMessage() {

    std::cerr
            << "\nAvailable commands: \n"
            << "help: Show this help message\n"
            << "test: Generate users & transactions to test blockchain"
            << "getblock <blockid>: Retrieve details of a mined block \n"
            << "exit: exit the program\n\n";

}


int main(int argc, char *argv[]) {

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
            std::cout << chain.getBlockInfo(std::stoi(argv[i + 1])) << std::endl;
        } else if (arg == "exit") {
            return 0;
        }

    }


    return 0;

}