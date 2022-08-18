/**
 *
 * Practice Lab 09 is about file control blocks (FCBs). A file control
 * block (FCB) is an important data structure used to represent files
 * in a system. In *nix systems, the FCBs are called ``inodes``. An
 * ``inode`` stores the attributes and disk block location(s) of the
 * respective file/directory on the system.
 * 
 * This lab requires you to write a C program (i.e. lab9.c) that takes
 * a file/folder as input (i.e. Command line argument) and outputs the
 * following attributes stored in the Object's ``inode``:
 *   1. Inode number
 *   2. File size
 *   3. Blocks
 *   4. User ID
 *   5. File permissions
 *   6. Time of last access
 *   7. Time of last modification
 *   8. Last status change time
 * To accomplish the above, you will need to use the ``stat`` data
 * structure. To learn more about ``stat``, please visit:
 * https://pubs.opengroup.org/onlinepubs/7908799/xsh/sysstat.h.html
 * 
 * In this lab, you will learn the following:
 *   1. How to obtain file attributes using the ``ls -li`` and
 *      ``stat`` commands.
 *   2. How to use the ``stat`` data structure to output file
 *      attributes in C.
 *   3. Learn about ``script`` and ``exit`` commands.
 * 
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date March 21st, 2022
 */

int main(int argc, char const *argv[]) {

    // STEP 0 : Briefly explain what is an FCB and what is an
    //          ``inode``? Why are these important? Fill in the
    //          blanks below.
    // TODO   : FCB is a f _ _ _ system structure in which the state
    //          of an open f _ _ _  is maintained. FCBs are managed
    //          by the o _ _ _ _ _ _ _ _ s _ _ _ _ _. The FCB resides
    //          in the memory of the p _ _ _ _ _ _ that uses the
    //          f _ _ _. This allows a p _ _ _ _ _ _ to have many
    //          f _ _ _ _ open at the same time.
    //          An inode is the * _ _ _ equivalent of an _ _ _. It
    //          describes a f _ _ _ s _ _ _ _ _ object such as a
    //          f _ _ _ or a f _ _ _ _ _ (aka d _ _ _ _ _ _ _ _).
    //          Each inode stores the object's a _ _ _ _ _ _ _ _ _
    //          and block locations in the s _ _ _ _ _ _ device.
    
    // STEP 1 : Create a simple text file named ``file1.txt``.
    // HINT   : Use the ``touch`` command

    // STEP 2 : Add the line "This is file 1" to ``file1.txt`` and
    //          save the changes.
    // HINT   : Use ``echo`` and redirect the output to ``file1.txt``.

    // STEP 3 : Get the inode number and other (file) attributes of
    //          ``file1.txt``. Fill in the blanks below.
    // HINT 1 : ls -li FILE_NAME
    // HINT 2 : The ``inode`` of the file is the 1st number
    // TODO   : The inode number of ``file1.txt`` is: ???
    //          The 'rwx' permissions of ``file1.txt`` is: ???
    // NOTE   : The inode number of ``file1.txt`` will (most likely)
    //          be different on your system/machine.

    // STEP 4   : What does ``l`` and ``i`` stand for in ``ls -li``?
    // HINT   : ``man ls``
    // TODO   : HOMEWORK

    // STEP 5 : Get detailed information (i.e. File attributes) and
    //          the inode number of ``file1.txt``. Fill in the blanks
    //          below. This is pretty much the same as STEP 3, but
    //          this time we are using a different command.
    // HINT   : Use the ``stat`` command.
    // TODO   : File Name = ???
    //          Inode number = ???
    //          Size = ???
    //          Permission = ???
    //          UID = ???

    // STEP 6 : Now it is time to use the ``stat`` data structure to
    //          retrieve file attributes in C. To get started, include
    //          the following header files:
    //            - Standard Library
    //            - Standard I/O
    //            - Errno
    //            - Strings
    //            - Ctime
    //               - Required to retrieve and display certain file
    //                 attributes related to time
    //            - Types (i.e. sys/types.h)
    //            - Stat (i.e. sys/stat.h)
    //              - Note: This is where the ``stat` data structure
    //                is located and defined.
    // TODO    : If time permits, explain the relevance of each header
    //           file. Otherwise, this is homework!

    // STEP 7 : Check the number of arguments provided by the user.
    //          The user should provide a single argument, which is
    //          the name of the file. If the user does not provide the
    //          correct number of arguments, indicate this in the
    //          error message. Note: We will retrieve the
    //          attributes for this file using the ``stat`` data
    //          structure.
    // HINT 1 : ``argc`` should be exactly 2. Anything else and you
    //          terminate the program. Use an if-statement.
    // HINT 2 : Use ``fprintf()`` and output the error to ``stderr``.

    // STEP 8 : If the program terminates due to an error, is it
    //          acceptable, as per Unix convention, to return 0. Why
    //          or why not?
    // TODO   : HOMEWORK

    // STEP 9 : Declare a ``stat`` struct called ``fileAttributes``.
    //          This is where the attributes of the file will be
    //          stored; in this 'struct'.
    // HINT   : struct stat NAME

    // STEP 10 : Use the ``stat()`` function to store the attributes
    //           of the file in the ``fileAttributes`` struct. Make
    //           sure you check the exit status of the ``stat()``
    //           command using an if-statement. If it fails, print
    //           an error message and indicate what the error was
    //           using ``errno``. Then, ``return -1``.
    // HINT 1  : (stat(FILE, STRUCT) != 0)
    // HINT 2  : Use ``man -s2 stat`` to get more information.
    // HINT 3  : The name of the file is in ``argv[1]``.

    //------------------------- IMPORTANT -------------------------//
    // STEP 11 : Answer the following questions:
    //             - What are file permissions? And why are they
    //               important?
    //             - What does 'drwx' stand for?
    //             - Can we change file permissions?
    //                 - Hint: ``man chmod``
    //             - How does ``chmod`` work?
    //             - What are the different modes in ``chmod``?
    //                 - Hint: ``chmod NNN XXX``
    //             - Why is ``chmod 777 XXX`` bad practice?
    //------------------------- IMPORTANT -------------------------//
    // ANSWER : 

    // STEP 12 : Adding on top STEP 10; this is the ``else`` block
    //           of the ``if`` statement. In the ``else`` block
    //           do the following:
    //             - Print the name of the file that attributes are
    //               being retrieved and displayed for
    //             - Refer to the Lab9 PDF and print the following:
    //                 - Inode
    //                 - Size (In Bytes)
    //                 - Blocks
    //                 - UID
    //                 - File Permissions
    //                     - Check if directory: S_IFDIR
    //                         - Can also use S_ISDIR()
    //                     - Check if user has read: S_IRUSR
    //                     - Check if user has write: S_IWUSR
    //                     - Read for group: S_IRGRP
    //                     - Write for group: ???
    //                     - Execute for group: ???
    //                     - Read for other: S_IROTH
    //                     - Write for other: S_IWOTH
    //                     - Execute for other: S_IXOTH
    //                     - HINT: Use the ternary operator!
    //                - Time
    //                    - Time of last access
    //                    - Time of last data modifications
    //                    - Time of last status change
    //                    - HINT: You will have to use ``ctime()``.
    //                            It takes the address of the value.

    // STEP 13: Return 0
    return 0;
}

// Extra Questions:

// Why is there no rename command in *nix systems? To rename a file,
// you need to use the ``mv`` (move) command.

// Explain the affect block size has on reading/writing files
