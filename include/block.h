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
    time_t m_timestamp{};
    int m_difficulty{1};

    std::vector<Transaction> m_data{};

public:

    Block(std::string prevHash, std::string dataHash);

    std::string getPrevHash() const;

    std::string getDataHash() const;

    std::string getBlockHash() const;

    int getTimestamp() const;

    int getNonce() const;

    int getDifficulty() const;

    void setData(std::vector<Transaction> t);

    int getDataSize();

    bool mine();

    friend std::ostream &operator<<(std::ostream &out, Block block);

    ~Block() = default;

};