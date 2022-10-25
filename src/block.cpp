#include "block.h"

Block::Block(std::string prevHash, std::string dataHash) {

    m_dataHash = dataHash;
    m_prevHash = prevHash;
    m_timestamp = time(0);
    
}

std::string Block::getBlockHash() const { return m_blockHash; };

void Block::setData(Pool pool) { m_data = pool; };

int Block::getDataSize() { return m_data.getPoolSize(); }

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

std::string Block::hashBlock() {

    MYSHA hash;

    std::string blockhash = hash(
            m_prevHash + m_dataHash + std::to_string(m_timestamp) +
            std::to_string(m_nonce));

    return blockhash;

}

bool Block::mine() {

    std::string targetStr(m_difficulty, '0');

    std::string hash = hashBlock();

    while (hash.substr(0, m_difficulty) != targetStr) {

        hash = hashBlock();

        m_nonce++;

        if (m_nonce > 10000 * m_difficulty)
            return false;
    }

    m_blockHash = hash;
    return true;

}