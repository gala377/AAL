//
// Created by igor on 05.01.18.
//

#ifndef AAL_NAIVE_H
#define AAL_NAIVE_H
#include "generator.h


namespace algorithm {

    class Bucket : public generator::Bucket {
    public:


    };

    class Naive {
    public:
        explicit Naive(const generator::Test &t);

        int run();

    private:

    };

}
#endif //AAL_NAIVE_H
