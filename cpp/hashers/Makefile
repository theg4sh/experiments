HEADERS=$(shell find include -type f \( -iname "*.hpp" -o -iname "*.h" \))
CXXFLAGS=-Iinclude/ -std=c++17

export CPPFLAGS

all: fnv1a_test

clean:
	rm -f fnv1a_test *.o

fnv1a_test: test.o
	$(CXX) -o $@ $^

%.o: $(HEADERS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

