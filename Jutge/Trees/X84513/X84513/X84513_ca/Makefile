CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pipe

SRCS := main.cc Arbre.cc
OBJS := $(SRCS:.cc=.o)
TARGET := main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)