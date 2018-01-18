//
// Created by igor on 04.01.18.
//

#ifndef AAL_GENERATOR_H
#define AAL_GENERATOR_H

#include <vector>
#include <utility>
#include <string>

namespace generator {

    //TODO zmienic pisanie do i czytanie z pliku na wypisywanie do i czytanie ze strumienia

    using Choices = std::vector<std::pair<int, int>>;
    using Choice = std::pair<int, int>;


    class Bucket {
    public:
        int capacity;
        std::vector<int> bricks;

        static Bucket New(int cap, int free_space, Choices bricks);

        Bucket(int cap, std::vector<int> &bricks) noexcept;
        Bucket(const Bucket &other) noexcept;
        Bucket(Bucket &&other) noexcept;
        Bucket();

        bool is_full();

        bool is_empty();
    };


    class Test {
    public:
        int k = 0;
        std::vector<Bucket> buckets;

        Test() = default;

        /*
         * Reads test data from file
         * File should be in format
         * n k
         * p0 k0
         * i0
         * i1
         * ...
         * ik0
         * p1 k1
         * i0
         * ...
         * ik1
         * ...
         * pn-1 kn-1
         * ...
         *
         * Where n - num of buckets, k - num of colors
         * pn is bucket capacity, kn is num of bricks currently in the bucket and i is brick id
         */
        Test(std::string filename);

        void dump_to_file(std::string filename);

        friend std::ostream &operator<<(std::ostream &out, const Test &t);
        friend std::istream &operator>>(std::istream &in, const Test &t);
    };


    Choices get_random_colors(int k);

    Test &shuffle_test(Test &t, int moves);

/*
 * generate_test tworzy pojedyńczy problem do rozwiązania
 *
 * @param n - liczba pojemników
 * @param k - liczba kolorów (łącznie nie może być więcej niż n klocków danego koloru)
 * @param min_p - minimalna pojemność jaką może mieć pojemnik
 * @param max_p - maksymalna pojemość jaką może mieć pojemnik
 * @param min_free_space - ile miejca minimalnie powinno zostać w każdym pojemniku
 * @param max_free_space - ile wolnego miejsca może być maksymalnie w jednym pojemniku
 * @param shuffle_moves - ile losowych ruchów powinno się wykonać
 *
 * @return returns problem test to resolve
 *
 */
    Test generate_test(int n, int k, int min_p, int max_p, int min_free_space, int max_free_space, int shuffle_moves);


}

#endif //AAL_GENERATOR_H
