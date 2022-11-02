#include "transaction.h"

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

    MYSHA hash;
    m_hash = hash(m_to + m_from + std::to_string(m_amount) + std::to_string(m_timestamp));

};

void Transaction::setAmount(double amount) {

    m_amount = amount;

}

int Transaction::getId() const {

    return m_id;

};

std::string Transaction::getRecipient() const {

    return m_to;

};

std::string Transaction::getSender() const {

    return m_from;

};

std::string Transaction::getHash() const {

    return m_hash;

};

time_t Transaction::getTimestamp() const {

    return m_timestamp;

};

double Transaction::getAmount() const {

    return m_amount;

}

std::ostream &operator<<(std::ostream &out, Transaction transaction) {

//    out << "\nId: " << transaction.m_id
//        << "\nFrom: " << transaction.m_from
//        << "\nTo: " << transaction.m_to
//        << "\nTransaction hash: " << transaction.m_hash
//        << "\nAmount: " << transaction.m_amount
//        << "\nTimestamp: " << transaction.m_timestamp << std::endl;

    out << std::left << std::setw(4) << "[№: " << std::setw(5) << transaction.m_id << "] $" << std::setw(8)
        << transaction.m_amount << " Hash: " << transaction.m_hash << " From: " << transaction.m_from << " -> "
        << transaction.m_to << " | Time: "
        << transaction.m_timestamp;

    return out;

}