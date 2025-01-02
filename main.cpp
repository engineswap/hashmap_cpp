#include <iostream>
#include <string>
#include <functional>
#include <tuple>
#include <array>
#include "hashmap.hpp"
using std::cout;
using std::string;

int main(){
	HashMap<string> map;

	map.insert("c++", "the best");
	map.insert("python", "the second best");
	map.insert("rust", "idk");
	map.print();

	cout << map.get("c++") << "\n";

	return 0;
}
