#include "block.h"

Block::Block(std::string prevHash, std::vector<Transaction> data) {

    m_prevHash = prevHash;
    m_data = data;
    m_merkleRoot = buildMerkleTree();
    m_timestamp = time(0);

}

std::string Block::buildMerkleTree() {

    MYSHA hash;

    std::vector<std::string> merkle;

    for (auto &tx: m_data) {
        merkle.push_back(tx.getHash());
    }

    if (merkle.empty()) {
        return "null";
    }
    if (merkle.size() == 1) {
        return merkle[0];
    }

    while (merkle.size() != 1) {
        std::vector<std::string> temp;

        if (merkle.size() % 2 != 0) {
            merkle.push_back(merkle.back());
        }
        for (size_t i = 0; i < merkle.size(); i += 2) {
            temp.push_back(hash(hash(merkle[i] + merkle[i + 1])));
        }
        merkle = temp;
    }
    return merkle[0];
}

int findUser(std::string publicKey, std::vector<User> &users) {

    auto it = find_if(users.begin(), users.end(),
                      [&publicKey](User &user) { return user.getPublicKey() == publicKey; });
    int index = std::distance(users.begin(), it);

    return index;

}

void Block::processTransactions(std::vector<User> &users) {

    int index;

    for (Transaction t: m_data) {

        index = findUser(t.getRecipient(), users);
        users[index].setBalance(users[index].getBalance() + t.getAmount());

        index = findUser(t.getSender(), users);
        users[index].setBalance(users[index].getBalance() - t.getAmount());

    }
}

std::string Block::getBlockHash() const {

    return m_blockHash;

};

std::vector<Transaction> Block::getData() {
    return m_data;
}

std::string Block::hashBlock() {

    MYSHA hash;

    std::string blockhash = hash(
            m_prevHash + m_merkleRoot + std::to_string(m_timestamp) +
            std::to_string(m_nonce));

    return blockhash;

}

bool Block::mine(int maxNonce) {

    std::string targetStr(m_difficulty, '0');

    std::string hash = hashBlock();

    while (hash.substr(0, m_difficulty) != targetStr) {

        hash = hashBlock();

        m_nonce++;

        if (m_nonce > maxNonce * m_difficulty)
            return false;
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
        << "\nDifficulty: " << block.m_difficulty
        << "\nNumber of transactions: " << block.m_data.size() << std::endl;

    return out;

}

//std::istream &operator>>(std::istream &in, Block &block) {
//
//    in >> block.m_blockHash
//       >> block.m_prevHash
//       >> block.m_merkleRoot
//       >> block.m_timestamp
//       >> block.m_nonce
//       >> block.m_difficulty;
//
//    return in;
//
//}
