CXX = g++
CXXFLAGS = -Wall -std=c++14

code :
	$(CXX) -o code ./Bookstore/*.cpp $(CXXFLAGS)

run :
	./code

clean:
	-rm -f *.o
