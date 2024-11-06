# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -I"Link to your raylib src folder" -Wno-enum-compare -Wno-unused-variable -fpermissive
LDFLAGS := -L"Link to your raylib src folder" -lraylib -lopengl32 -lgdi32 -lwinmm

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
BIN := raylib_project

.PHONY: all clean run

all: $(BIN) run

$(BIN): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run:
	./$(BIN)

clean:
	rm -f $(OBJS) $(BIN)

