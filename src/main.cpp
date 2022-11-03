#include "utils.h"
#include "blockchain.h"

int main() {

    Blockchain chain;

    std::vector<Transaction> pool;
    std::vector<User> users;

    initBlockchain(chain, pool, users);

    return 0;

}