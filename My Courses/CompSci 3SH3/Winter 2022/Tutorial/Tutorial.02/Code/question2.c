/*
 * Processes are forked multiple times in an unstructured manner to
 * create a relatively large process tree. The questions at the
 * bottom are excellent practice.
 *
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date February 1st, 2022
 */

#include <stdio.h>
#include <unistd.h>

int main() {
    
    for(int i = 0; i < 4 i++) {
        fork();
    }

    return 0;
}

/**
 * Question: Draw a process tree diagram.
 * Tip: You should do it on paper
 * 
 * Question: How many processes are created?
 * Tip: Think in terms of powers of 2
 */