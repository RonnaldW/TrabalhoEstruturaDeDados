# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall

# Source files
SRCS = src/main.c src/menu.c src/paciente.c 

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = paciente

# Phony targets
.PHONY: all compile run clean

# Default target (compile and run)
all: compile run

# Explicit compile target (produces the target program)
compile: $(TARGET)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)