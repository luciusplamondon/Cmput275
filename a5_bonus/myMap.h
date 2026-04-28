#ifndef MYMAP_H
#define MYMAP_H

#include <vector>
#include <utility>

template <typename K, typename V>
class Map {
    std::vector<std::pair<K, V>> data;
    int find_index(const K& key, bool& found) const { //binary search
        int low = 0;
        int high = (int)data.size()-1;
        found = false;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (data[mid].first == key) {
                found = true;
                return mid;
            } else if (data[mid].first < key) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return low;
    }
public:
    Map(){}; //default
    ~Map(){}; //destructor
    Map(const Map&){};//copy 
    Map(Map&&){};//move
    Map& operator=(const Map&){};//copy assignment
    Map& operator=(Map&&){};//move assignemt
    V& operator[](const K& key) {
        bool found;
        int index = find_index(key, found);

        if (found) {
            return data[index].second;
        }
        data.insert(data.begin() + index, std::make_pair(key, V())); //key does not exist, so insert it in
        return data[index].second;
    }
    V operator()(const K& key) const { //like map but uses cons
        bool check;
        int index = find_index(key, check);

        if (check) {
            return data[index].second; //not returning a reference
        }
        return V(); // Key not found, return V
    }
    class Iterator {
        const std::pair<K, V>* ptr;
    public:
        Iterator(const std::pair<K, V>* p) : ptr(p) {}
        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr; //return bool
        }
        Iterator& operator++() {
            ptr++;
            return *this; //return ptr++
        }
        const K& operator*() const {
            return ptr->first; //return dereference (aka first)
        }
    };
    Iterator begin() const { 
        return Iterator(data.empty() ? nullptr : &data[0]); // return first element
    }
    Iterator end() const { 
        return Iterator(data.empty() ? nullptr : &data[0] + data.size()); //return last
    }
};
#endif