CXX:=g++
CXXFLAGS:= -O3 -g -std=c++11

LD_LIB_FLAGS:=-L. -I.

example.exe: main.cpp pliib.hpp pliib.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LD_LIB_FLAGS) $(LD_INCLUDE_FLAGS)
