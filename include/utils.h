#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <random>
#include <fstream>

#include "user.h"
#include "transaction.h"
#include "blockchain.h"
#include "block.h"

void initBlockchain(Blockchain &chain, std::vector<Transaction> pool, std::vector<User> &users, bool debug);

void genUsers(std::vector<User> &users);

void genPool(std::vector<User> &users, std::vector<Transaction> &pool);