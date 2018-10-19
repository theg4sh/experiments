# Required libopenal-dev libalut-dev

INCLUDE_DIR=./include

all: src/altoolset/wav_player.o src/altoolset/context.o src/altoolset/device.o main.o
	g++ -Wall -std=c++11 -g -I$(INCLUDE_DIR) -o openal-simple $^ -lopenal -lalut

clean:
	rm -f ./src/altoolset/*.o ./*.o
	rm -f ./openal-simple

%.o: %.cpp
	g++ -Wall -std=c++11 -g -I$(INCLUDE_DIR) -c -o $@ $^ -lopenal -lalut

