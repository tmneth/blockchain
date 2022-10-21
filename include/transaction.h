#pragma once

#include <iostream>

class Transaction {

private:

    int m_id{};
    std::string m_to{};
    std::string m_from{};
    double m_amount{};

public:

    void setId(int id);

    void setRecipient(std::string_view hash);

    void setSender(std::string_view hash);

    int getId();

    std::string getRecipient();

    std::string getSender();

};
