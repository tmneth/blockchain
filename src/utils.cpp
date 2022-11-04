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

    std::vector<User> tempUsers(users);
    std::vector<Transaction> tempPool(pool);


    for (int i = 0; !pool.empty(); i++) {

        char blockName = 'a';
        int maxNonce = 10000;
        bool isMined = false;

        while (!isMined) {

            for (int j = 0; j < CANDIDATES; j++) {

                Block block(chain.getPrevHash(), selectTransactions(tempPool, tempUsers));

                if (block.mine(maxNonce)) {
                    pool = tempPool;
                    users = tempUsers;

                    std::ofstream fout("blocks/block" + std::to_string(i) + ".txt");
                    fout << block;
                    fout.close();

                    chain.appendBlock(block);
                    std::cout << "Mined block " << blockName << std::endl;

                    isMined = true;
                    break;
                } else {
                    tempPool = pool;
                    tempUsers = users;
                    blockName++;
                    continue;
                }
            }
            if (!isMined) {
                maxNonce *= 2;
            }
        }
    }
//
//    std::cout << "User details:" << std::endl;
//    for (int i = 0; i < users.size(); ++i) {
//        std::cout << oldUsers[i].getName() << " " << oldUsers[i].getPublicKey() << " | $" << oldUsers[i].getBalance()
//                  << " -> $" << users[i].getBalance() << std::endl;
//    }
}