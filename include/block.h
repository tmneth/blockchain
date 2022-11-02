#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <algorithm>
#include <vector>
#include "transaction.h"
#include "hash.h"
#include "user.h"

class Block {

private:

    std::string m_prevHash{};
    std::string m_blockHash{};
    std::string m_merkleRoot{};
    int m_nonce{};
    int m_difficulty{2};
    time_t m_timestamp{};
    std::vector<Transaction> m_data;

public:

    Block(std::string prevHash, std::vector<Transaction> pool);

    std::string getBlockHash() const;

    std::vector<Transaction> getData() const;

    std::string hashBlock();

    void processTransactions(std::vector<Transaction> pool, std::vector<User> &users);

    bool mine(int maxNonce);

    std::string buildMerkleTree(std::vector<Transaction> pool);

    friend std::ostream &operator<<(std::ostream &out, Block block);

    ~Block() = default;

};

int findUser(std::string publicKey, std::vector<User> &users);