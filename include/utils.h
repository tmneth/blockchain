#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <random>

#include "user.h"
#include "transaction.h"
#include "blockchain.h"
#include "block.h"
#include "pool.h"

void initBlockchain(Blockchain &chain, Pool pool, std::vector<User> users);

void genUsers(std::vector<User> &users);

void genPool(std::vector<User> &users, Pool &pool);