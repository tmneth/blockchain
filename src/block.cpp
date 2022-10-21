#include "block.h"

Block::Block(int index, std::string &prevHash, std::string &blockHash, std::string nonce, std::vector<std::string> data) {
    this->m_index = index;
    this->m_data = data;
    this->m_prevHash = prevHash;
    this->m_blockHash = blockHash;
    m_timeStamp = time(0);
}

std::string Block::getPrevHash() const { return this->m_prevHash; };

std::string Block::getBlockHash() const { return this->m_blockHash; };

int Block::getIndex() const { return this->m_index; };