#include <random>
#include <set>
#include <utility>
#include "block.h"

Block::Block(std::string prevHash, std::vector<Transaction> pool) {

    m_prevHash = std::move(prevHash);
    m_data = std::move(pool);
    m_timestamp = time(nullptr);

}

std::string Block::buildMerkleTree(std::vector<Transaction> pool) {

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

void Block::processTransactions(std::vector<Transaction> pool, std::vector<User> &users) {

    std::vector<Transaction> newPool;

    MYSHA hash;


    for (int i = 0; i < 100; ++i) {

        int senderId = findUser(pool[i].getSender(), users);
        int recipientId = findUser(pool[i].getRecipient(), users);

        double txAmount = pool[i].getAmount();

        if (users[senderId].getBalance() >= txAmount &&
            hash(users[senderId].getPublicKey()
                 + users[recipientId].getPublicKey()
                 + std::to_string(pool[i].getAmount())
                 + std::to_string(pool[i].getTimestamp()))
            == pool[i].getHash()) {

            newPool.push_back(pool[i]);

            users[senderId].setBalance(users[senderId].getBalance() - txAmount);

            users[recipientId].setBalance(users[recipientId].getBalance() + txAmount);

        }

    }

    m_merkleRoot = buildMerkleTree(newPool);

}

std::string Block::getBlockHash() const {

    return m_blockHash;

};

std::vector<Transaction> Block::getData() const {

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

    out << "\nBlock hash: " << block.m_blockHash
        << "\nPrevious hash: " << block.m_prevHash
        << "\nMerkle root: " << block.m_merkleRoot
        << "\nTimestamp: " << block.m_timestamp
        << "\nNonce: " << block.m_nonce
        << "\nDifficulty: " << block.m_difficulty
        << "\nNumber of transactions: " << block.m_data.size() << std::endl;

    std::cout << "\nTransaction list: " << std::endl;
    for (Transaction transaction: block.m_data)
        std::cout << transaction << std::endl;

    return out;

}