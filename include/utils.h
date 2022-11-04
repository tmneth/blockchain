#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <random>
#include <fstream>
#include <filesystem>

#include "user.h"
#include "transaction.h"
#include "blockchain.h"
#include "block.h"


void initBlockchain(Blockchain &chain, std::vector<Transaction> pool, std::vector<User> &users);