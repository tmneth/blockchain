#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "transaction.h"

class Pool {
    
private:

    std::vector<Transaction> m_pool;

public:

    void getTransactionInfo(int txId);

    int getPoolSize();

    void addTransaction(Transaction transaction);

    void removeTransaction(int txId);

    void removeByTxId(int txId);

    std::vector<Transaction> getPool();

    Transaction getTransaction(int txId);

    std::string genMerkleHash();

};
