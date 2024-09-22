#include "my_str_COW.hpp"

int main() {
    COW::my_str_COW<char> hello_world {"hello,world!"};
    std::cout << hello_world.cur_addr() << " <-- hello_world str address." << std::endl;
    std::cout << hello_world << std::endl;

    auto hello = hello_world.substr(1,11);
    std::cout << hello.cur_addr() << " <-- hello_world substr address before rewriting." << std::endl;
    std::cout << hello << std::endl;

    hello[1] = 'n';
    hello[2] = 'j';
    hello[4] = 'y';
    std::cout << hello.cur_addr() << " <-- hello_world substr address after rewriting it to enjoyworld." << std::endl;
    std::cout << hello << std::endl;

    return 0;
}
