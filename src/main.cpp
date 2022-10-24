#include "utils.h"
#include "blockchain.h"

int main() {

    Blockchain chain;
    std::vector<User> users;
    std::vector<Transaction> pool;

    genUsers(users);
    genPool(users, pool);
    initBlockchain(chain, pool, users);

    bool input = true;
    int userChoice;

    std::cout
            << "Please use one of the following commands:\n"
            << "1. Show blockchain information\n"
            << "2. Get information regarding specific block\n"
            << "3. Get information regarding specific transaction\n"
            << "4. Exit\n";

    do {

        std::cout << "cli >: ";
        std::cin >> userChoice;

//        validateInput(userChoice, 1, 8);

        switch (userChoice) {
            case 1:
                std::cout << chain << std::endl;
                break;
            case 2:
                int blockId;
                std::cout << "Enter block id: ";
                std::cin >> blockId;

                if (blockId >= chain.getChain().size())
                    std::cerr << "Selected id is out of range" << std::endl;
                else
                    std::cout << chain.getBlockInfo(blockId) << std::endl;
                break;
            case 3:
                int transactionId;
                std::cout << "Enter transaction id: ";
                std::cin >> transactionId;

                if (transactionId >= pool.size())
                    std::cerr << "Selected id is out of range" << std::endl;
                else {

                    transactionId = getTransaction(pool, transactionId);

                    std::cout << pool[transactionId] << std::endl;

                }
                break;
            case 4:
                input = false;
                break;
        }
    } while (input);


    return 0;

}