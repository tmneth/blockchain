#include "block.h"

Block::Block(std::string prevHash, std::string dataHash) {
    m_dataHash = dataHash;
    m_prevHash = prevHash;
    m_timestamp = time(0);
}

std::string Block::getBlockHash() const { return m_blockHash; };

void Block::setData(std::vector<Transaction> t) {
    m_data = t;
};

int Block::getDataSize() {
    return m_data.size();
}

std::ostream &operator<<(std::ostream &out, Block block) {

    out << "\nBlock hash: " << block.m_blockHash
        << "\nPrevious hash: " << block.m_prevHash
        << "\nData hash: " << block.m_dataHash
        << "\nTimestamp: " << block.m_timestamp
        << "\nNonce: " << block.m_nonce
        << "\nDifficulty: " << block.m_difficulty
        << "\nNumber of transactions: " << block.getDataSize() << std::endl;

    return out;
}

bool Block::mine() {

    for (int nonce = 0; nonce < 100000000; ++nonce) {
        MYSHA mysha;

        std::string targetStr(m_difficulty, '0');

        std::string hash = mysha(
                m_prevHash + m_dataHash + std::to_string(m_timestamp) +
                std::to_string(nonce));

        if (hash.substr(0, m_difficulty) == targetStr) {

            m_nonce = nonce;
            m_blockHash = hash;

            return true;
        }
    }
    return false;
}