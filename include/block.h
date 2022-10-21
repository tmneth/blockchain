#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <vector>

class Block {

private:

    int m_index{};
    std::string m_prevHash{};
    std::string m_blockHash{};
    std::string m_nonce{};
    int m_timeStamp{};
    int m_difficultyTarget{};
    std::vector<std::string> m_data;

public:

    Block(int index, std::string &prevHash, std::string &blockHash, std::string nonce, std::vector<std::string> data);

    std::string getPrevHash() const;

    std::string getBlockHash() const;

    int getIndex() const;

};