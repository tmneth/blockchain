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

    for (int i = 1; i <= 10000; ++i) {

        double amount = genRandAmount();

        int randUser1 = seed(mt);
        int randUser2 = seed(mt);

        while (randUser1 == randUser2)
            randUser1 = seed(mt);

        while (amount > users[randUser1].getBalance())
            amount = genRandAmount();

        Transaction transaction;

        transaction.setId(i);

        transaction.setAmount(amount);

        transaction.setSender(users[randUser1].getPublicKey());
        transaction.setRecipient(users[randUser2].getPublicKey());

        transaction.setHash();

        pool.push_back(transaction);
    }

}

std::vector<Transaction> shrinkPool(std::vector<Transaction> &pool) {

    std::vector<Transaction> newPool;

    for (int i = 0; i < 100; ++i) {

        std::random_device device;
        std::mt19937 mt(device());
        std::uniform_int_distribution<int> seed(0, pool.size() - 1);

        int index = seed(mt);

        newPool.push_back(pool[index]);

    }


    return newPool;

}

void purgeTransactions(std::vector<Transaction> newPool, std::vector<Transaction> &pool) {

    for (Transaction &tx: newPool) {
        auto it = std::find_if(pool.begin(), pool.end(),
                               [&tx](Transaction t) { return t.getId() == tx.getId(); });
        if (it != pool.end()) {
            pool.erase(it);
        }
    }
}

void initBlockchain(Blockchain &chain, std::vector<Transaction> pool, std::vector<User> &users) {

    for (int i = 1; pool.size(); i++) {

        std::vector<Transaction> newPool;
        std::vector<Block> blocks;
        char blockName = 'a';
        int maxNonce = 10000;

        for (int j = 0; j < 5; ++j)
            blocks.emplace_back(chain.getPrevHash(), shrinkPool(pool));

        for (Block block: blocks) {
            if (block.mine(maxNonce)) {
                purgeTransactions(block.getData(), pool);
                block.processTransactions(users);
                chain.appendBlock(block);
//                std::cout << "Mined block " << blockName << std::endl;
                std::cout << block << std::string(50, '-') << std::endl;
                break;7
            } else {
                blockName++;
                maxNonce *= 2;
            }
        }

    }

    for(User u: users) {
        std::cout << u << std::endl;
    }

}