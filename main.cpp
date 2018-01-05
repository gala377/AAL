#include <iostream>
#include "Naive.h"

int main(int argc, char* argv[]) {
    algorithm::Naive res(generator::generate_test(10, 10, 4, 10, 1, 3, 100));
    std::cout << res;
    return 0;
}
