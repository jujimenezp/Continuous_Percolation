CXX=g++
CXXFLAGS=-std=c++20 -Wall

.PHONY: graph
.PRECIOUS: %.x

perco.x: perco.cpp perco.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

graph: perco.x hay.dat no_hay.dat
	./graph.py hay
	./graph.py no_hay

clean:
	@rm *.dat
	@rm perco.x
