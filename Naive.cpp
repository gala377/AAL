//
// Created by igor on 05.01.18.
//

#include "Naive.h"
#include <iostream>

namespace algorithm {

    Naive::Naive(const generator::Test &t) : k(t.k) {
        for (auto &&bucket : t.buckets) {
            buckets.emplace_back(Bucket(bucket, k));
        }
    }

    int Naive::run() {
        bool move_made = false;
        int total_moves = 0;
        while (true) {
            for (int i = 0; i < buckets.size(); ++i) {
                int moves_made = move_unneeded_bricks(i, *this);
                move_made = move_made ? move_made : bool(moves_made);
                total_moves += moves_made;
            }

            if (!move_made) {
                total_moves = -1;
                break;
            }
            move_made = false;

            if(resolved()) {
                break;
            }
        }
        return total_moves;
    }

    int move_unneeded_bricks(int bucket_index, Naive &alg) {
        int moves_made = 0;
        for (auto &unneeded : alg.buckets[bucket_index].unneeded) {
            for (int j = 0; j < alg.buckets.size(); ++j) {
                auto needed = alg.buckets[j].accepted.find(unneeded);
                if (needed != alg.buckets[j].accepted_end() and !alg.buckets[j].is_full()) {
                    moves_made = move(bucket_index, j, alg);
                }
            }
        }
        return moves_made;
    }

    std::ostream &operator<<(std::ostream &out, const Naive &n) {
        for (int i = 0; i < n.buckets.size(); ++i) {
            std::cout << "\n\nBucket number " << i << "\tCapacity: " << n.buckets[i].capacity;
            std::cout << "\tFull: " << n.buckets[i].bricks.size() << "\n";
            std::cout << "BRICKS:\n";
            for (auto &brick : n.buckets[i].bricks) {
                std::cout << brick << "\t";
            }
            std::cout << "\nNEEDED:\n";
            for (auto &brick : n.buckets[i].accepted) {
                std::cout << brick << "\t";
            }
            std::cout << "\nUNNEEDED:\n";
            for (auto &brick : n.buckets[i].unneeded) {
                std::cout << brick << "\t";
            }

        }
        return out;
    }

    int move(int ab_index, int bb_index, Naive &alg) {
        int moves_made = 0;
        if(abs(ab_index - bb_index) <= alg.buckets.size()/2) {
            if(bb_index < ab_index) {
                for (int i = bb_index; i < ab_index; ++i) {
                    //todo move rigth
                }
            } else {
                //move left
            }
        } else {
            if(bb_index < ab_index) {
                //move left
            } else {
                //move right
            }
        }
        return moves_made;
    }

    bool Naive::resolved() {
        for (auto &bucket : buckets) {
            if(!bucket.unneeded.empty()) {
                return false;
            }
        }
        return true;
    }

    Bucket::Bucket(const generator::Bucket &other, int k) : generator::Bucket(other) {
        int countmap[k] = {0};
        for (auto &brick : bricks) {
            countmap[brick]++;
        }
        for (int i = 0; i < k; ++i) {
            if (countmap[i] > 1) {
                unneeded.insert(i);
            } else if (countmap[i] == 0) {
                accepted.insert(i);
            }
        }
    }

    auto Bucket::accepted_end() -> decltype(accepted.end()) {
        return accepted.end();
    }

}