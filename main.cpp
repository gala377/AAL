#include <iostream>
#include "generator.h"


int main(int argc, char* argv[]) {
    Test t = generate_test(10, 10, 4, 10, 1, 3, 100);
    std::cout << t;
    t.dump_to_file("test_1.txt");
    return 0;
}
