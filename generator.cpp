//
// Created by igor on 04.01.18.
//
#include <algorithm>
#include <iostream>
#include "generator.h"


Bucket::Bucket(Bucket&& other) noexcept {
    capacity = other.capacity;
    bricks = std::move(other.bricks);
}

Bucket::Bucket(const Bucket& other) noexcept : capacity(other.capacity) {
    for(auto const val: other.bricks) {
        bricks.push_back(val);
    }
}

Bucket::Bucket(int cap, std::vector<int>& bricks) noexcept : capacity(cap), bricks(std::move(bricks)) {};

bool Bucket::is_full() {
    return capacity == bricks.size();
}

bool Bucket::is_empty() {
    return bricks.size() == 0;
}

Bucket Bucket::New(int capacity, int free_space, Choices bricks) {
    auto end = bricks.begin() + std::min(int(bricks.size()), capacity - free_space);
    std::vector<int> trimmed;
    for(auto it = bricks.begin(); it != end; it++) {
        trimmed.push_back((*it).first);
    }
    return Bucket(capacity, trimmed);
}


Test generate_test(int n, int k, int min_p, int max_p, int min_free_space, int max_free_space, int shuffle_moves) {
    Test test = Test();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> capacity(min_p, max_p);

    for(int i = 0; i < n; ++i) {
        Choices blocks = get_random_colors(k);
        int cap = capacity(gen);

        std::uniform_int_distribution<> free_space(min_free_space, std::min(max_free_space, cap));
        int space = free_space(gen);

        test.buckets.emplace_back(Bucket::New(cap, space, blocks));
    }
    shuffle_test(test, shuffle_moves);
    return test;
}


Test& shuffle_test(Test &t, int moves) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, t.buckets.size()-1);

    for(int i = 0; i < moves; ++i) {
        Bucket& a = t.buckets[dis(gen)];
        Bucket& b = t.buckets[dis(gen)];
        std::cout << "Shuffle " << i << "\n";
        if (b.is_full() or a.is_empty()) {
            std::cout << "Skipping\n";
            continue;
        }
        b.bricks.push_back(a.bricks.back());
        a.bricks.pop_back();
    }
    return t;
}

Choices get_random_colors(int k) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    Choices result;

    for(int i = 0; i < k; ++i) {
        result.emplace_back(std::make_pair(i, dis(gen)));
    }

    std::sort(result.begin(), result.end(), [](const Choice& a, const Choice& b) { return a.second > b.second; });
    return result;
}