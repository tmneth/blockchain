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

int Transaction::getId() {
    return m_id;
};

std::string Transaction::getRecipient() {
    return m_to;
};

std::string Transaction::getSender() {
    return m_from;
};