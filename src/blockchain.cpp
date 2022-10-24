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

std::string Blockchain::getBlockInfo(int blockid) {

    auto it = find_if(m_chain.begin(), m_chain.end(), [&blockid](Block &block) { return block.getIndex() == blockid; });
    int index = std::distance(m_chain.begin(), it);

    return m_chain[index].getBlockProps();
}

int Blockchain::getDifficulty() {
    return m_difficulty;
}

std::ostream &operator<<(std::ostream &out, Blockchain chain) {
    out << "Blocks: " << chain.getChain().size() << "\nDifficulty: " << chain.getDifficulty() << std::endl;
    return out;
}

void Blockchain::print() {
    for (const Block &block: m_chain)
        std::cout << "Block hash: " << block.getBlockHash() << "\nPrevious hash: " << block.getPrevHash()
                  << "\nMerkle hash: " << block.getDataHash() << "\nNonce: "
                  << block.getNonce()
                  << std::endl << std::endl;
}