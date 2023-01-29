//
// Created by JODE on 2023-01-29.
//
#include <unordered_map>
#include <list>
using namespace std;
class LFUCache {
private:
    int capacity;
    unordered_map<int ,list<pair<int ,int>>> frequencies;
    unordered_map<int, pair<int, list<pair<int, int>>::iterator>> cache;
    int minn;

    void insert(int key, int frequency, int value){
        frequencies[frequency].push_back({key, value});
        cache[key] = {frequency, --frequencies[frequency].end()};
    }

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        minn = 0;
    }

    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end()) {
            return -1;
        }
        int frequency = it->second.first;
        auto iter = it->second.second;
        pair<int, int> key_value = *iter;
        frequencies[frequency].erase(iter);
        if (frequencies[frequency].empty() && minn == frequency){
            minn += 1;
        }
        insert(key, frequency + 1, key_value.second);
        return key_value.second;
    }

    void put(int key, int value) {
        if (this->capacity <= 0)
            return;
        auto it = cache.find(key);
        if (it != cache.end()){
            it->second.second->second = value;
            get(key);
            return;
        }
        if (capacity == cache.size()){
            cache.erase(frequencies[minn].front().first);
            frequencies[minn].pop_front();
        }
        minn = 1;
        insert(key, 1, value);
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */