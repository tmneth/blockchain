#include "utils.h"
#include "blockchain.h"

void showHelpMessage() {

    std::cerr
            << "\nAvailable commands: \n"
            << "help: Show this help message\n"
            << "getblock <blockhash>: Retrieve details of a mined block \n"
            << "gettransaction <transactionid>: Retrieve details of a transaction \n"
            << "stop: exit the program\n";
}


int main(int argc, char *argv[]) {

    Blockchain chain;

    std::vector<Transaction> pool;
    std::vector<User> users;

    genUsers(users);
    genPool(users, pool);
    initBlockchain(chain, pool, users);

    if (argc == 1) {
        showHelpMessage();
        return 1;
    }

    for (int i = 0; i < argc; i++) {

        std::string arg = argv[i];

        if (arg == "help") {
            showHelpMessage();
            return 1;
        } else if (arg == "getblock") {
            chain.getBlockInfo(argv[i + 1]);
        }

    }


    return 0;

}