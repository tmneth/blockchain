#include <iostream>
#include "utils.h"
#include "user.h"

int main() {

    std::vector<User> users;

    genUsers(users);

    genPool(users);

    return 0;
}
