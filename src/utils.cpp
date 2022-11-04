#include "utils.h"

double genRandAmount() {

    std::mt19937 mt{std::random_device{}()};
    std::uniform_real_distribution<> amount(1000.0, 99999.0);

    return amount(mt);
}

void genUsers(std::vector<User> &users) {

    for (int i = 1; i <= USER_NUM; ++i) {
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

void purgeTransactions(std::vector<Transaction> newPool, std::vector<Transaction> &pool) {

    for (Transaction &tx: newPool) {
        auto it = std::find_if(pool.begin(), pool.end(),
                               [&tx](const Transaction &t) { return t.getId() == tx.getId(); });
        pool.erase(it);
    }

}

int findUser(std::string publicKey, std::vector<User> &users) {

    auto it = find_if(users.begin(), users.end(),
                      [&publicKey](User &user) { return user.getPublicKey() == publicKey; });
    int index = std::distance(users.begin(), it);

    return index;

}

std::vector<Transaction> processTransactions(std::vector<Transaction> &pool, std::vector<User> &users) {

    if (pool.size() < REDUCED_TRANSACTION_NUM) {
        return pool;
    } else {

        std::vector<Transaction> newPool;
        MYSHA hash;
        std::vector<int> randInd;

        for (int i = 0; i < REDUCED_TRANSACTION_NUM; ++i)
            randInd.push_back(i);

        std::shuffle(randInd.begin(), randInd.end(), std::mt19937(std::random_device()()));

        for (int i = 0; i < REDUCED_TRANSACTION_NUM; ++i) {

            int index = randInd[i];

            int senderId = findUser(pool[index].getSender(), users);
            int recipientId = findUser(pool[index].getRecipient(), users);

            double txAmount = pool[index].getAmount();

            if (users[senderId].getBalance() >= txAmount &&
                hash(users[senderId].getPublicKey()
                     + users[recipientId].getPublicKey()
                     + std::to_string(pool[index].getAmount())
                     + std::to_string(pool[index].getTimestamp()))
                == pool[index].getHash()) {

                newPool.push_back(pool[index]);

                users[senderId].setBalance(users[senderId].getBalance() - txAmount);

                users[recipientId].setBalance(users[recipientId].getBalance() + txAmount);

            } else {
                pool.erase(pool.begin() + index);
            }

        }
        return newPool;
    }
}

void initBlockchain(Blockchain &chain, std::vector<Transaction> pool, std::vector<User> &users) {

    std::filesystem::create_directories("blocks");

    genUsers(users);
    genPool(users, pool);
    std::vector<User> oldUsers(users);

    for (int i = 0; !pool.empty(); i++) {
        std::vector<Transaction> newPool;
        std::vector<Block> blocks;
        char blockName = 'a';
        int maxNonce = 10000;

        for (int j = 0; j < 5; ++j)

            blocks.emplace_back(chain.getPrevHash(), processTransactions(pool, users));

        for (Block block: blocks) {

            if (block.mine(maxNonce)) {

                purgeTransactions(block.getData(), pool);

                std::ofstream fout("blocks/block" + std::to_string(i) + ".txt");
                fout << block;
                fout.close();

                chain.appendBlock(block);
                std::cout << "Mined block " << blockName << std::endl;
                break;

            } else {

                blockName++;
                maxNonce *= 2;

            }
        }
    }

    std::cout << "User details:" << std::endl;
    for (int i = 0; i < users.size(); ++i) {
        std::cout << oldUsers[i].getName() << " " << oldUsers[i].getPublicKey() << " | $" << oldUsers[i].getBalance()
                  << " -> $" << users[i].getBalance() << std::endl;
    }
}