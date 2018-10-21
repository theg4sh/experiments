# Required libopenal-dev libalut-dev

INCLUDE_DIR=./include

all: src/altoolset/wav_player.o \
	src/altoolset/queue_player.o \
	src/altoolset/silence_generator.o \
	src/altoolset/sin_generator.o \
	src/altoolset/context.o \
	src/altoolset/device.o \
	main.o
	g++ -Wall -std=c++14 -g -I$(INCLUDE_DIR) -o openal-simple $^ -lopenal -lalut -lpthread \
		-lboost_system -lboost_program_options -lboost_filesystem

clean:
	rm -f ./src/altoolset/*.o ./*.o
	rm -f ./openal-simple

%.o: %.cpp
	g++ -Wall -std=c++14 -g -I$(INCLUDE_DIR) -c -o $@ $^ -lopenal -lalut \
		-lboost_system -lboost_program_options -lboost_filesystem

