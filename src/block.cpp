#include "block.h"

Block::Block(std::string prevHash, std::string dataHash) {
    m_dataHash = dataHash;
    m_prevHash = prevHash;
    m_timestamp = time(0);
}

std::string Block::getPrevHash() const { return m_prevHash; };

std::string Block::getDataHash() const { return m_dataHash; };

std::string Block::getBlockHash() const { return m_blockHash; };

int Block::getTimestamp() const { return m_timestamp; };

int Block::getDifficulty() const { return m_difficulty; }

int Block::getNonce() const { return m_nonce; };

void Block::setData(std::vector<Transaction> t) {
    m_data = t;
};

int Block::getDataSize() {
    return m_data.size();
}

std::ostream &operator<<(std::ostream &out, Block block) {

    out << "\nBlock hash: " << block.getBlockHash()
        << "\nPrevious hash: " << block.getPrevHash()
        << "\nData hash: " << block.getDataHash()
        << "\nTimestamp: " << block.getTimestamp()
        << "\nNonce: " << block.getNonce()
        << "\nDifficulty: " << block.getDifficulty()
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