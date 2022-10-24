#pragma once

#include <iostream>

class Transaction {

private:

    int m_id{};
    std::string m_to{};
    std::string m_from{};
    std::string m_hash{};
    double m_amount{};

public:

    Transaction() = default;

    void setId(int id);

    void setRecipient(std::string_view hash);

    void setSender(std::string_view hash);

    void setHash();

    void setAmount(double amount);

    int getId();

    std::string getRecipient();

    std::string getSender();

    std::string getHash();

    double getAmount();

    friend std::ostream &operator<<(std::ostream &out, Transaction transaction);

    ~Transaction() = default;

};
