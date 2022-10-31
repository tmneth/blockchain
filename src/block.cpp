#include "block.h"

Block::Block(std::string prevHash, std::string dataHash, std::vector<Transaction> newPool) {

    m_data = newPool;
    m_dataHash = dataHash;
    m_prevHash = prevHash;
    m_timestamp = time(0);

}

std::string Block::buildMerkleTree() {

    std::vector<std::string> merkle;

    for (auto& tx : m_data) {
        merkle.push_back(hash(hash(tx.getID())));
    }

    if (merkle.empty()) {
        return "null";
    }
    if (merkle.size() == 1) {
        return merkle[0];
    }

    while (merkle.size() != 1)
    {
        std::vector<std::string> temp;

        if (merkle.size() % 2 != 0) {
            merkle.push_back(merkle.back());
        }
        for (size_t i = 0; i < merkle.size(); i+=2)
        {
            temp.push_back(hash(hash(merkle[i] + merkle[i + 1])));
        }
        merkle = temp;
    }
    return merkle[0];
}

std::string Block::getBlockHash() const {

    return m_blockHash;

};

std::ostream &operator<<(std::ostream &out, Block block) {

    out << "\nBlock hash: " << block.m_blockHash
        << "\nPrevious hash: " << block.m_prevHash
        << "\nData hash: " << block.m_dataHash
        << "\nTimestamp: " << block.m_timestamp
        << "\nNonce: " << block.m_nonce
        << "\nDifficulty: " << block.m_difficulty
        << "\nNumber of transactions: " << block.m_data.size() << std::endl;

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