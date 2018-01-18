//
// Created by igor on 18.01.18.
//

#ifndef AAL_ASTAR_H
#define AAL_ASTAR_H

#include "BFS.h"

namespace algorithm {


    class AStar : BFS {
    public:
        const int iteration_limit = 10000;

        class Bucket : public BFS::Bucket {
            using BFS::Bucket::Bucket;
        };
        class State : public BFS::State {
        public:
            State(const State& other) = default;
            State(const BFS::State& other, int k);
            explicit State(const generator::Test &t);

            int k;
        };

        using StateDepth = std::pair<AStar::State, int>;

        class Compare
        {
        public:
            bool operator() (StateDepth & a, StateDepth & b);
            int cost(State& s, int depth);
        };


        explicit AStar(const generator::Test &t);
        int run();

    private:
        int k;
        State initial;
        std::set<std::size_t> visited;


        std::vector<State> gen_states(State& s);
    };



}

#endif //AAL_ASTAR_H
