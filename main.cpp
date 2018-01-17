#include <iostream>
#include "Naive.h"
#include "generator.h"

int main(int argc, char* argv[]) {
    algorithm::Naive res(generator::generate_test(10, 10, 4, 10, 1, 3, 100));
    std::cout << res;
    int fin = res.run();
    std::cout << "\n\n\nResolved in: " << fin << "\n";
    std::cout << res;
    return 0;
}
