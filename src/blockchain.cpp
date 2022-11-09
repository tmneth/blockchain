#include "blockchain.h"

void Blockchain::appendBlock(const Block &block) {

    m_chain.push_back(block);

}

std::string Blockchain::getPrevHash() {

    return m_chain.empty()
           ? "AEEBAD4A796FCC2E15DC4C6061B45ED9B373F26ADFC798CA7D2D8CC58182718E"
           : m_chain[m_chain.size() - 1].getBlockHash();

}

void Blockchain::getBlockchaininfo(int &blocks) {

    Json::Value root;
    std::ifstream readChain("blockchaininfo.json");
    readChain >> root;
    readChain.close();
    blocks = root.get("blocks", 0).asInt();

}

void Blockchain::getBlockchaininfo() {

    Json::Value root;
    std::ifstream readChain("blockchaininfo.json");
    readChain >> root;
    readChain.close();
    std::cout << root << std::endl;

}

void Blockchain::getBlock(std::string blockhash) {

    int blocks;
    Json::Value root;
    getBlockchaininfo(blocks);

    for (int i = 0; i < blocks; i++) {
        std::ifstream readBlock("blocks/block" + std::to_string(i) + "/block.json");
        readBlock >> root;
        if (root["hash"] == blockhash) {
            std::cout << root << std::endl;
            return;
        }
    }
    std::cout << "No block with provided hash was found" << std::endl;
}

void Blockchain::getRawtransaction(std::string txid) {
    int blocks;
    Json::Value root;
    getBlockchaininfo(blocks);
    for (int i = 0; i < blocks; i++) {
        std::ifstream readBlock("blocks/block" + std::to_string(i) + "/block.json");
        readBlock >> root;
        readBlock.close();
        int txNum = root.get("nTx", 0).asInt();
        for (int j = 0; j < txNum; ++j) {
            std::ifstream readTx("blocks/block" + std::to_string(i) + "/tx" + std::to_string(j) + ".json");
            readTx >> root;
            readTx.close();
            if (root["txid"] == txid) {
                std::cout << root << std::endl;
                return;
            }
        }
    }
    std::cout << "No transaction with provided txid was found" << std::endl;

}

Json::Value Blockchain::toJSON() {

    Json::Value rootJsonValue;

    rootJsonValue["chain"] = m_name;
    rootJsonValue["blocks"] = (int) m_chain.size();
    rootJsonValue["headers"] = (int) m_chain.size();
    rootJsonValue["difficulty"] = DIFFICULTY_TARGET;
    rootJsonValue["bestblockhash"] = m_chain[m_chain.size() - 1].getBlockHash();

    return rootJsonValue;

}