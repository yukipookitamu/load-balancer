# Makefile

CC = g++
CCFLAGS = -Wall -Werror -Wextra -std=c++11 -g
TARGET = loadbalancer
SRC = main.cpp WebServer.cpp Request.cpp RequestQueue.cpp LoadBalancer.cpp
OBJ = $(SRC:.cpp=.o)
DEPS = WebServer.h Request.h RequestQueue.h LoadBalancer.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
