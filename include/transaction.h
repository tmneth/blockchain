#pragma once

#include <iostream>
#include "hash.h"
#include <iomanip>
#include <jsoncpp/json/json.h>


class Transaction {

private:

    std::string m_to{};
    std::string m_from{};
    std::string m_hash{};
    double m_amount{};
    time_t m_timestamp{};

public:

    Transaction() : m_timestamp(time(0)) {};

    void setRecipient(std::string_view hash);

    void setSender(std::string_view hash);

    void setHash();

    void setAmount(double amount);

    std::string getRecipient() const;

    std::string getSender() const;

    std::string getHash() const;

    double getAmount() const;

    time_t getTimestamp() const;

    Json::Value toJSON();

    ~Transaction() = default;

};
