#include "utils.h"

double genRandAmount() {

    std::mt19937 mt{std::random_device{}()};
    std::uniform_real_distribution<> amount(1000.0, 99999.0);

    return amount(mt);
}

void genUsers(std::vector<User> &users) {

    for (int i = 1; i <= 1000; ++i) {
        User user("user" + std::to_string(i), genRandAmount());

        users.push_back(user);
    }

}

void genPool(std::vector<User> &users, std::vector<Transaction> &pool) {

    std::random_device device;
    std::mt19937 mt(device());
    std::uniform_int_distribution<int> seed(0, users.size() - 1);

    for (int i = 0; i < 10000; ++i) {
        double amount = genRandAmount();

        int randUser1 = seed(mt);
        int randUser2 = seed(mt);

        while (randUser1 == randUser2)
            randUser1 = seed(mt);

        Transaction transaction;

        transaction.setId(i);

        transaction.setAmount(amount);

        transaction.setSender(users[randUser1].getPublicKey());
        transaction.setRecipient(users[randUser2].getPublicKey());

        transaction.setHash();

        pool.push_back(transaction);
    }

}

void purgeTransactions(std::vector<Transaction> newPool, std::vector<Transaction> &pool) {

    for (Transaction &tx: newPool) {
        auto it = std::find_if(pool.begin(), pool.end(),
                               [&tx](const Transaction &t) { return t.getId() == tx.getId(); });
        pool.erase(it);
    }

}

std::vector<Transaction> selectTransactions(std::vector<Transaction> &pool) {

    std::vector<Transaction> newPool;

    std::vector<int> randInd;

    for (int i = 0; i < pool.size(); ++i)
        randInd.push_back(i);


    std::shuffle(randInd.begin(), randInd.end(), std::mt19937(std::random_device()()));

    for (int i = 0; i < 100; ++i) {

        int index = randInd[i];

        newPool.push_back(pool[index]);

    }

    return newPool;

}

void initBlockchain(Blockchain &chain, std::vector<Transaction> pool, std::vector<User> &users, bool debug = false) {

    genUsers(users);
    genPool(users, pool);

    while (!pool.empty()) {
        std::vector<Transaction> newPool;
        std::vector<Block> blocks;
        char blockName = 'a';
        int maxNonce = 10000;

        for (int j = 0; j < 5; ++j)
            blocks.emplace_back(chain.getPrevHash(), selectTransactions(pool));

        for (Block block: blocks) {
            block.processTransactions(pool, users);
            if (block.mine(maxNonce)) {
                purgeTransactions(block.getData(), pool);
                chain.appendBlock(block);
                if (debug) {
                    std::cout << "\nMined block " << blockName << std::endl;
                    std::cout << block << std::string(13, '-') << std::endl;
                }
                break;
            } else {
                blockName++;
                maxNonce *= 2;
            }
        }
    }

}