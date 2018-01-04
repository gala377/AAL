#include <iostream>
#include "generator.h"


int main(int argc, char* argv[]) {
    Test t = generate_test(10, 10);
    for(int i = 0; i < t.buckets.size(); ++i) {
        std::cout << "Bucket " << i << "/n";
        for (auto const &brick : t.buckets[i].bricks) {
            std::cout << brick << "\t";
        }
    }
    return 0;
}