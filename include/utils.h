#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>

#include "user.h"
#include "transaction.h"

// generate 1000 random users
void genUsers(std::vector<User> &users);

// generate pool of 10000 transactions between prev generated users
void genPool(std::vector<User> users);