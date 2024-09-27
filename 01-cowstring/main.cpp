#include "my_str_COW.hpp"

int main() {
    COW::my_str_COW<char> hello_world {"hello, world!"};
    std::cout << hello_world.cur_addr() << " <-- hello_world str address." << std::endl;
    std::cout << hello_world << std::endl;

    COW::my_str_COW<char> l_letter {"l"};
    auto idxs_arr = hello_world.search(l_letter);
    std::cout << l_letter << " first appearance indexes are : ";
    for (size_t i = 0; i < idxs_arr.size(); ++i) {
        std::cout << idxs_arr[i] << " ";
    }
    std::cout << std::endl;

    auto hello = hello_world.substr(1,12);
    std::cout << hello.cur_addr() << " <-- hello_world substr address before rewriting." << std::endl;
    std::cout << hello << std::endl;

    COW::my_str_COW<char> rld {"rld"};
    idxs_arr = hello.search(rld);
    std::cout << "rld first appearance index is: " << idxs_arr[0]  << std::endl;

    hello[1] = 'n';
    hello[2] = 'j';
    hello[4] = 'y';
    std::cout << hello.cur_addr() << " <-- hello_world substr address after rewriting it to enjoyworld." << std::endl;
    std::cout << hello << std::endl;

    return 0;
}
