
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
TARGET = calculator
SOURCES = main.c Calculator.c
HEADERS = Calculator.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) -lm

clean:
	rm -f $(TARGET) $(TARGET).exe

.PHONY: all clean
