CXX=g++
CXXFLAGS=-std=c++20 -Wall -lgsl

.PHONY: graph
.PRECIOUS: %.x

all: code/perco.x

code/perco.x: code/perco.cpp code/perco.hpp code/monte_carlo_integral.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

graph: code/perco.x results/hay.dat results/no_hay.dat
	code/graph.py results/hay
	code/graph.py results/no_hay

clean:
	@find . -type f -name "*.dat" -delete
	@find . -type f -name "*.x" -delete
clean_results:
	@find . -type f -name "*.pdf" -delete
	@find . -type f -name "*.png" -delete
