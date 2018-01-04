#include <iostream>
#include "generator.h"


int main(int argc, char* argv[]) {
    Test t = generate_test(10, 10, 4, 10, 1, 3, 100);
    for(int i = 0; i < t.buckets.size(); ++i) {
        unsigned long free_space = t.buckets[i].capacity - t.buckets[i].bricks.size();
        std::cout << "\nBucket " << i << "\tCapacity: " << t.buckets[i].capacity << "\tFree: " << free_space << "\n";
        for (auto const &brick : t.buckets[i].bricks) {
            std::cout << brick << "\t";
        }
        for (free_space; free_space > 0; --free_space) {
            std::cout << "x\t";
        }
    }
    return 0;
}