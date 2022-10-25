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

        std::swap(pool[index], pool.back());
        pool.pop_back();

        newPool.push_back(pool[index]);
    }

    return newPool;

}

std::string genMerkleTree(std::vector<Transaction> pool) {

    MYSHA mysha;

    std::string dataHash;

    for (Transaction t: pool)
        dataHash += t.getHash();

    return mysha(dataHash);

}

int findUser(std::string publicKey, std::vector<User> &users) {

    auto it = find_if(users.begin(), users.end(),
                      [&publicKey](User &user) { return user.getPublicKey() == publicKey; });
    int index = std::distance(users.begin(), it);

    return index;

}

int getTransaction(std::vector<Transaction> &pool, int id) {

    auto it = find_if(pool.begin(), pool.end(),
                      [&id](Transaction &t) { return t.getId() == id; });

    int index = std::distance(pool.begin(), it);

    return index;
}

void processTransactions(std::vector<Transaction> &pool, std::vector<User> &users) {

    std::string publicKey;
    int index;

    for (Transaction t: pool) {

        index = findUser(t.getRecipient(), users);
        users[index].setBalance(users[index].getBalance() + t.getAmount());

        index = findUser(t.getSender(), users);
        users[index].setBalance(users[index].getBalance() - t.getAmount());

        int transactionId = t.getId();

        auto transactionIt = find_if(pool.begin(), pool.end(),
                                     [&transactionId](Transaction &t) { return t.getId() == transactionId; });
        pool.erase(transactionIt);

    }

}

void initBlockchain(Blockchain &chain, std::vector<Transaction> pool, std::vector<User> users) {

    std::vector<Transaction> newPool;

    std::string dataHash;

    for (int i = 1; pool.size(); i++) {

        newPool = shrinkPool(pool);

        dataHash = genMerkleTree(newPool);

        Block newBlock(chain.getPrevHash(), dataHash);

        newBlock.setData(newPool);

        if (newBlock.mine())
            chain.appendBlock(newBlock);

        processTransactions(newPool, users);
    }

    std::cout << chain << std::endl;

}