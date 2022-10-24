#include "block.h"
#include "hash.h"
#include <algorithm>

Block::Block(std::string prevHash, std::string dataHash, int index) {
    m_index = index;
    m_dataHash = dataHash;
    m_prevHash = prevHash;
    m_timeStamp = time(0);
}

std::string Block::getPrevHash() const { return m_prevHash; };

std::string Block::getDataHash() const { return m_dataHash; };

std::string Block::getBlockHash() const { return m_blockHash; };

int Block::getNonce() const { return m_nonce; };

int Block::getIndex() const { return m_index; };

void Block::setData(std::vector<Transaction> t) {
    m_data = t;
};

std::string Block::getBlockProps() {
    std::stringstream stream;

    stream << "\nId: " << m_index << "\nBlock hash: " << m_blockHash << "\nPrevious hash: " << m_prevHash
              << "\nData hash: " << m_dataHash << "\nNonce: " << m_nonce << std::endl;

    return stream.str();
}

std::ostream &operator<<(std::ostream &out, Block block) {
    out << block.getIndex() << " " << block.getBlockHash() << " " << block.getPrevHash() << " " << block.getDataHash()
        << " " << block.getNonce() << std::endl;
    return out;
}

bool Block::mine(int difficultyTarget) {

    for (int nonce = 0; nonce < 100000000; ++nonce) {
        MYSHA mysha;

        std::string targetStr(difficultyTarget, '0');

        std::string hash = mysha(
                std::to_string(m_index) + m_prevHash + m_dataHash + std::to_string(m_timeStamp) +
                std::to_string(nonce));

        if (hash.substr(0, difficultyTarget) == targetStr) {

            m_nonce = nonce;
            m_blockHash = hash;

            return true;
        }
    }
    return false;
}