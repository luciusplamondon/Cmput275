#include <iostream>
#include "intSet.h"

void intSet::grow() { //dynamically growing array baby!!!
    capacity *= 2;
    int *newData = new int[capacity];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}
intSet::intSet() : data{new int[4]}, size{0}, capacity{4} {}  // Default Constructor

intSet::intSet(const intSet& is) : data{new int[is.capacity]}, size{is.size}, capacity{is.capacity} { // Copy Constructor, creates a deep copy
    for (int i = 0; i < size; ++i) {
        data[i] = is.data[i]; //simple for loop that copies data from to the new array
    }
}
intSet& intSet::operator=(const intSet& is) { // Copy Assignment Operator
    if (this == &is) return *this; // Self-assignment check
    
    int *newData = new int[is.capacity]; //new array = size of assignment
    for (int i = 0; i < is.size; ++i) {
        newData[i] = is.data[i]; //simple for loop that copies data from before
    }
    
    delete[] data; // Clean up old memory
    data = newData;// make data new data
    size = is.size; // make old size into new size
    capacity = is.capacity; // make old capacity to new capacity
    return *this;
}
intSet::intSet(intSet &&is) : data{is.data}, size{is.size}, capacity{is.capacity} { // Move Constructor (move items into here before getting deleted by a function)
    is.data = nullptr;
    is.size = 0;
    is.capacity = 0;
}

intSet& intSet::operator=(intSet &&is) { // Move Assignment Operator
    if (this == &is) return *this; //if it is the same thing do nothing
    
    delete[] data; // Clean up existing resource
    
    data = is.data; //is data is now this data
    size = is.size;// his size is my size, ayo?
    capacity = is.capacity;// ext
    
    is.data = nullptr;// same thing as the move constructor
    is.size = 0;
    is.capacity = 0;
    return *this;
}

intSet::~intSet() { // Destructor
    delete[] data; // simply delete data, no linked list thankfully, i love dynamically growing array :)
}

intSet intSet::operator|(const intSet &other) const { // get the union of them
    intSet result = *this; // Start with copy of first set
    for (int i = 0; i < other.size; ++i) {
        result.add(other.data[i]); // check add
    }
    return result;
}
intSet intSet::operator&(const intSet &other) const { // get the intersection
    intSet result;
    for (int i = 0; i < size; ++i) {
        if (other.contains(data[i])) {//if both have that item, put it in the list
            result.add(data[i]);
        }
    }
    return result;
}
bool intSet::operator==(const intSet &other) const {//Return true is both sets are the same
    if (size != other.size) return false;//if the sizes dont match, dont even bother to contine
    for (int i = 0; i < size; ++i) { //if somehow they are the same, we must check if every item is the same unfortunatly
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

bool intSet::isSubset(const intSet &s) const { // Returns true if every element in 's' exists in this
    for (int i = 0; i < s.size; ++i) {
        if (!this->contains(s.data[i])) return false; // for loop that check if every element is in this
    }
    return true;
}

bool intSet::contains(int e) const { //return true if it does contain e
    for (int i = 0; i < size; ++i) { //go through array until e == data[i]
        if (data[i] == e) return true;
    }
    return false;
}

void intSet::add(int e) {
    if (contains(e)) return; // no duplicates are allowed
    
    if (size == capacity) grow();// if capacity reached, grow it using dynamic array baby:)
    
    int i = size - 1; //sorting it here to make output much easier
    while (i >= 0 && data[i] > e) {
        data[i + 1] = data[i];
        --i;
    }
    data[i + 1] = e;
    size++;
}

void intSet::remove(int e) {// remove item in the set
    for (int i = 0; i < size; ++i) {
        if (data[i] == e) { //item found so delete it
            for (int j = i; j < size - 1; ++j) { //shift every int past the deleted int to the left since deleting the int leaves a gap in our array
                data[j] = data[j + 1];
            }
            size--;
            return; 
        }
    }
}
std::ostream& operator<<(std::ostream& out, const intSet& is) { //output
    out << "(";
    for (int i = 0; i < is.size; ++i) { // since its already sorted, we simply print the array
        out << is.data[i];
        if (i < is.size - 1) out << ", ";
    }
    out << ")";
    return out;
}