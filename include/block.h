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
    int m_difficulty{3};

    time_t m_timestamp{};

    std::vector<Transaction> m_data;

public:

    Block(std::string prevHash, std::vector<Transaction> data);

    Block() = default;

    std::string getBlockHash() const;

    std::string hashBlock();

    std::vector<Transaction> getData();

    void processTransactions(std::vector<User> &users);

    bool mine(int maxNonce);

    std::string buildMerkleTree();

    friend std::ostream &operator<<(std::ostream &out, Block block);

//    friend std::istream &operator>>(std::istream &in, Block &block);

    ~Block() = default;

};