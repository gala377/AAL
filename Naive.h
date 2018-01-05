//
// Created by igor on 05.01.18.
//

#ifndef AAL_NAIVE_H
#define AAL_NAIVE_H
#include "generator.h"
#include <set>

namespace algorithm {

    class Bucket : public generator::Bucket {
    public:
        Bucket(const generator::Bucket& other, int k);

        std::set<int> accepted;
        std::set<int> unneeded;
    };

    class Naive {
    public:
        explicit Naive(const generator::Test &t);

        int run();

        friend std::ostream &operator<<(std::ostream &out, const Naive &n);
    private:
        int k;
        std::vector<Bucket> buckets;
    };

}
#endif //AAL_NAIVE_H
