#pragma once

#include <iostream>
#include "hash.h"

class Transaction {

private:

    int m_id{};
    std::string m_to{};
    std::string m_from{};
    std::string m_hash{};
    double m_amount{};

    time_t m_timestamp{};

public:

    Transaction() : m_timestamp(time(0)) {};

    void setId(int id);

    void setRecipient(std::string_view hash);

    void setSender(std::string_view hash);

    void setHash();

    void setAmount(double amount);

    int getId();

    std::string getRecipient() const;

    std::string getSender() const;

    std::string getHash() const;

    double getAmount() const;

    friend std::ostream &operator<<(std::ostream &out, Transaction transaction);

    ~Transaction() = default;

};
