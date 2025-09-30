# Makefile for Cache Simulator Concepts Demo

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = cache_demo
SRC = cache_demo.c

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
	@echo "Build complete! Run with: ./$(TARGET)"

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
	@echo "Cleaned up build files"

# Help target
help:
	@echo "Available targets:"
	@echo "  make          - Build the demo program"
	@echo "  make run      - Build and run the demo"
	@echo "  make clean    - Remove built files"
	@echo "  make help     - Show this help message"