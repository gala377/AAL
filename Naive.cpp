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
        int moves_made = 0;
        while(true) {
            for (int i = 0; i < buckets.size(); ++i) {
                for (auto &unneeded : buckets[i].unneeded) {
                    // znajdz gdzie mozesz wrzucic
                    for (int j = 0; j < buckets.size(); ++j) {
                        if(buckets[j].accepted.count(unneeded) and !buckets[j].is_full()) {
                            // sprawdz ktora droga jest krotsza ( l or r )
                                //idz krotsza jezeli sie nie da sprawdz druga
                                //jezeli sie nie da to olej
                            // przerzuc tam klocek i dodaj ruchy
                        }
                    }
                }

            }

            if(!move_made) {
                break;
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

}