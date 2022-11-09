#include "utils.h"
#include "blockchain.h"

void showHelpMessage() {

    std::cerr
            << "Please use one of the following commands:\n"
            << "help - Displays available commands.\n"
            << "initchain - initializes and serializes blockchain.\n"
            << "getblockchaininfo - Returns an object containing various state info.\n"
            << "getblock <hash> - Returns information about the block with the given hash.\n"
            << "getrawtransaction <txid> - Returns raw transaction representation for given transaction id.\n"
            << "exit: Exits the program.";

}

int main(int argc, char *argv[]) {

    Blockchain chain;
    std::vector<Transaction> pool;
    std::vector<User> users;

    if (!std::filesystem::exists("blockchaininfo.json"))
        initBlockchain(chain, pool, users);

    for (int i = 0; i < argc; i++) {

        std::string arg = argv[i];

        if (arg == "help" || argc == 1 || argc > 3) {
            showHelpMessage();
            return 127;
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