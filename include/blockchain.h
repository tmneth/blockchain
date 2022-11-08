#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "block.h"

class Blockchain {

private:

    std::vector <Block> m_chain;
    std::string m_name{"main"};

public:

    Blockchain() = default;

    void appendBlock(const Block &block);

    std::string getPrevHash();

    void getBlock(std::string blockhash);

    void getBlockchaininfo();

    void getBlockchaininfo(int &blocks);

    void getRawtransaction(std::string txid);

    Json::Value toJSON();

    ~Blockchain() = default;

};