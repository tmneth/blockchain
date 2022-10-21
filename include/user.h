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

    User() {
        MYSHA hash;

        std::random_device device;
        std::mt19937 mt(device());
        std::uniform_int_distribution<int> seed(10000, 1000000);

        m_privateKey = hash(std::to_string(seed(mt)));
        m_publicKey = hash(m_privateKey + m_name);
    };

    void setName(std::string_view name);

    void setBalance(double balance);

    std::string getName();

    std::string getPublicKey();

    double getBalance();

    friend std::ostream &operator<<(std::ostream &out, User user);

    ~User() = default;

};