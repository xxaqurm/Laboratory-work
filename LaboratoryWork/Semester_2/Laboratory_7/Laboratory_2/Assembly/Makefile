# Makefile for Assembly Factorial Program

# Compiler and linker settings
ASM = nasm
ASMFLAGS = -f elf32
LD = ld
LDFLAGS = -m elf_i386
TARGET = task3
SOURCE = task3.asm
OBJ = $(SOURCE:.asm=.o)

# Default target
all: build run

# Build the program
build: $(TARGET)

$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $<

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

# Run the program
run:
	./$(TARGET)

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)

# Help message
help:
	@echo "Available targets:"
	@echo "  make build    - Compile the program"
	@echo "  make run      - Run the program"
	@echo "  make clean    - Remove generated files"
	@echo "  make all      - Build and run (default)"
	@echo "  make help     - Show this help message"

.PHONY: all build run clean help