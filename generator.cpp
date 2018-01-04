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

Bucket::Bucket(int cap, Choices bricks) noexcept : capacity(cap) {
    auto end = bricks.begin() + std::min(int(bricks.size()), capacity);
    std::vector<int> trimmed;
    for(auto it = bricks.begin(); it != end; it++) {
        trimmed.push_back((*it).first);
    }
    this->bricks = std::move(trimmed);
}


Test generate_test(int n, int k) {
    Test test = Test();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    for(int i = 0; i < n; ++i) {
        Choices blocks = get_random_colors(k);
        int cap = dis(gen);
        test.buckets.emplace_back(Bucket(cap, blocks));
        shuffle_test(test);
    }
    return test;
}

Test shuffle_test(Test &t) {
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