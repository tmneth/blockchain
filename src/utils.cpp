#include "utils.h"

double genRandAmount() {

    std::mt19937 mt{std::random_device{}()};
    std::uniform_real_distribution<> amount(1000.0, 99999.0);

    return amount(mt);
}

void genUsers(std::vector<User> &users) {

    for (int i = 0; i < USER_NUM; ++i) {
        User user("user" + std::to_string(i), genRandAmount());

        users.push_back(user);
    }

}

void genPool(std::vector<User> &users, std::vector<Transaction> &pool) {

    std::random_device device;
    std::mt19937 mt(device());
    std::uniform_int_distribution<int> seed(0, users.size() - 1);


    for (int i = 0; i < TRANSACTION_NUM; ++i) {
        double amount = genRandAmount();

        int randUser1 = seed(mt);
        int randUser2 = seed(mt);

        Transaction transaction;

        transaction.setId(i);

        transaction.setAmount(amount);

        transaction.setSender(users[randUser1].getPublicKey());
        transaction.setRecipient(users[randUser2].getPublicKey());

        transaction.setHash();

        pool.push_back(transaction);
    }

}

int findUser(std::string publicKey, std::vector<User> &users) {

    auto it = find_if(users.begin(), users.end(),
                      [&publicKey](User &user) { return user.getPublicKey() == publicKey; });
    int index = std::distance(users.begin(), it);

    return index;

}

std::vector<Transaction> selectTransactions(std::vector<Transaction> &pool, std::vector<User> &users) {

    std::vector<Transaction> newPool;
    MYSHA hash;

    std::random_device device;
    std::mt19937 mt(device());

    while (newPool.size() < REDUCED_TRANSACTION_NUM && !pool.empty()) {

        std::uniform_int_distribution<int> seed(0, pool.size() - 1);

        int index = seed(mt);

        int senderId = findUser(pool[index].getSender(), users);
        int recipientId = findUser(pool[index].getRecipient(), users);

        double txAmount = pool[index].getAmount();

        if (users[senderId].getBalance() >= txAmount
            &&
            hash(users[senderId].getPublicKey()
                 + users[recipientId].getPublicKey()
                 + std::to_string(pool[index].getAmount())
                 + std::to_string(pool[index].getTimestamp()))
            == pool[index].getHash()) {

            newPool.push_back(pool.at(index));

            users[senderId].setBalance(users[senderId].getBalance() - txAmount);

            users[recipientId].setBalance(users[recipientId].getBalance() + txAmount);

        }

        pool.erase(pool.begin() + index);

    }

    return newPool;
}

void initBlockchain(Blockchain &chain, std::vector<Transaction> pool, std::vector<User> &users) {

    std::filesystem::create_directories("blocks");

    genUsers(users);
    genPool(users, pool);

    std::vector<User> oldUsers(users);


    for (int i = 0; !pool.empty(); i++) {

        bool isMined = false;

#pragma omp parallel for shared(isMined) num_threads(THREAD_NUM)
        for (int j = 0; j < THREAD_NUM; j++) {

            if (isMined) continue;

            std::vector<User> tempUsers(users);
            std::vector<Transaction> tempPool(pool);

            Block block(chain.getPrevHash(), selectTransactions(tempPool, tempUsers));

            if (block.mine(isMined)) {

#pragma omp flush(isMined)
                isMined = true;

#pragma omp critical
                {
                    pool = tempPool;
                    users = tempUsers;

                    std::ofstream fout("blocks/block" + std::to_string(i) + ".txt");
                    fout << block;
                    fout.close();

                    chain.appendBlock(block);
                    std::cout << "Thread " << omp_get_thread_num() << " mined " << i << " block" << std::endl;
                }
            }
        }
    }

    std::cout << "\nUser details:" << std::endl;

    for (int i = 0; i < users.size(); ++i) {
        std::cout << "\nName: " << users[i].getName()
                  << "\nPublic key: " << users[i].getPublicKey()
                  << "\nBalance: " << oldUsers[i].getBalance() << " -> " << users[i].getBalance() << std::endl;
    }
}
