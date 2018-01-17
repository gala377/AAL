//
// Created by igor on 05.01.18.
//

#ifndef AAL_NAIVE_H
#define AAL_NAIVE_H
#include "generator.h"
#include <set>

namespace algorithm {
    class Naive {
    public:
        class Bucket : public generator::Bucket {
        public:

            Bucket(const generator::Bucket& other, int k);

            std::set<int> accepted;
            std::multiset<int> unneeded;

            auto accepted_end() -> decltype(accepted.end());

        };

        const int iteration_limit = 1000000;

        explicit Naive(const generator::Test &t);

        int run();
        bool resolved();

        friend int move(int ab_index, int bb_index, int color_index, Naive& alg);
        friend int move_right(int ab_index, int bb_index, Naive& alg);
        friend int move_left(int ab_index, int bb_index, Naive& alg);

        friend std::ostream &operator<<(std::ostream &out, const Naive &n);
        friend int move_unneeded_bricks(int bucket_index, Naive& alg);
    private:
        int k;
        std::vector<Bucket> buckets;
    };

}
#endif //AAL_NAIVE_H
