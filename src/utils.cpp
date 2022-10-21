#include <algorithm>
#include <random>
#include "utils.h"

double genRandAmount() {

    std::mt19937 mt{std::random_device{}()};
    std::uniform_real_distribution<> amount(1000.0, 99999.0);

    return amount(mt);
}

std::vector<User> genUsers() {

    std::vector<User> users(1000);

    for (int i = 1; i <= 1000; ++i) {
        User user;

        user.setName("user" + std::to_string(i));
        user.setBalance(genRandAmount());

        users.push_back(user);
    }

//    for (User u: users)
//        std::cout << u << std::endl;

    return users;
}

std::vector<Transaction> genPool(std::vector<User> &users) {

    std::vector<Transaction> pool;

    std::random_device device;
    std::mt19937 mt(device());
    std::uniform_int_distribution<int> seed(0, 999);

    for (int i = 1; i <= 10000; ++i) {

        int randSender = seed(mt);
        int randRecipient = seed(mt);

        Transaction transaction;

        transaction.setId(i);

        transaction.setSender(users[randSender].getPublicKey());
        transaction.setRecipient(users[randRecipient].getPublicKey());
        transaction.setAmount(genRandAmount());

        pool.push_back(transaction);
    }

//    for (Transaction t: pool)
//        std::cout << t << std::endl;

    return pool;

}

std::vector<Transaction> shrinkPool(std::vector<Transaction> &pool) {

    std::mt19937_64 random_engine{std::random_device{}()};
    std::vector<Transaction> newPool;
    std::ranges::sample(pool, std::back_inserter(newPool), 100, random_engine);

//    for (Transaction t : newPool)
//    {
//        std::cout << t << std::endl;
//    }

    return newPool;
}
