#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "block.h"

class Blockchain {

private:

    std::vector<Block> m_chain;
    int m_difficulty{2};

public:

    Blockchain() {
        Block genesisBlock(
                "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
                "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
                0
        );
        genesisBlock.mine(2);
        appendBlock(genesisBlock);
    }

    void appendBlock(Block block);

    std::string getPrevHash();

    int getDifficulty();

    std::string getBlockInfo(int blockid);

    void print();

    std::vector<Block> getChain();

    friend std::ostream &operator<<(std::ostream &out, Blockchain chain);

};