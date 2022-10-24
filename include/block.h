#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <vector>

#include "transaction.h"

class Block {
//
//protected:
//    Block(int m_index, std::string prevHash, std::string dataHash, std::string blockHash, int m_nonce);

private:

    int m_index{};
    std::string m_prevHash{};
    std::string m_dataHash{};
    std::string m_blockHash{};
    int m_nonce{};
    int m_timeStamp{};
    std::vector<Transaction> m_data{};
    int m_difficultyTarget{};

public:

    Block(std::string prevHash, std::string dataHash, int index);

    std::string getPrevHash() const;

    std::string getDataHash() const;

    std::string getBlockHash() const;

    int getNonce() const;

    int getIndex() const;

    void setData(std::vector<Transaction> t);

    std::string getBlockProps();

    bool mine(int difficultyTarget);

    friend std::ostream &operator<<(std::ostream &out, Block block);

    ~Block() = default;

};