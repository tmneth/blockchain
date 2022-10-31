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
                "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
                "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
                pool
        );
        genesisBlock.mine();
        appendBlock(genesisBlock);
    }

    void appendBlock(Block block);

    std::string getPrevHash();

    void getBlockInfo(std::string blockhash);

    std::vector<Block> getChain();

    friend std::ostream &operator<<(std::ostream &out, Blockchain chain);

};