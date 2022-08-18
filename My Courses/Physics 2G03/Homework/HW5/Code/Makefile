# My sine program in one file

sine1file: sine1file.o
	c++ sine1file.o -lm -o sine1file

sine1file.o: sine1file.cpp
	c++ sine1file.cpp -c

# My sine program using my function sine (separate files)

sine: sinemain.o sine.o
	c++ sinemain.o -lm sine.o -o sine

sinemain.o: sinemain.cpp sine.h
	c++ sinemain.cpp -c

sine.o: sine.cpp sine.h
	c++ sine.cpp -c

# Sine program using the standard library function sin

sinestandard: sinestandard.o
	c++ sinestandard.o -lm -o sinestandard

sinestandard.o: sinestandard.cpp
	c++ sinestandard.cpp -c





