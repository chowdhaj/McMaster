
/**
 * Template for Practice Lab 8. Students are strongly encouraged to
 * fill the template out as the TA walksthrough it and explains each
 * aspect of the lab. Be prepared to answer questions, because labs
 * are all about learning vis a vis engagement.
 * 
 * In this lab, you will learn about memory mapping files in C, by
 * writing a program that opens a binary file and map it to a memory
 * region using the system call ``mmap()``. The binary file contains
 * ten 4-byte integers in binary format.
 *
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date   March 14th, 2022
 */

// STEP 1 : Open the binary file and answer the following questions:
//            - What does ".bin" stand for?
//            - What 10 numbers (in binary) are in the file?
//            - Without looking at the "size", how big is the binary
//              file? (Hint: Do some math)
//            - What do you think the system call ``mmap()`` stands
//              for?
//            - What do you think the functionl ``memcpy()`` stands
//              for?
// HINT1  : hexdump -x numbers.bin
// HINT2  : xxd -b numbers.bin | cut -d" " -f2-7 | tr -d ' '

// STEP 2 : Include all required header files, stated in the PDF

// STEP 3 : Don't forget to include the ``stdio.h`` header file.
//          What does this header file contain that we need?

// STEP 4 : Specify what each header file is required for. Provide a
//          small description indicating what the header file is
//          used for.

// STEP 5 : What is a file descriptor?
// HINT   : Use ``man fcntl``

// STEP 6 : Define/declare a global int array, called 'intArray'

// STEP 7 : Declare a (signed) character pointer called 'mmapfptr'
//          What do you think 'mmapfptr' stands for?

// STEP 8 : Define the following 3 macros (i.e. #define XXX YYY)
//            - SIZE   :: The size of each integer (in bytes)
//            - COUNT  :: How many integers are in the file?
//            - MEMORY :: Total size of the file, use SIZE and COUNT
//                        to define this

int main(int argc, char const *argv[]) {
    
    // STEP 9 : Open the binary file using the ``open()`` system call.
    //          For permissions, open the file as read only. Call the
    //          file descriptor 'mmapfile_fd'.
    // HINT 1 : int XXX = open("FILE", PERMISSIONS);
    // HINT 2 : ``man -s2 open``
    // HMWK   : What is the difference between the ``open()`` system
    //          call and Library function? (This was on the midterm).

    // STEP 10 : Use the system call ``mmap()`` to memory map the file
    //           opened in the previous step, STEP 9.
    // HINT 1  : Use ``man mmap`` to figure out what arguments the
    //           ``mmap()`` system call takes. Fill in the following:
    //             - void * addr   :: 
    //             - size_t len    :: 
    //             - int prot      :: 
    //             - int flags     :: 
    //             - int fd        :: 
    //             - off_t offset  :: 
    // HINT 2   : Use ``man mmap`` to figure out what ``mmap()``
    //            returns. Appropriately store the return value.

    // STEP 11 : Answer the following questions.
    //             - What does 'len' stand for?
    //             - What does 'prot' stand for?
    //             - What does 'fd' stand for?
    //             - What is the purpose of 'flags'?
    //             - What is ``off_t``?

    // STEP 12 : Using a for-loop, retrieve the contents of the memory
    //           mapped file, and store it in 'intArray', the integer
    //           array.
    // HINT    : Use the ``memcpy()`` function. Use the 'man' pages to
    //           obtain more information about ``memcpy()``.
    /*
    for (int i = 0; i < ???; i++) {
        // TODO : Copy numbers from the memory mapped file to the
        //        integer array
        // HINT : Arguments in ``memcpy()`` need to be incremented on
        //         every iteration.
        //memcpy(???);
    }
     */
     
    // STEP 13 : Add up all the values in 'intArray', and output the
    //           final sum to the terminal. Store the result in an int
    //           called 'sum'.

    // STEP 14 : Unmap the memory file via the ``munmap()`` system
    //           call. Then, ``return 0`` and terminate the program.
    // HINT    : ``man munmap``

    // STEP 15 : For ``munmap()``, how come we do not have to cast
    //           the argument from 'char *' to 'void *'?

    // STEP 16 : What is 'void *'?

    return 0;
}
