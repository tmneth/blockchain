#include "user.h"

void User::setName(std::string_view name) {
    this->m_name = name;
}

void User::setBalance(double balance) {
    this->m_balance = balance;
};

std::string User::getName() {
    return m_name;
};

std::string User::getPublicKey() {
    return m_publicKey;
};

double User::getBalance() {
    return m_balance;
};

std::ostream &operator<<(std::ostream &out, User user) {
    out << "User: " << user.getName() << "\nPublic key: " << user.getPublicKey() << "\nBalance: " << user.getBalance()
        << std::endl;
    return out;
}