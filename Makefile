CXXFLAGS= -Wall -Wextra -pedantic -ggdb -std=c++11 -O0
slow: main.cpp
	$(CXX) $(CXXFLAGS) -o slow.o main.cpp
