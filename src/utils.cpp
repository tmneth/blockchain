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

int findUser(std::string publicKey, std::vector<User> &users) {

    auto it = find_if(users.begin(), users.end(),
                      [&publicKey](User &user) { return user.getPublicKey() == publicKey; });
    int index = std::distance(users.begin(), it);

    return index;

}

void processTransactions(Pool pool, std::vector<User> &users) {

    std::string publicKey;
    int index;

    for (Transaction t: pool.getPool()) {

        index = findUser(t.getRecipient(), users);
        users[index].setBalance(users[index].getBalance() + t.getAmount());

        index = findUser(t.getSender(), users);
        users[index].setBalance(users[index].getBalance() - t.getAmount());

        int txId = t.getId();

        pool.removeByTxId(txId);

    }

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

        processTransactions(newPool, users);
    }

    std::cout << chain << std::endl;

}