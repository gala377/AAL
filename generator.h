//
// Created by igor on 04.01.18.
//

#ifndef AAL_GENERATOR_H
#define AAL_GENERATOR_H

#include <vector>
#include <utility>

using Choices = std::vector<std::pair<int, int>>;
using Choice = std::pair<int, int>;


class Bucket {
public:
    int capacity;
    std::vector<int> bricks;

    Bucket(int, Choices) noexcept;
    Bucket(const Bucket&) noexcept;
    Bucket(Bucket&&) noexcept;
};


class Test {
public:
    std::vector<Bucket> buckets;
};


Choices get_random_colors(int k);
Test shuffle_test(Test &t);

/*
 * generate_test tworzy pojedyńczy problem do rozwiązania
 *
 * @param n - liczba pojemników
 * @param k - liczba kolorów (łącznie nie może być więcej niż n klocków danego koloru)
 *
 */
Test generate_test(int n, int k);

#endif //AAL_GENERATOR_H
