#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "transaction.h"
#include "user.h"

class Pool {

private:

    std::vector<Transaction> m_pool;

public:

    void getTransactionInfo(int txId);

    int getPoolSize();

    void addTransaction(const Transaction& transaction);

    void removeTransaction(int txId);

    void processTransactions(std::vector<User> &users);

    Transaction getTransaction(int txId);

    std::string genMerkleHash();

};
