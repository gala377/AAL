//
// Created by igor on 17.01.18.
//

#include "BFS.h"
#include <algorithm>
#include <queue>
#include <iostream>

algorithm::BFS::Bucket::Bucket(const generator::Bucket &other) : capacity(other.capacity) {
    for(auto &&brick : other.bricks) {
        bricks.insert(brick);
    }
}

bool algorithm::BFS::Bucket::is_empty() {
    return bricks.empty();
}

bool algorithm::BFS::Bucket::is_full() {
    return bricks.size() == capacity;
}

bool algorithm::BFS::Bucket::operator!=(const algorithm::BFS::Bucket &other) const {
    return !(*this == other);
}

bool algorithm::BFS::Bucket::operator==(const algorithm::BFS::Bucket &other) const {
    return capacity == other.capacity && bricks == other.bricks;
}

std::size_t algorithm::BFS::Bucket::hash() {
    std::size_t seed = bricks.size();
    for(auto& i : bricks) {
        seed ^= std::hash<int>{}(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

algorithm::BFS::Bucket::Bucket(const algorithm::BFS::Bucket &other) :
    capacity(other.capacity), bricks(other.bricks) {

}


algorithm::BFS::BFS(const generator::Test &t) : k(t.k), initial(t) {

}

int algorithm::BFS::run() {
    std::queue<std::pair<State, int>> pending;
    pending.push(std::make_pair(this->initial, 0));

    int iteration = 0;
    while(!pending.empty()) {
        auto current = pending.front();
        pending.pop();

        if(current.first.resolved()) {
            return current.second;
        }


        std::vector<State> possible_next = gen_states(current.first);
        for (auto &&next : possible_next) {
            if(!visited.count(next.hash())) {
                auto new_state = std::make_pair(next, current.second+1);
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

std::vector<algorithm::BFS::State> algorithm::BFS::gen_states(algorithm::BFS::State &s) {
    std::vector<State> states;
    for (int i = 0; i < s.buckets.size(); ++i) {
        for (auto &&brick: s.buckets[i].bricks) {
            int left = --i < 0 ? s.buckets.size()-1 : i;
            int right = ++i % s.buckets.size();

            if(!s.buckets[left].is_full()) {
                states.push_back(s.move(i, left, brick));
            }
            if(!s.buckets[right].is_full()) {
                states.push_back(s.move(i, right, brick));
            }
        }
    }
    return states;
}


algorithm::BFS::State::State(const generator::Test &t) {
    for (auto &&bucket : t.buckets) {
        buckets.push_back(Bucket(bucket));
    }
}

bool algorithm::BFS::State::operator!=(const algorithm::BFS::State &other) const {
    return !(*this != other);
}

bool algorithm::BFS::State::operator==(const algorithm::BFS::State &other) const {
    if(buckets.size() != other.buckets.size())
        return false;
    for (int i = 0; i < buckets.size(); ++i) {
        if(buckets[i] != other.buckets[i])
            return false;
    }
    return true;
}

std::size_t algorithm::BFS::State::hash() {
    std::size_t seed = buckets.size();
    for(auto& i : buckets) {
        seed ^= i.hash() + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}


algorithm::BFS::State algorithm::BFS::State::move(int from_index, int to_index, int color) const {
    State new_state(*this);

    new_state.buckets[to_index].bricks.insert(color);
    auto it = new_state.buckets[from_index].bricks.find(color);
    new_state.buckets[from_index].bricks.erase(it);

    return new_state;
}

algorithm::BFS::State::State(const algorithm::BFS::State &other) {
    for (auto &&bucket : other.buckets) {
        buckets.push_back(Bucket(bucket));
    }
}

bool algorithm::BFS::State::resolved() const {
    for (auto &&bucket : buckets) {
        for (auto &&brick : bucket.bricks) {
                if(bucket.bricks.count(brick) > 1)
                    return false;
        }
    }
    return true;
}
