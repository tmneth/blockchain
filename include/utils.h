#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>

#include "user.h"
#include "transaction.h"

// generate 1000 random users
std::vector<User> genUsers();

// generate pool of 10000 transactions between prev generated users
std::vector<Transaction> genPool(std::vector<User> &users);

// select 100 random transactions from the pool
std::vector<Transaction> shrinkPool(std::vector<Transaction> &pool);