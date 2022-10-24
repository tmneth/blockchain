#include "transaction.h"
#include "hash.h"

void Transaction::setId(int id) {
    m_id = id;
}

void Transaction::setRecipient(std::string_view hash) {
    m_to = hash;
};

void Transaction::setSender(std::string_view hash) {
    m_from = hash;
};

void Transaction::setHash() {
    MYSHA mysha;
    m_hash = mysha(m_to + m_from );
};

void Transaction::setAmount(double amount) {
    m_amount = amount;
}

int Transaction::getId() {
    return m_id;
};

std::string Transaction::getRecipient() {
    return m_to;
};

std::string Transaction::getSender() {
    return m_from;
};

std::string Transaction::getHash() {
    return m_hash;
};

double Transaction::getAmount() {
    return m_amount;
}

std::ostream &operator<<(std::ostream &out, Transaction transaction) {
    out << "Id: " << transaction.getId() << "\nFrom: " << transaction.getSender() << "\nTo: "
        << transaction.getRecipient() << "\nTransaction hash: "
        << transaction.getHash() << "\nAmount: " << transaction.getAmount()
        << std::endl;
    return out;
}