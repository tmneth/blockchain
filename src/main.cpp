#include "utils.h"
#include "blockchain.h"

void showHelpMessage() {

    std::cerr
            << "Please use one of the following commands:\n"
            << "help: Show this help message\n"
            << "initchain: Initialize blockchain\n"
            << "getblock <blockhash>: Retrieve information of a selected block\n"
            << "getrawtransaction <txid>: Retrieve information of a selected transaction\n"
            << "exit: Exit the program\n"
            << std::endl;

}

int main(int argc, char *argv[]) {

    Blockchain chain;
    std::vector <Transaction> pool;
    std::vector <User> users;

    if (argc == 1) {
        showHelpMessage();
        return 1;
    }

    for (int i = 0; i < argc; i++) {

        std::string arg = argv[i];

        if (arg == "help") {
            showHelpMessage();
            return 1;
        } else if (arg == "initchain") {
            initBlockchain(chain, pool, users);
        } else if (arg == "getblockchaininfo") {
            chain.getBlockchaininfo();
        } else if (arg == "getblock") {
            chain.getBlock(argv[i + 1]);
        } else if (arg == "getrawtransaction") {
            chain.getRawtransaction(argv[i + 1]);
        } else if (arg == "exit") {
            return 1;
        }

    }

    return 0;

}