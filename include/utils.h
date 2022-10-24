#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>

#include "user.h"
#include "transaction.h"
#include "blockchain.h"

void initBlockchain(Blockchain &chain, std::vector<Transaction> pool, std::vector<User> users);

int getTransaction(std::vector<Transaction> &pool, int id);

void genUsers(std::vector<User> &users);

void genPool(std::vector<User> &users, std::vector<Transaction> &pool);