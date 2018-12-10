CXX = g++
CXXFLAGS = -Wall -std=c++14 -g

code :
	$(CXX) -o code ./Bookstore/*.cpp $(CXXFLAGS)

clean:
	rm score -f
