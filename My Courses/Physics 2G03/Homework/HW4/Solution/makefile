# A better Makefile

CPP=c++
CFLAG=-O0
LFLAG=-o
OFLAG=-c
OBJECT_FILES=pi.o
SOURCE_FILES=pi.cpp
EXECUTABLES=pi

make: pi

pi: $(OBJECT_FILES)
	$(CPP) $(CFLAG) $(OBJECT_FILES) $(LFLAG) $@

pi.o:
	$(CPP) $(CFLAG) $(SOURCE_FILES) $(OFLAG)

clean:
	rm -f $(OBJECT_FILES)
	rm -f $(EXECUTABLES)