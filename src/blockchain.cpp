#include "blockchain.h"

void Blockchain::appendBlock(const Block &block) {

    m_chain.push_back(block);

}

std::string Blockchain::getPrevHash() {

    return m_chain.empty()
           ? "AEEBAD4A796FCC2E15DC4C6061B45ED9B373F26ADFC798CA7D2D8CC58182718E"
           : m_chain[m_chain.size() - 1].getBlockHash();

}