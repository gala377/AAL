#include <iostream>
#include <fstream>
#include "Naive.h"
#include "AStar.h"

int main(int argc, char* argv[]) {
    generator::Test t = generator::generate_test(10, 10, 4, 10, 1, 3, 1000);

    std::cout << "TEST" << "\n" << t;

    int fin  = algorithm::Naive(t).run();
    std::cout << "\n\n\nNaive Resolved in: " << fin << "\n";
    fin = algorithm::AStar(t).run();
    std::cout << "\n\n\nAStar Resolved in: " << fin << "\n";
    fin = algorithm::BFS(t).run();
    std::cout << "\n\n\nBFS Resolved in: " << fin << "\n";
    return 0;
}
