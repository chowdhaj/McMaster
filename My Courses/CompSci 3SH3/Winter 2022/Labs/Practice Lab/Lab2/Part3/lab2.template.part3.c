/**
 * The goal of Lab 02 is to get familiar and comfortable with how
 * kernel modules are created, loaded, and removed. You will be
 * exposed to several kernel-only functions.
 *
 * Note: This file does not compile. It merely serves as a guide on
 *       how to do the extra material (i.e. Part #3)
 *
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date January 24th, 2022
 */

#include <linux/hash.h>    // Contains the constant value "GRP"
#include <linux/gcd.h>     // Defines `gcd()` function
#include <asm/param.h>     // Contains the value of `HZ`
#include <linux/jiffies.h> // Contains the value of `jiffies`

// Note: All these header files can be located via `locate file.h`.

/*
 * * * * * *
 * How To  *
 * * * * * *
 *
 * 1. Copy `part1.c` and make the following modifications by following
 *    the steps outlined below.
 * 2. Include the header files listed above to `part1.c`. The comments
 *    explain why each header file is needed.
 * 3. Print out the value of GOLDEN_RATIO_PRIME in the `simple_init()`
 *    function. See below for more information.
 * 4. Use the `gcd()` function to calculate the greatest common
 *    divisor between 3300 and 24. Print the answer to the kernel log
 *    buffer via `printk()` in the `simple_exit()` function. See
 *    below for more information.
 * 5. The global variable `jiffies` keeps track of the number of
 *    interrupts that have occurred since the system was booted. Print
 *    this value to the kernel log in both the `simple_init()` and
 *    `simple_exit()` function. See below for more information.
 *    The global variable `HZ` determines the frequency of timer
 *    interrupts; its value varies by machine type and architecture.
 *    Print this value to the kernel log in the `simple_init()`
 *    function. See below for more information.
 */

/* Step 3 */
// Add the following line to the `simple_init()` function:
printk(KERN_INFO "The Golden Ratio Prime Value Is: [%TODO]\n", TODO);
// In order to fill in "TODO", take a peak at the header file at:
// /usr/src/linux-headers-4.4.0-87/include/linux/hash.h

/* Step 4 */
// Add the following line to the `simple_exit()` function:
printk(KERN_INFO "The GCD of %d and %d is: %lu\n", 3300, 24, TODO);
// In order to fill in "TODO", take a peak at the header file at:
// /usr/src/linux-headers-4.4.0-87/include/linux/gcd.h

// Note: In order to use the `gcd()` function, the licence for the
// kernel module must be set to 'GPL'.

// # Run your code to make sure it works! # //

/* Step 5A*/
// Add the following line to the `simple_init()` function:
printk(KERN_INFO "The value of jiffies is: [%TODO]\n", TODO);
// In order to fill in "TODO", take a peak at the header file at:
// /usr/src/linux-headers-4.4.0-87/include/linux/jiffies.h

/* Step 5B */
// Add the following line to the `simple_init()` function:
printk(KERN_INFO "The value of HZ is: [%TODO]\n", TODO);
// In order to fill in "TODO", take a peak at the header file at:
// /usr/src/linux-headers-4.4.0-87/include/asm-generic/param.h

/* STEP 5C */
// Add the following line to the `simple_exit()` function:
printk(KERN_INFO "The value of jiffies is: [%TODO]\n", TODO);
// The values of "TODO" will be the same as the values in "Step 5A"

// # Run your code to make sure it works! # //

/*
 * * * * * * * * * * * * * * * *
 * Important Terminal Commands *
 * * * * * * * * * * * * * * * *
 *
 * lsmod
 *   - List all kernel models that are currently loaded in three
 *     columns: name, size, and where the module is being used.
 *     Stands for list modules.
 * dmesg
 *   - Print/control the kernel ring buffer. In other words, prints
 *     the contents of the kernel log buffer. The kernel log buffer
 *     can fill up quickly and can be cleared with the following
 *     command: `sudo dmesg -c`.
 * insmod
 *   - Inserts a module into the Linux kernel. Must be prefaced with
 *     `sudo`, and the specified file must be a (compiled) kernel
 *     object (i.e. sudo insmod NAME.ko). Notice that you must include
 *     the [(.ko)] extension.
 * rmmod
 *   - Removes a (loaded) module from the Linux kernel. Must be
 *     prefaced with `sudo`, and the name of the module is the last
 *     argument (i.e. sudo rmmod NAME). Notice that the suffix [.(ko)]
 *     is not required here.
 */

/*
 * * * * * * * * * * * * * * *
 * `printk()` VS. `printf()` *
 * * * * * * * * * * * * * * *
 *
 * As previously stated, `printk()` is the kernel equivalent of
 * `printf()`. One difference between the two is that `printk()`
 * allows a priority flag, also called a log level. The log level is
 * not a separate argument, it is concatenated to the format string.
 * The available log levels are:
 *   KERN_EMERG
 *     -> Used for system instability or imminent crashes. This is the
 *        highest level in order of severity.
 *     -> Log Level = 0
 *   KERN_ALERT
 *     -> Used when user attention is immediately required.
 *     -> Log Level = 1
 *   KERN_CRIT
 *     -> Used to inform about critical errors (hardware/software)
 *     -> Log Level = 2
 *   KERN_ERR
 *     -> Used to notify the user about non-critical errors. (i.e.
 *        Failed or problematic device recognition, driver-related
 *        problems).
 *     -> Log Level = 3
 *   KERN_WARNING
 *     -> Usually used as the default in the majority of Linux
 *        distributions, to display warnings or messages about non
 *        imminent errors.
 *     -> Log Level = 4
 *   KERN_NOTICE
 *     -> Messages that use this level of severity are about events
 *        which may be worth noting.
 *     -> Log Level = 5
 *   KERN_INFO
 *     -> Used for informational messages about the action(s)
 *        performed by the kernel.
 *     -> Log Level = 6
 *   KERN_DEBUG
 *     -> Mainly used for debugging
 *     -> Log Level = 7
 *   KERN_DEFAULT
 *     -> If the log level is omitted, then the message is printed
 *        with KERN_DEFAULT level.
 *     -> Log Level = N/A
 *   KERN_CONT
 *     -> Only used when continuing a log message with no newline
 *        enclosed.
 *     -> Log Level = N/A
 *
 * Source:
 * https://linuxconfig.org/introduction-to-the-linux-kernel-log-levels
 * https://www.kernel.org/doc/html/latest/core-api/printk-basics.html
 */

/*
 * * * * * * *
 * Makefile  *
 * * * * * * *
 *
 * Use the Makefile to compile this program. Understanding how the
 * Makefile is not as important as understanding the structure of
 * kernel modules, how modules are loaded, removed, etc.
 *
 * The Makefile produces multiple outputs. The most important file
 * ends in [.(ko)] - it stands for kernel object. This is the
 * compiled kernel module; it is loaded into the kernel.
 */

/*
 * * * * * *
 * Testing *
 * * * * * *
 *
 * Test out your kernel module:
 * a) Compile using the Makefile; type [ make ]
 * b) Insert module via [ sudo insmod part1.ko ]
 * c) Verify module is loaded via [ lsmod ]
 * d) Check kernel log buffer via [ dmesg ]
 * e) Remove module via [ sudo rmmod part1 ]
 * f) Check kernel log buffer
 * g) Verify module is removed by listing modules
 */
