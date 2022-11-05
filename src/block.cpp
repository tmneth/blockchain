#include "block.h"

Block::Block(std::string prevHash, std::vector<Transaction> pool) {

    m_prevHash = std::move(prevHash);
    m_data = pool;
    m_merkleRoot = buildMerkleTree();
    m_timestamp = time(nullptr);

}

std::string Block::buildMerkleTree() {

    MYSHA hash;

    std::string node;

    std::vector<std::string> merkle;

    for (Transaction &tx: m_data)
        merkle.push_back(tx.getHash());

    if (merkle.empty())
        return "null_hash";

    if (merkle.size() == 1)
        return merkle[0];

    while (merkle.size() > 1) {
        std::vector<std::string> temp;

        if (merkle.size() % 2 != 0)
            merkle.push_back(merkle.back());

        for (int i = 0; i < merkle.size(); i += 2) {
            node = hash(hash(merkle[i] + merkle[i + 1]));
            temp.push_back(node);
        }

        merkle = temp;

    }
    return merkle[0];

}

std::string Block::getBlockHash() const {

    return m_blockHash;

};

std::string Block::hashBlock() {

    MYSHA hash;

    std::string blockhash = hash(
            m_prevHash + m_merkleRoot + std::to_string(m_timestamp) +
            std::to_string(m_nonce));

    return blockhash;

}

bool Block::mine(bool isMined) {

    std::string targetStr(DIFFICULTY_TARGET, '0');

    std::string hash = hashBlock();

    while (hash.substr(0, DIFFICULTY_TARGET) != targetStr) {

#pragma omp flush(isMined)
        if (isMined)
            return false;

        hash = hashBlock();

        m_nonce++;

    }

    m_blockHash = hash;
    return true;

}

std::ostream &operator<<(std::ostream &out, Block block) {

    out << "Block hash: " << block.m_blockHash
        << "\nPrevious hash: " << block.m_prevHash
        << "\nMerkle root: " << block.m_merkleRoot
        << "\nTimestamp: " << block.m_timestamp
        << "\nNonce: " << block.m_nonce
        << "\nDifficulty: " << DIFFICULTY_TARGET
        << "\nNumber of transactions: " << block.m_data.size() << std::endl;

    out << "\nTransaction list: " << std::endl;
    for (Transaction transaction: block.m_data)
        out << transaction << std::endl;

    return out;

}