#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <algorithm>
#include <vector>
#include "transaction.h"
#include "hash.h"

class Block {

private:

    std::string m_prevHash{};
    std::string m_dataHash{};
    std::string m_blockHash{};

    int m_nonce{};
    int m_difficulty{2};

    time_t m_timestamp{};

    std::vector <Transaction> m_data{};

public:

    Block(std::string prevHash, std::string dataHash, std::vector<Transaction> newPool);

    std::string getBlockHash() const;

    std::string hashBlock();

    bool mine();

    std::string buildMerkleTree();

    friend std::ostream &operator<<(std::ostream &out, Block block);

    ~Block() = default;

};