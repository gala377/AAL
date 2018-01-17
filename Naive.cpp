//
// Created by igor on 05.01.18.
//

#include "Naive.h"
#include <iostream>
#include <algorithm>

namespace algorithm {

    Naive::Naive(const generator::Test &t) : k(t.k) {
        for (auto &&bucket : t.buckets) {
            buckets.push_back(Bucket(bucket, k));
        }
    }

    int Naive::run() {
        int total_moves = 0;
        int iteration = 0;
        while (true) {
            bool move_made = false;
            for (int i = 0; i < buckets.size(); ++i) {
                int moves_made = move_unneeded_bricks(i, *this);
                move_made = move_made || bool(moves_made);
                total_moves += moves_made;
            }

            if (!move_made || iteration >= iteration_limit) {
                total_moves = -1;
                break;
            }

            if(resolved()) {
                break;
            }
            ++iteration;
        }
        return total_moves;
    }

    int move_unneeded_bricks(int bucket_index, Naive &alg) {
        int moves_made = 0;
        for (auto &unneeded : alg.buckets[bucket_index].unneeded) {
            for (int j = 0; j < alg.buckets.size(); ++j) {
                auto needed = alg.buckets[j].accepted.find(unneeded);
                if (needed != alg.buckets[j].accepted_end() and !alg.buckets[j].is_full()) {
                    moves_made = move(bucket_index, j, unneeded, alg);
                    if(moves_made) {
                        return moves_made;
                    }
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

    int move(int ab_index, int bb_index, int color_index, Naive &alg) {
        int moves_made = 0;
        if(abs(ab_index - bb_index) <= alg.buckets.size()/2) {
            if(bb_index < ab_index) {
                moves_made = move_left(ab_index, bb_index, alg);
                moves_made = !moves_made ? move_right(ab_index, bb_index, alg) : moves_made;
            } else {
                moves_made = move_right(ab_index, bb_index, alg);
                moves_made = !moves_made ? move_left(ab_index, bb_index, alg) : moves_made;
            }
        } else {
            if(bb_index < ab_index) {
                moves_made = move_right(ab_index, bb_index, alg);
                moves_made = !moves_made ? move_left(ab_index, bb_index, alg) : moves_made;
            } else {
                moves_made = move_left(ab_index, bb_index, alg);
                moves_made = !moves_made ? move_right(ab_index, bb_index, alg) : moves_made;
            }
        }
        if(moves_made) {
            auto set_it = alg.buckets[ab_index].unneeded.find(color_index);
            alg.buckets[ab_index].unneeded.erase(set_it);

            auto vec_it = std::find(alg.buckets[ab_index].bricks.begin(), alg.buckets[ab_index].bricks.end(), color_index);
            if(vec_it == alg.buckets[ab_index].bricks.end())
                std::cout << "\nERROROROROROR\n";
            alg.buckets[ab_index].bricks.erase(vec_it);

            alg.buckets[bb_index].accepted.erase(color_index);
            alg.buckets[bb_index].bricks.push_back(color_index);
        }
        return moves_made;
    }

    int move_left(int ab_index, int bb_index, Naive &alg) {
        int moves = 0;
        while(ab_index != bb_index) {
            if(alg.buckets[--ab_index].is_full()) {
                return 0;
            }
            ab_index = ab_index < 0 ? alg.buckets.size()-1 : ab_index;
            ++moves;
        }
        return moves;
    }

    int move_right(int ab_index, int bb_index, Naive &alg) {
        int moves = 0;
        while(ab_index != bb_index) {
            if(alg.buckets[++ab_index].is_full()) {
                return 0;
            }
            ab_index %= alg.buckets.size();
            ++moves;
        }
        return moves;
    }

    bool Naive::resolved() {
        for (auto &bucket : buckets) {
            if(!bucket.unneeded.empty()) {
                return false;
            }
        }
        return true;
    }


    Naive::Bucket::Bucket(const generator::Bucket &other, int k) : generator::Bucket(other) {
        int countmap[k] = {0};
        for (auto &brick : bricks) {
            countmap[brick]++;
        }
        for (int i = 0; i < k; ++i) {
            if (countmap[i] > 1) {
                for(int j = 1; j < countmap[i]; ++j)
                    unneeded.insert(i);
            } else if (countmap[i] == 0) {
                accepted.insert(i);
            }
        }
    }

    auto Naive::Bucket::accepted_end() -> decltype(accepted.end()) {
        return accepted.end();
    }

}