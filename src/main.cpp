#include "utils.h"
#include "blockchain.h"

void showHelpMessage() {
    std::cerr
            << "Please use one of the following commands:\n"
            << "getblockchaininfo: Show information about blockchain\n"
            << std::endl;
}

int main(int argc, char *argv[]) {

    Blockchain chain;

    initBlockchain(chain);

    if (argc == 1) {
        showHelpMessage();
        return 1;
    }

    for (int i = 0; i < argc; i++) {

        std::string arg = argv[i];

        if ((arg == "-h") || (arg == "--help")) {
            showHelpMessage();
            return 1;
        } else if (arg == "getblockchaininfo") {
            std::cout << chain << std::endl;
        }
    }

    return 0;

}