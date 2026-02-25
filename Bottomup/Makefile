CC := g++
CFLAGS := -Wall -std=c++11

TARGET := splay

OBJS := mainsplay.o splay.o customErrorClass.o

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

mainsplay.o: mainsplay.cpp
	$(CC) -c $<

splay.o: splay.cpp
	$(CC) -c $<

customErrorClass.o: customErrorClass.cpp
	$(CC) -c $<

run: $(TARGET)
	./$(TARGET)

clean:
	del /F /Q mainsplay.o splay.o customErrorClass.o splay.exe 2>NUL