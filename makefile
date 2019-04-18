
TARGET := main.run
MAKEFLAGS += Rr
SOURCES := common.cpp main.cpp


OBJECTS := $(SOURCES:.cpp=.o)
SQLITE_OBJECTS := ./sqlite3/sqlite3.o
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) $(SQLITE_OBJECTS)
	g++ $^ -lpthread -ldl -o $@

clean:
	rm -f *.o *.run

$(SQLITE_OBJECTS): ./sqlite3/sqlite3.c ./sqlite3/sqlite3.h
	gcc -O3 -march=native -c $< -o $@

%.o: %.cpp
	g++ -Wall -Wextra -Wpedantic -Wshadow -std=c++11 -Ofast -march=native -c $< -o $@

common.o: common.cpp common.hpp sqlite3/sqlite3.h
main.o: main.cpp common.hpp sqlite3/sqlite3.h
