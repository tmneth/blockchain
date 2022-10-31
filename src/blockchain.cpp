#include "blockchain.h"

void Blockchain::appendBlock(Block block) {

    m_chain.push_back(block);

}

std::vector<Block> Blockchain::getChain() {

    return m_chain;

}

std::string Blockchain::getPrevHash() {

    return m_chain[m_chain.size() - 1].getBlockHash();

}

void Blockchain::getBlockInfo(std::string blockhash) {

    auto it = find_if(m_chain.begin(), m_chain.end(),
                      [&blockhash](Block &block) { return block.getBlockHash() == blockhash; });

    if (it != m_chain.end()) {
        int index = std::distance(m_chain.begin(), it);
        std::cout << m_chain[index];
    } else
        std::cout << "Block with this hash does not exist." << std::endl;

}

std::ostream &operator<<(std::ostream &out, Blockchain chain) {

    for (const Block &block: chain.getChain())
        out << block;
    return out;

}