#include "utils.h"
#include "transaction.h"
#include "user.h"

int main() {
    std::vector<Transaction> t;
    std::vector<User> u;

    u = genUsers();

    t = genPool(u);
    t = shrinkPool(t);

    for (Transaction pool : t)
    {
        std::cout << pool << std::endl;
    }

    return 0;
}
