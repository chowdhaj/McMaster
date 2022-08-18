/**
 * proc_jiffy.c
 *
 * Kernel module that creates a jiffies file in proc/
 *
 * The makefile must be used to compile this program
 *
 * Author: Jatin Chowdhary
 * Code borrowed from Operating System Concepts - 10th Edition
 */

#include <linux/init.h>    // Library to initialize functions or data
#include <linux/kernel.h>  // Includes library for KERN_ALERT
#include <linux/module.h>  // This library is needed for all modules
#include <linux/proc_fs.h> // Include library for proc filesystem
#include <linux/jiffies.h> // Library for Jiffies
#include <asm/uaccess.h>   // Include library for memory functions

#define MSG_BUFFER_SIZE 256      // Defines a constant number: 256
#define PROC_PERMISSION 0666     // Defines a constant number: 0666
#define PROC_FILE_NAME "jiffies" // Defines a constant string

// Function prototype for the 'proc_read' function
ssize_t proc_read(struct file *file, char __user *usr_buf,
    size_t count, loff_t *pos);

// This is a struct definition for files
static struct file_operations proc_ops = {
    .owner = THIS_MODULE,
    .read = proc_read,
};

/*
 * This function is called when the module is loaded.
 * It takes no arguments and returns an int.
 *
 * The job of this function is to create a file called
 *   "jiffies" in /proc. If the function is successful
 *   then it will return 0, otherwise 1.
 */
int proc_init(void) {

    printk(KERN_INFO "Jiffy Module Loaded\n");

    /*
     * Creates the /proc/jiffies entry or file, and returns a 1 or
     *   0 based on success or failure, respectively
     *
     * PROC_FILE_NAME  :: The name of the file and is defined above
     * PROC_PERMISSION :: The permision of the file; defined above
     * NULL            :: The name of the parent directory under /proc
     * &proc_ops       :: The file_operation structure
     */
    if (proc_create(PROC_FILE_NAME, PROC_PERMISSION, 
                    NULL, &proc_ops)) {
        printk(KERN_INFO "[PC] File /proc/jiffies Created!\n");
        return 0; // Return 0 for success
    } else {
        printk(KERN_INFO "[PC] Failed To Create File\n");
        return 1; // Return 1 for failure
    }
}

/*
 * This function is called when the module is removed.
 * It takes no arguments and does not return anything.
 *
 * The job of this function is to remove the "jiffies"
 *   file in the directory /proc.
 */
void proc_exit(void) {

    /* Removes the /proc/jiffies entry or file */
    remove_proc_entry(PROC_FILE_NAME, NULL);
    // PROC_FILE_NAME is the name of the file and is defined above

    printk(KERN_INFO "Jiffy Module Terminated\n\n");
}

/*
 * This function is called each time /proc/hello is read
 * It takes 4 arguments, and they are:
 *    struct file *file
 *    char __user *usr_buf
 *    size_t count
 *    loff_t *pos
 * It returns a number indicating whether the operation
 *   was completed successfully, or failed.
 *
 * The job of this function is to write data to the "jiffies"
 *   file in /proc, and update it with the current value of
 *   jiffies retrieved from 'jiffies.h'.
 */
ssize_t proc_read(struct file *file, char __user *usr_buf,
    size_t count, loff_t *pos) {

    int write_success = 0;
    char buffer[MSG_BUFFER_SIZE] ;
    static int completed = 0;

    if (completed) {
        completed = 0;
        return 0;
    }

    completed = 1;

    // Writes to the file /proc/jiffies and returns an exit code,
    //   which is stored
    write_success = sprintf(buffer, "Current Value Of Jiffies: %lu\n",
        jiffies);

    // Exit code is checked for success & status is printed to Kernel
    if (write_success) {
        printk(KERN_INFO "[WSC] Successful Write To: /proc/jiffies\n");
    } else {
        printk(KERN_INFO "[WSC] Failed To Write To: /proc/jiffies\n");
    }

    /* Copies kernel space `buffer` to user space `usr_buf` */
    copy_to_user(usr_buf, buffer, write_success);

    // Return exit code indicating success or failure
    return write_success;
}

// Initialize Module (proc_init is called)
module_init(proc_init);

// Exit Module (proc_exit is called)
module_exit(proc_exit);

MODULE_LICENSE("FOSS & OSS");
MODULE_DESCRIPTION("Proc_Jiffies Module");
MODULE_AUTHOR("Jatin Chowdhary");

// END
