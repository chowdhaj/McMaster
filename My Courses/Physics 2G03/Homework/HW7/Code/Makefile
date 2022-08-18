# A better Makefile

CPP=c++
CFLAG=-O0
LFLAG=-o
OFLAG=-c
OBJECT_FILES=testsort.o sort.o
TS_SOURCE_FILES=testsort.cpp
S_SOURCE_FILES=sort.cpp
EXECUTABLES=testsort sort

make: testsort

testsort: $(OBJECT_FILES)
	$(CPP) $(CFLAG) $(OBJECT_FILES) $(LFLAG) $@

testsort.o: testsort.cpp sort.h
	$(CPP) $(CFLAG) $(TS_SOURCE_FILES) $(OFLAG)
 
sort.o: sort.cpp sort.h
	$(CPP) $(CFLAG) $(S_SOURCE_FILES) $(OFLAG)

clean: 
	rm -f $(OBJECT_FILES) 
	rm -f $(EXECUTABLES)
