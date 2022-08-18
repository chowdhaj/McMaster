/**
 * proc_second.c
 *
 * Kernel module that creates a seconds file in proc/
 *
 * The makefile must be used to compile this program
 *
 * Author: Jatin Chowdhary
 * Code borrowed from Operating System Concepts - 10th Edition
 */

#include <linux/init.h>     // Include library to initialize functions
#include <linux/kernel.h>   // Include library to use KERN_ALERT
#include <linux/module.h>   // This library is needed for all modules
#include <linux/proc_fs.h>  // Include library for proc filesystem
#include <linux/jiffies.h>  // Include library to use jiffies
#include <asm/uaccess.h>    // Include library for memory functions
#include <asm/param.h>      // Include library to use HZ

#define STR_BUFFER_SIZE 256      // Defines constant size of 256
#define PROC_PERMISSION 0666     // Defines the constant 0666
#define PROC_FILE_NAME "seconds" // Defines a string constant

/*
 * Global unsigned long int; for jiffies
 * This variable is used to hold number of jiffies
 */
static unsigned long int first_jiffy = 0;

// Function prototype for 'calculate_time_elapsed'
int calculate_time_elapsed(unsigned long current_jiffy);

// Function prototype for the 'proc_read' function
ssize_t proc_read(struct file *file, char __user *usr_buf,
    size_t count, loff_t *pos);

// Struct definition for 'file_operation'
static struct file_operations proc_ops = {
    .owner = THIS_MODULE,
    .read = proc_read,
};

/*
 * This function is called when the module is loaded.
 * It takes no arguments and returns an int.
 *
 * This function assigns the current value of jiffies
 *   to the global variable defined at the top. Then,
 *   it creates a file called "seconds" in proc/ using
 *   the 'proc_create' function. If the function is
 *   successful, then it will return 0, otherwise 1.
 */
int proc_init(void) {

    // Assigns jiffies to the variable 'first_jiffy'
    first_jiffy = jiffies;

    printk(KERN_INFO "Seconds Module Loaded\n");

    /*
     * Creates the /proc/seconds entry or file, and
     *   returns a 1 or 0 based on success or failure,
     *   respectively.
     *
     * PROC_FILE_NAME  :: The name of the file; defined at top
     * PROC_PERMISSION :: The permission of the file; defined at top
     * NULL            :: The name of the parent directory under /proc
     * &proc_ops       :: The file_operation structure
     */
    if (proc_create(PROC_FILE_NAME, PROC_PERMISSION,
                    NULL, &proc_ops)) {
        printk(KERN_INFO "[PC] File /proc/seconds Created!\n");
        return 0; // Return 0 for success
    } else {
        printk(KERN_INFO "[PC] Failed To Create File\n");
        return 1; // Return 1 for failure
    }
}

/*
 * This function is called when the module is removed.
 * It takes no arguments and does not have a return type.
 *
 * The role of this function is to remove the "seconds"
 *   file in the proc/ directory.
 */
void proc_exit(void) {

    /* Removes the /proc/hello entry */
    remove_proc_entry(PROC_FILE_NAME, NULL);
    // PROC_FILE_NAME is the name of the file; defined at the top

    printk(KERN_INFO "Seconds Module Terminated\n\n");
}

/*
 * This function is called each time /proc/hello is read
 * It takes 4 arguments, and they are:
 *   struct file *file
 *   char __user *usr_buf
 *   size_t count
 *   loff_t *pos
 * It returns a number indicating whether the operation
 *   was completed sucessfully, or failed.
 *
 * This function prints information into the "seconds"
 *   file in the proc/ directory, everytime the file
 *   is read (i.e. cat /proc/seconds).
 * The information in the file is:
 *   First Jiffies
 *   Current Jiffies
 *   HZ
 *   Time Elapsed
 */
ssize_t proc_read(struct file *file, char __user *usr_buf,
    size_t count, loff_t *pos) {

    int write_success = 0;
    unsigned long int current_jiffy = 0;
    char buffer[STR_BUFFER_SIZE] ;
    static int completed = 0;

    if (completed) {
        completed = 0;
        return 0;
    }

    completed = 1;           // Set completed status to 1 (true)
    current_jiffy = jiffies; // Gets current value of jiffies

    // Writes to the file /proc/seconds and returns an exit code,
    //   which is stored
    write_success =
        sprintf(buffer, "Initial Jiffy: %lu\nCurrent Jiffy: %lu\n
                         HZ = %i\nTime Elapsed(s) = %i seconds\n",
                first_jiffy, current_jiffy, HZ,
                calculate_time_elapsed(current_jiffy));

    // Exit code is checked for success & status is printed to Kernel
    if (write_success) {
        printk(KERN_INFO "[WSC] Successful Write To: /proc/seconds\n");
    } else {
        printk(KERN_INFO "[WSC] Failed To Write To: /proc/seconds\n");
    }

    /* Copies kernel space `buffer` to user space `usr_buf` */
    copy_to_user(usr_buf, buffer, write_success);

    return write_success;
}

/*
 * This function calculates the time elapsed, in seconds,
 *   since the module was loaded and returns the value
 *   as an int.
 * It calculates time elapsed by subtracting the current
 *   jiffies value from the first jiffies value, and then
 *   dividing it by HZ.
 * If the value of HZ is 0, then it will output an error
 *   message and return -1.
 */
int calculate_time_elapsed(unsigned long current_jiffy) {

    if (HZ == 0) {
        printk(KERN_INFO "ERROR: Cannot Divide By Zero!\n");
        return -1;
    } else {
        // Calculate time elapsed, in seconds, and return it
        return ((int)(current_jiffy - first_jiffy) / HZ);
    }
}

// Initialize Module (proc_init is called)
module_init(proc_init);

// Exit Module (proc_exit is called)
module_exit(proc_exit);

MODULE_LICENSE("FOSS & OSS");
MODULE_DESCRIPTION("Seconds_Proc Module");
MODULE_AUTHOR("Jatin Chowdhary");

// END
