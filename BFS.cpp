//
// Created by igor on 17.01.18.
//

#include "BFS.h"
#include <algorithm>
#include <queue>

alghorithm::Bucket::Bucket(const generator::Bucket &other) : capacity(other.capacity) {
    for(auto &&brick : other.bricks) {
        bricks.insert(brick);
    }
}

bool alghorithm::Bucket::is_empty() {
    return bricks.empty();
}

bool alghorithm::Bucket::is_full() {
    return bricks.size() == capacity;
}

bool alghorithm::Bucket::operator!=(const alghorithm::Bucket &other) const {
    return !(*this == other);
}

bool alghorithm::Bucket::operator==(const alghorithm::Bucket &other) const {
    return capacity == other.capacity && bricks == other.bricks;
}

std::size_t alghorithm::Bucket::hash() {
    std::size_t seed = bricks.size();
    for(auto& i : bricks) {
        seed ^= std::hash<int>{}(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

alghorithm::Bucket::Bucket(const alghorithm::Bucket &other) :
    capacity(other.capacity), bricks(other.bricks) {

}


alghorithm::BFS::BFS(const generator::Test &t) : k(t.k), initial(t) {

}

int alghorithm::BFS::run() {
    std::queue<State> pending;
    pending.push(this->initial);

    while(!pending.empty()) {
        State current = pending.front();
        pending.pop();
        visited.insert(current.hash());

    }

}

std::vector<alghorithm::State> alghorithm::BFS::gen_states(alghorithm::State &s) {
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


alghorithm::State::State(const generator::Test &t) {
    for (auto &&bucket : t.buckets) {
        buckets.emplace_back(Bucket(bucket));
    }
}

bool alghorithm::State::operator!=(const alghorithm::State &other) const {
    return !(*this != other);
}

bool alghorithm::State::operator==(const alghorithm::State &other) const {
    if(buckets.size() != other.buckets.size())
        return false;
    for (int i = 0; i < buckets.size(); ++i) {
        if(buckets[i] != other.buckets[i])
            return false;
    }
    return true;
}

std::size_t alghorithm::State::hash() {
    std::size_t seed = buckets.size();
    for(auto& i : buckets) {
        seed ^= i.hash() + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

alghorithm::State alghorithm::State::move(int from_index, int to_index, int color) const {
    State new_state(*this);

    new_state.buckets[to_index].bricks.insert(color);
    auto it = new_state.buckets[from_index].bricks.find(color);
    new_state.buckets[from_index].bricks.erase(it);

    return new_state;
}

alghorithm::State::State(const alghorithm::State &other) {
    for (auto &&bucket : other.buckets) {
        buckets.push_back(Bucket(bucket));
    }
}
