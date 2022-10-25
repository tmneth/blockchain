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

void genPool(std::vector<User> &users, Pool &pool) {

    std::random_device device;
    std::mt19937 mt(device());
    std::uniform_int_distribution<int> seed(0, 999);

    for (int i = 1; i <= 10000; ++i) {

        int randUser1 = seed(mt);
        int randUser2 = seed(mt);
        double amount = genRandAmount();

        while (randUser1 == randUser2)
            randUser1 = seed(mt);

        while (users[randUser1].getBalance() < amount)
            amount = genRandAmount();


        Transaction transaction;

        transaction.setId(i);

        transaction.setAmount(amount);

        transaction.setSender(users[randUser1].getPublicKey());
        transaction.setRecipient(users[randUser2].getPublicKey());

        transaction.setHash();

        pool.addTransaction(transaction);
    }

}

Pool shrinkPool(Pool &pool) {

    Pool newPool;

    for (int i = 0; i < 100; ++i) {

        std::random_device device;
        std::mt19937 mt(device());
        std::uniform_int_distribution<int> seed(0, pool.getPoolSize() - 1);

        int index = seed(mt);

        newPool.addTransaction(pool.getTransaction(index));

        pool.removeTransaction(index);
    }

    return newPool;

}

void initBlockchain(Blockchain &chain, Pool pool, std::vector<User> users) {

    Pool newPool;

    std::string dataHash;

    for (int i = 1; pool.getPoolSize(); i++) {

        newPool = shrinkPool(pool);

        dataHash = newPool.genMerkleHash();

        Block newBlock(chain.getPrevHash(), dataHash);

        newBlock.setData(newPool);

        if (newBlock.mine())
            chain.appendBlock(newBlock);

        newPool.processTransactions(users);
    }

    std::cout << chain << std::endl;

}