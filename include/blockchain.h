#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "block.h"

class Blockchain {

private:

    std::vector<Block> m_chain;

public:

    Blockchain() {
        std::vector<Transaction> pool(0);
        Block genesisBlock(
                std::string(16, 0),
                pool
        );
        genesisBlock.mine(10000);
        appendBlock(genesisBlock);
    }

    void appendBlock(const Block &block);

    std::string getPrevHash();

    Block getBlockInfo(int blocknumber);

    std::vector<Block> getChain();

    friend std::ostream &operator<<(std::ostream &out, Blockchain chain);

    ~Blockchain() = default;

};