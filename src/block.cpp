#include "block.h"

Block::Block(std::string prevHash, std::vector<Transaction> pool, int height) {

    m_prevHash = std::move(prevHash);
    m_data = pool;
    m_height = height;
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

std::vector<Transaction> Block::getData() const {

    return m_data;

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

Json::Value Block::toJSON() {

    Json::Value transactions;

    for (int i = 0; i < m_data.size(); ++i)
        transactions[i] = Json::Value(m_data[i].getHash());

    Json::Value rootJsonValue;

    rootJsonValue["hash"] = m_blockHash;
    rootJsonValue["merkleroot"] = m_merkleRoot;
    rootJsonValue["previousblockhash"] = m_prevHash;
    rootJsonValue["nonce"] = m_nonce;
    rootJsonValue["height"] = m_height;
    rootJsonValue["difficulty"] = DIFFICULTY_TARGET;
    rootJsonValue["time"] = (int) m_timestamp;
    rootJsonValue["tx"] = transactions;
    rootJsonValue["nTx"] = (int) m_data.size();

    return rootJsonValue;

}