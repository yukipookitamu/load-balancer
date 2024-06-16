# Makefile

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++11 -g
TARGET = loadbalancer.exe
SRC = main.cpp WebServer.cpp Request.cpp RequestQueue.cpp LoadBalancer.cpp
OBJ = $(SRC:.cpp=.o)
DEPS = WebServer.h Request.h RequestQueue.h LoadBalancer.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-$(RM) $(OBJ) $(TARGET)

# For Windows compatibility
ifeq ($(OS),Windows_NT)
    RM = del /Q
else
    RM = rm -f
endif
