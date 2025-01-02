# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17

all:
	$(CXX) $(CXXFLAGS) main.cpp hashmap.cpp -o a.out

# Clean up generated files
clean:
	rm -f a.out