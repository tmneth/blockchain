#include <random>
#include "utils.h"

void genUsers() {

    std::vector<User> users;

    users.reserve(1000);

    std::random_device device;
    std::mt19937 mt(device());
    std::uniform_int_distribution<int> seed(100, 1000000);

    for (int i = 1; i <= 1000; ++i) {
        User user;

        user.setName("user" + std::to_string(i));
        user.setBalance(seed(mt));

        users.push_back(user);
    }

    for (User u: users) {
        std::cout << u << std::endl;
    }

}