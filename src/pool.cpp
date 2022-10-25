#include "pool.h"


void Pool::getTransactionInfo(int txId) {

    auto it = find_if(m_pool.begin(), m_pool.end(),
                      [&txId](Transaction &transaction) { return transaction.getId() == txId; });

    if (it != m_pool.end()) {
        int index = std::distance(m_pool.begin(), it);
        std::cout << m_pool[index];
    } else
        std::cout << "Transaction with this id does not exist." << std::endl;

}

int Pool::getPoolSize() { return m_pool.size(); }

void Pool::addTransaction(const Transaction &transaction) { m_pool.push_back(transaction); }

Transaction Pool::getTransaction(int txId) { return m_pool[txId]; }

void Pool::removeTransaction(int txId) {

    auto transactionIt = find_if(m_pool.begin(), m_pool.end(),
                                 [&txId](Transaction &t) { return t.getId() == txId; });
    m_pool.erase(transactionIt);

}

std::string Pool::genMerkleHash() {

    MYSHA hash;

    std::string dataHash;

    for (const Transaction &t: m_pool)
        dataHash += t.getHash();

    return hash(dataHash);

}

int findUser(std::string publicKey, std::vector<User> &users) {

    auto it = find_if(users.begin(), users.end(),
                      [&publicKey](User &user) { return user.getPublicKey() == publicKey; });
    int index = std::distance(users.begin(), it);

    return index;

}

void Pool::processTransactions(std::vector<User> &users) {

    std::string publicKey;

    int index;

    for (Transaction t: m_pool) {

        index = findUser(t.getRecipient(), users);
        users[index].setBalance(users[index].getBalance() + t.getAmount());

        index = findUser(t.getSender(), users);
        users[index].setBalance(users[index].getBalance() - t.getAmount());

        int txId = t.getId();

        removeTransaction(txId);

    }
    
}