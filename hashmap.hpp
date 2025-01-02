#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <tuple>
#include <vector>
#include <stdexcept>
#include <array>
#include <set>
using std::cout;
using std::string;

template <typename T> 
using HashPair = std::tuple<string,T>; // Whats stored in associative array

template <typename T> 
class HashMap{
public:

	HashMap();

	void insert(string key, T value, bool resizing=false);

	T get(string key);

	void print();

	void remove(string key);

	void resize(int size);

	double getLoadFactor();

private:
	std::vector<std::optional<HashPair<T>>> associativeArr;
	
	// We need to track the number of assigned values to efficiently compute the load factor
	int assignedValues;

	std::hash<string> hasher;
};