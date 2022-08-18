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
# Compile With Pthread
PT=-pthread
# Add Extra Libraries
IFLAG=-lrt

# The Executable To Build
# This Is The Name Of The File
TARGET=mod_sorting

make: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o $(OFLAG) $@ $(PT)

$(TARGET).o: $(TARGET).c
	$(CC) $(WFLAG) $(CFLAG) $(TARGET).c

clean:
	rm -f $(TARGET)
	rm -f $(TARGET).o
