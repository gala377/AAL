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

    static Bucket New(int cap, int free_space, Choices bricks);

    Bucket(int cap, std::vector<int>& bricks) noexcept;
    Bucket(const Bucket& other) noexcept;
    Bucket(Bucket&& other) noexcept;

    bool is_full();
    bool is_empty();
};


class Test {
public:
    std::vector<Bucket> buckets;
};


Choices get_random_colors(int k);

Test& shuffle_test(Test &t, int moves);

/*
 * generate_test tworzy pojedyńczy problem do rozwiązania
 *
 * @param n - liczba pojemników
 * @param k - liczba kolorów (łącznie nie może być więcej niż n klocków danego koloru)
 *
 */
Test generate_test(int n, int k, int min_p, int max_p, int min_free_space, int max_free_space, int shuffle_moves);

#endif //AAL_GENERATOR_H
