//
// Created by igor on 18.01.18.
//

#include "AStar.h"
#include <queue>
#include <iostream>

algorithm::AStar::AStar(const generator::Test &t) : k(t.k), initial(t), BFS(t) {
}

algorithm::AStar::State::State(const generator::Test &t) : k(t.k), BFS::State(t) {

}

algorithm::AStar::State::State(const algorithm::BFS::State &other, int k) :
    k(k), BFS::State(other) {

}


int algorithm::AStar::Compare::cost(algorithm::AStar::State &s, int depth) {
    int cost = 0;
    for (auto &&b : s.buckets) {
        for(int i = 0; i < s.k; ++i) {
            int count = b.bricks.count(i);
            if(count) {
                cost += count-1;
            }
        }
    }
    return depth + cost;
}

bool algorithm::AStar::Compare::operator()(algorithm::AStar::StateDepth &a,
                                            algorithm::AStar::StateDepth &b) {
    return cost(a.first, a.second) > cost(b.first, b.second);
}




int algorithm::AStar::run() {
    std::priority_queue<StateDepth, std::vector<StateDepth>, AStar::Compare> pending;
    pending.push(std::make_pair(initial, 0));
    int iteration = 0;
    while(!pending.empty()) {
        auto current = pending.top();
        pending.pop();

        Compare c;
//        std::cout << "State: " << current.first.hash() << "\n";
        std::cout << "Depth: " << current.second << "\n";
        std::cout << "Cost: " << c.cost(current.first, current.second);

        if(current.first.resolved()) {
            return current.second;
        }

        std::vector<State> possible_next = gen_states(current.first);
        for (auto &&next : possible_next) {
            if(!visited.count(next.hash())) {
                std::pair<State, int> new_state = std::make_pair(next, current.second+1);
                pending.push(new_state);
                visited.insert(new_state.first.hash());
            }
        }
        ++iteration;
        if(iteration > iteration_limit) {
            break;
        }
    }
    return -1;
}

std::vector<algorithm::AStar::State> algorithm::AStar::gen_states(algorithm::AStar::State &s) {
    std::vector<State> states;
    for (int i = 0; i < s.buckets.size(); ++i) {
        for (auto &&brick: s.buckets[i].bricks) {
            int left = --i < 0 ? s.buckets.size()-1 : i;
            int right = ++i % s.buckets.size();

            if(!s.buckets[left].is_full()) {
                states.push_back(State(s.move(i, left, brick), k));
            }
            if(!s.buckets[right].is_full()) {
                states.push_back(State(s.move(i, right, brick), k));
            }
        }
    }
    return states;
}





