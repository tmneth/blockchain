#include "user.h"

User::User(std::string name, double balance) {
    MYSHA hash;

    std::random_device device;
    std::mt19937 mt(device());
    std::uniform_int_distribution<int> seed(10000, 1000000);

    m_privateKey = hash(std::to_string(seed(mt)));
    m_publicKey = hash(m_privateKey + m_name);

    m_name = name;
    m_balance = balance;

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
    out << "Name: " << user.getName() << "\nPublic key: " << user.getPublicKey() << "\nBalance: " << user.getBalance()
        << std::endl;
    return out;
}
