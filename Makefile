CXX = g++
CXXFLAGS = -Wall -std=c++14 -O2

code :
	$(CXX) -o code ./Bookstore/*.cpp $(CXXFLAGS)

clean:
	rm score -f