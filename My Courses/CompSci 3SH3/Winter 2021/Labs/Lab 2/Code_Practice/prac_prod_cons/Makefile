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
TARGET_C=consumer
TARGET_P=producer

make: $(TARGET_C) $(TARGET_P)

$(TARGET_C): $(TARGET_C).o
	$(CC) $(TARGET_C).o $(OFLAG) $@ $(IFLAG)

$(TARGET_C).o: $(TARGET_C).c
	$(CC) $(WFLAG) $(CFLAG) $(TARGET_C).c

$(TARGET_P): $(TARGET_P).o
	$(CC) $(TARGET_P).o $(OFLAG) $@ $(IFLAG)

$(TARGET_P).o: $(TARGET_P).c
	$(CC) $(WFLAG) $(CFLAG) $(TARGET_P).c

clean:
	rm -f $(TARGET_C)
	rm -f $(TARGET_C).o
	rm -f $(TARGET_P)
	rm -f $(TARGET_P).o

