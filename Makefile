CXX:=g++
CXXFLAGS:= -O3 -g -std=c++11 -fopenmp

LD_LIB_FLAGS:=-L./ -I./



example.exe: main.o #pliib.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LD_LIB_FLAGS) $(LD_INCLUDE_FLAGS)

test: test_pliib.cpp pliib.hpp catch.hpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LD_LIB_FLAGS) $(LD_INCLUDE_FLAGS) && ./test

main.o: main.cpp pliib.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LD_LIB_FLAGS) $(LD_INCLUDE_FLAGS)

#pliib.o: pliib.cpp pliib.hpp
#	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LD_LIB_FLAGS) $(LD_INCLUDE_FLAGS) 

.PHONY: clean

clean:
	rm *.o
	rm example.exe
