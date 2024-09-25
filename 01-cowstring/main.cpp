#include "my_str_COW.hpp"

int main() {
    COW::my_str_COW<char> hello_world {"hello, world!"};
    std::cout << hello_world.cur_addr() << " <-- hello_world str address." << std::endl;
    std::cout << hello_world << std::endl;

    COW::my_str_COW<char> smth {"ll"};
    auto idx = hello_world.search(smth);
    std::cout << "ll index is: " << idx << std::endl;

    auto hello = hello_world.substr(1,12);
    std::cout << hello.cur_addr() << " <-- hello_world substr address before rewriting." << std::endl;
    std::cout << hello << std::endl;

    COW::my_str_COW<char> rld {"rld"};
    idx = hello.search(rld);
    std::cout << "rld index is: " << idx  << std::endl;

    hello[1] = 'n';
    hello[2] = 'j';
    hello[4] = 'y';
    std::cout << hello.cur_addr() << " <-- hello_world substr address after rewriting it to enjoyworld." << std::endl;
    std::cout << hello << std::endl;

    return 0;
}
