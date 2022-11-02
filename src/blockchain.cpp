#include "blockchain.h"

void Blockchain::appendBlock(const Block &block) {

    m_chain.push_back(block);

}

std::vector<Block> Blockchain::getChain() {

    return m_chain;

}

std::string Blockchain::getPrevHash() {

    return m_chain[m_chain.size() - 1].getBlockHash();

}

Block Blockchain::getBlockInfo(int blocknumber) {

    if (blocknumber >= m_chain.size() || blocknumber < 0)
        std::cout << "Entered number is out of range." << std::endl;
    else
        return m_chain[blocknumber];

}

std::ostream &operator<<(std::ostream &out, Blockchain chain) {

    for (const Block &block: chain.getChain())
        out << block;
    return out;

}