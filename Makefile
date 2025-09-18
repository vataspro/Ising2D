CXX=g++
CXXFLAGS=-std=c++17

SRCS = main.cpp ranlxs.cpp ising.cpp

ising: ranlxs.o
	$(CXX) $(CXXFLAGS) $(SRCS) -o exec

clean:
	rm *.o *~ exec
