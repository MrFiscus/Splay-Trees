CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -O2

TARGET := splay
SRCS := mainsplay.cpp splay.cpp customErrorClass.cpp
OBJS := $(SRCS:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) splay.exe