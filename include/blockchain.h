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

    Blockchain() = default;

    void appendBlock(const Block &block);

    std::string getPrevHash();

    ~Blockchain() = default;

};