//
// Created by igor on 04.01.18.
//
#include <algorithm>
#include <iostream>
#include "generator.h"
#include <fstream>


namespace generator {

    Bucket::Bucket(Bucket &&other) noexcept {
        capacity = other.capacity;
        bricks = std::move(other.bricks);
    }

    Bucket::Bucket(const Bucket &other) noexcept : capacity(other.capacity) {
        for (auto const val: other.bricks) {
            bricks.push_back(val);
        }
    }

    Bucket::Bucket(int cap, std::vector<int> &bricks) noexcept : capacity(cap), bricks(std::move(bricks)) {};

    bool Bucket::is_full() {
        return capacity == bricks.size();
    }

    bool Bucket::is_empty() {
        return bricks.empty();
    }

    Bucket Bucket::New(int capacity, int free_space, Choices bricks) {
        auto end = bricks.begin() + std::min(int(bricks.size()), capacity - free_space);
        std::vector<int> trimmed;
        for (auto it = bricks.begin(); it != end; it++) {
            trimmed.push_back((*it).first);
        }
        return Bucket(capacity, trimmed);
    }

    Bucket::Bucket() : capacity(0) {}


    Test::Test(std::string filename) {
        std::fstream file;
        file.open(filename, std::fstream::in);
        if (file.is_open()) {
            int n = 0;
            file >> n;
            file >> k;
            for (int i = 0; i < n; ++i) {
                int cap, occupied;
                file >> cap >> occupied;
                std::vector<int> bricks;
                for (int j = 0; j < occupied; ++j) {
                    int brick;
                    file >> brick;
                    bricks.push_back(brick);
                }
                buckets.emplace_back(Bucket(cap, bricks));
            }
            file.close();
        }
    }

    void Test::dump_to_file(std::string filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << buckets.size() << " " << k << std::endl;
            for (auto &&bucket : buckets) {
                file << bucket.capacity << " " << bucket.bricks.size() << std::endl;
                for (auto &&brick : bucket.bricks) {
                    file << brick << std::endl;
                }
            }
            file.close();
        } else {
            throw std::ios_base::failure("Could not open file to write the test to");
        }
    }

    std::ostream &operator<<(std::ostream &out, const Test &t) {
        for (int i = 0; i < t.buckets.size(); ++i) {
            unsigned long free_space = t.buckets[i].capacity - t.buckets[i].bricks.size();
            std::cout << "\nBucket " << i << "\tCapacity: " << t.buckets[i].capacity << "\tFree: " << free_space
                      << "\n";
            for (auto const &brick : t.buckets[i].bricks) {
                std::cout << brick << "\t";
            }
            for (free_space; free_space > 0; --free_space) {
                std::cout << "x\t";
            }
        }
        return out;
    }


    Test generate_test(int n, int k, int min_p, int max_p, int min_free_space, int max_free_space, int shuffle_moves) {
        Test test = Test();
        test.k = k;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> capacity(min_p, max_p);

        for (int i = 0; i < n; ++i) {
            Choices blocks = get_random_colors(k);
            int cap = capacity(gen);

            std::uniform_int_distribution<> free_space(min_free_space, std::min(max_free_space, cap));
            int space = free_space(gen);

            test.buckets.emplace_back(Bucket::New(cap, space, blocks));
        }
        shuffle_test(test, shuffle_moves);
        return test;
    }

    Test &shuffle_test(Test &t, int moves) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, t.buckets.size() - 1);

        for (int i = 0; i < moves; ++i) {
            int bucketindex = dis(gen);
            Bucket &a = t.buckets[bucketindex];
            Bucket &b = t.buckets[(bucketindex + 1) % t.buckets.size()];

            if (b.is_full() or a.is_empty()) {
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

        for (int i = 0; i < k; ++i) {
            result.emplace_back(std::make_pair(i, dis(gen)));
        }

        std::sort(result.begin(), result.end(), [](const Choice &a, const Choice &b) { return a.second > b.second; });
        return result;
    }

}