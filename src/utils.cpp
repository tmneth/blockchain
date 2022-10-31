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
    std::uniform_int_distribution<int> seed(0, users.size()-1);

    for (int i = 1; i <= 10000; ++i) {

        double amount =  genRandAmount();

        int randUser1 = seed(mt);
        int randUser2 = seed(mt);

        while (randUser1 == randUser2)
            randUser1 = seed(mt);

        while(amount > users[randUser1].getBalance())
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

void removeTransaction(int txId, std::vector<Transaction> &pool) {

    auto transactionIt = find_if(pool.begin(), pool.end(),
                                 [&txId](Transaction &t) { return t.getId() == txId; });
    pool.erase(transactionIt);

}


std::vector<Transaction> shrinkPool(std::vector<Transaction> &pool) {

    std::vector<Transaction> newPool;

    for (int i = 0; i < 100; ++i) {

        std::random_device device;
        std::mt19937 mt(device());
        std::uniform_int_distribution<int> seed(0, pool.size() - 1);

        int index = seed(mt);

        newPool.push_back(pool[index]);

        removeTransaction(index, pool);
    }


    return newPool;

}

int findUser(std::string publicKey, std::vector<User> &users) {

    auto it = find_if(users.begin(), users.end(),
                      [&publicKey](User &user) { return user.getPublicKey() == publicKey; });
    int index = std::distance(users.begin(), it);

    return index;

}

void processTransactions(std::vector<User> &users, std::vector<Transaction> pool) {

    std::string publicKey;

    int index;

    for (Transaction t: pool) {

        index = findUser(t.getRecipient(), users);
        users[index].setBalance(users[index].getBalance() + t.getAmount());

        index = findUser(t.getSender(), users);
        users[index].setBalance(users[index].getBalance() - t.getAmount());

        int txId = t.getId();

        removeTransaction(txId, pool);

    }

}

void initBlockchain(Blockchain &chain, std::vector<Transaction> pool, std::vector<User> &users) {

    std::vector<Transaction> newPool;

    std::string dataHash;

    for (int i = 1; pool.size(); i++) {

        newPool = shrinkPool(pool);

        Block newBlock(chain.getPrevHash(), dataHash, newPool);

        if (newBlock.mine())
            chain.appendBlock(newBlock);

        processTransactions(users, newPool);
    }

    std::cout << chain << std::endl;
//
//    for(const User& u: users) {
//        std::cout << u << std::endl;
//    }

}