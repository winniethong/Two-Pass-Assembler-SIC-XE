CXX=g++
CXXFLAGS=-std=c++11 -Wall -g3 -c
OBJS = asxe.o
PROGRAM = asxe

$(PROGRAM): $(OBJS)
	$(CXX) -o $(PROGRAM) $^

asxe.o: asxe.cpp
	$(CXX) $(CXXFLAGS) asxe.cpp


clean:
	rm -f *.o $(PROGRAM)
