#include "utils.h"
#include "blockchain.h"


std::vector<std::string> getArgs(std::string text) {

    std::vector<std::string> args;

    std::string::size_type beg = 0, end;
    do {
        end = text.find(' ', beg);
        if (end == std::string::npos) {
            end = text.size();
        }
        args.emplace_back(text.substr(beg, end - beg));
        beg = end + 1;
    } while (beg < text.size());

    return args;

}

void showHelpMessage() {

    std::cerr
            << "\nAvailable commands: \n"
            << "help: Show this help message\n"
            << "getblock <blockhash>: Retrieve the details of a mined block \n"
            << "gettransaction <transactionid>: Retrieve the details of a transaction \n"
            << "stop: exit the program\n";

}

int main() {

    Blockchain chain;
    Pool pool;

    std::vector<User> users;

    genUsers(users);
    genPool(users, pool);
    initBlockchain(chain, pool, users);

    bool input = true;

    do {
        std::string userArg;
        getline(std::cin, userArg);
        std::vector<std::string> args = getArgs(userArg);

        if (args[0] == "help" || args.size() > 2) {
            showHelpMessage();
        } else if (args[0] == "getblock") {
            std::string hash = args[1];
            chain.getBlockInfo(hash);
        } else if (args[0] == "gettransaction") {
            pool.getTransactionInfo(stoi(args[1]));
        } else if (args[0] == "stop") {
            input = false;
        } else {
            std::cout << "Command not found. Try again" << std::endl;
        }

    } while (input);
    
    return 0;

}