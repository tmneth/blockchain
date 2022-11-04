#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <algorithm>
#include <vector>
#include "transaction.h"
#include "hash.h"
#include "user.h"
#include "constants.h"

class Block {

private:

    std::string m_prevHash{};
    std::string m_blockHash{};
    std::string m_merkleRoot{};
    int m_nonce{};
    time_t m_timestamp{};
    std::vector<Transaction> m_data;

public:

    Block(std::string prevHash, std::vector<Transaction> pool);

    std::string getBlockHash() const;

    std::string hashBlock();

    bool mine(bool flag);

    std::string buildMerkleTree();

    friend std::ostream &operator<<(std::ostream &out, Block block);

    ~Block() = default;

};