#pragma once

#include <iostream>
#include <random>
#include "hash.h"

class User {

private:

    std::string m_name{};
    std::string m_privateKey{};
    std::string m_publicKey{};
    double m_balance{};

public:

    User(std::string name, double balance);

    std::string getName();

    std::string getPublicKey();

    double getBalance();

    friend std::ostream &operator<<(std::ostream &out, User user);

    ~User() = default;

};