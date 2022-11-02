#include "blockchain.h"

void Blockchain::appendBlock(const Block &block) {

    m_chain.push_back(block);

}

std::string Blockchain::getPrevHash() {

    return m_chain[m_chain.size() - 1].getBlockHash();

}

void Blockchain::getBlockInfo(int blocknumber) {

    if (blocknumber >= m_chain.size() || blocknumber < 0)
        std::cout << "Entered number is out of range." << std::endl;
    else
        std::cout << m_chain[blocknumber] << std::endl;

}