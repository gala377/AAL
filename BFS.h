//
// Created by igor on 17.01.18.
//

#ifndef AAL_BFS_H
#define AAL_BFS_H
#include <set>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "generator.h"

namespace algorithm {
    class BFS {
    public:
        const int iteration_limit = 10000;

        class Bucket {
        public:
            std::multiset<int> bricks;
            int capacity;

            Bucket(const Bucket& other);
            explicit Bucket(const generator::Bucket& other);

            bool is_empty();
            bool is_full();

            bool operator==(const Bucket& other) const;
            bool operator!=(const Bucket& other) const;

            std::size_t hash();
        };

        class State {
        public:
            std::vector<BFS::Bucket> buckets;


            State(const State& other);
            explicit State(const generator::Test &t);


            bool operator==(const State &other) const;
            bool operator!=(const State &other) const;

            bool resolved() const;
            std::size_t hash();

            virtual State move (int from_index, int to_index, int color) const;
        };

        explicit BFS(const generator::Test &t);

        virtual int run();
    protected:
        int k;
        State initial;
        std::set<std::size_t> visited;

        virtual std::vector<State> gen_states(State& s);
    };

}

#endif //AAL_BFS_H
