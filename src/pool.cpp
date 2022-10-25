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

int Pool::getPoolSize() {
    return m_pool.size();
}

void Pool::addTransaction(Transaction transaction) {
    m_pool.push_back(transaction);
}

void Pool::removeTransaction(int txId) {
    std::swap(m_pool[txId], m_pool.back());
    m_pool.pop_back();
}

Transaction Pool::getTransaction(int txId) {
    return m_pool[txId];
}

std::vector<Transaction> Pool::getPool() {
    return m_pool;
}

void Pool::removeByTxId(int txId) {

    auto transactionIt = find_if(m_pool.begin(), m_pool.end(),
                                 [&txId](Transaction &t) { return t.getId() == txId; });
    m_pool.erase(transactionIt);

}

std::string Pool::genMerkleHash() {

    MYSHA hash;

    std::string dataHash;

    for (Transaction t: m_pool)
        dataHash += t.getHash();

    return hash(dataHash);
}