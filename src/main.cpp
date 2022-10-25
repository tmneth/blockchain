#include "utils.h"
#include "blockchain.h"


std::vector<std::string> getArgs(std::string text) {

    std::vector<std::string> words;

    std::string::size_type beg = 0, end;
    do {
        end = text.find(' ', beg);
        if (end == std::string::npos) {
            end = text.size();
        }
        words.emplace_back(text.substr(beg, end - beg));
        beg = end + 1;
    } while (beg < text.size());

    return words;

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
        std::vector<std::string> words = getArgs(userArg);

        if (words[0] == "help") {
            showHelpMessage();
        } else if (words[0] == "getblock") {
            std::string hash = words[1];
            chain.getBlockInfo(hash);
        } else if (words[0] == "gettransaction") {
            pool.getTransactionInfo(stoi(words[1]));
        } else if (words[0] == "stop") {
            input = false;
        } else {
            std::cout << "Command not found. Try again" << std::endl;
        }

    } while (input);


    return 0;

}