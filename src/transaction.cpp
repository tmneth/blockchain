#include "transaction.h"

void Transaction::setId(int id) { m_id = id; }

void Transaction::setRecipient(std::string_view hash) { m_to = hash; };

void Transaction::setSender(std::string_view hash) { m_from = hash; };

void Transaction::setHash() {

    MYSHA hash;
    m_hash = hash(m_to + m_from + std::to_string(m_amount) + std::to_string(m_timestamp));

};

void Transaction::setAmount(double amount) { m_amount = amount; }

int Transaction::getId() { return m_id; };

std::string Transaction::getRecipient() const { return m_to; };

std::string Transaction::getSender() const { return m_from; };

std::string Transaction::getHash() const { return m_hash; };


double Transaction::getAmount() const { return m_amount; }

std::ostream &operator<<(std::ostream &out, Transaction transaction) {

    out << "\nId: " << transaction.m_id
        << "\nFrom: " << transaction.m_from
        << "\nTo: " << transaction.m_to
        << "\nTransaction hash: " << transaction.m_hash
        << "\nAmount: " << transaction.m_amount
        << "\nTimestamp: " << transaction.m_timestamp << std::endl;
    return out;

}

//std::istream &operator>>(std::istream &in, Transaction &transaction) {
//
//    in >> transaction.m_id
//       >> transaction.m_from
//       >> transaction.m_to
//       >> transaction.m_hash
//       >> transaction.m_amount
//       >> transaction.m_timestamp;
//
//    return in;
//
//}
