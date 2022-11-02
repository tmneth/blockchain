#include "user.h"

#include <utility>

User::User(std::string name, double balance) {

    MYSHA hash;

    std::random_device device;
    std::mt19937 mt(device());
    std::uniform_int_distribution<int> seed(10000, 1000000);

    m_privateKey = hash(std::to_string(seed(mt)));
    m_publicKey = hash(m_privateKey + m_name);

    m_name = std::move(name);
    m_balance = balance;

};

void User::setBalance(double balance) {

    m_balance = balance;

}

std::string User::getName() const {
    return m_name;
}

std::string User::getPublicKey() const {

    return m_publicKey;

};

double User::getBalance() const {

    return m_balance;

};

std::ostream &operator<<(std::ostream &out, const User &user) {

    out << user.m_name
        << "\n Public key: " << user.m_publicKey
        << "\n Balance: " << user.m_balance << std::endl;
    return out;

}
