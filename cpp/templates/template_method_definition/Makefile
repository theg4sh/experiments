CXX=g++ -std=c++14 -Wall -Wextra -I.

.PHONY=all main internal external show-me-the-truth clean

all:
	@echo "usage: make <internal|external>"

main:
	$(CXX) -D$(MODE)=1 -c -o main_$(MODE).o main.cpp

internal:
	$(MAKE) MODE=INTERNAL main
	$(CXX) -c -o internal_definition.o internal_definition.cpp
	$(CXX) -o internal_definition internal_definition.o main_INTERNAL.o

external:
	$(MAKE) MODE=EXTERNAL main
	$(CXX) -c -o external_definition.o external_definition.cpp
	$(CXX) -o external_definition external_definition.o main_EXTERNAL.o

show-me-the-truth:
	$(CXX) -DINTERNAL=1 -E internal_definition.cpp main.cpp > ./.internal_plain.cpp
	$(CXX) -DEXTERNAL=1 -E external_definition.cpp main.cpp > ./.external_plain.cpp
	vimdiff + ./.internal_plain.cpp ./.external_plain.cpp


clean:
	rm -f *.o
	rm -f internal_definition
	rm -f ./.internal_plain.cpp ./.external_plain.cpp
