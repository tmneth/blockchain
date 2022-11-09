#pragma once

#include <iostream>
#include "transaction.h"
#include <bitcoin.hpp>

std::string buildMerkle(std::vector<Transaction> &data);