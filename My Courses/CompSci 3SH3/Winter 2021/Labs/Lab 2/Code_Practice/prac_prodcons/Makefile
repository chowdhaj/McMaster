# The Compiler Command
# 'gcc' is for C && 'g++' is for C++
CC=gcc

# Flags For The Compiler
# Do Not Optimize Code
EFLAG=-O0
# Create Object File
OFLAG=-o
# Compile Source
CFLAG=-c
# Compiler Warnings
WFLAG=-Wall
# Add Extra Libraries
IFLAG=-lrt

# The Executable To Build
# This Is The Name Of The File
TARGET=prodcons

make: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o $(OFLAG) $@ $(IFLAG)

$(TARGET).o: $(TARGET).c
	$(CC) $(WFLAG) $(CFLAG) $(TARGET).c

clean:
	rm -f $(TARGET)
	rm -f $(TARGET).o
