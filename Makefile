CXX:=g++
CXXFLAGS:= -O0 -g -std=c++11

LD_LIB_FLAGS:=-L./ -I./

example.exe: main.o #pliib.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LD_LIB_FLAGS) $(LD_INCLUDE_FLAGS)

main.o: main.cpp #pliib.o
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LD_LIB_FLAGS) $(LD_INCLUDE_FLAGS)

#pliib.o: pliib.cpp pliib.hpp
#	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LD_LIB_FLAGS) $(LD_INCLUDE_FLAGS) 

.PHONY: clean

clean:
	rm *.o
	rm example.exe
