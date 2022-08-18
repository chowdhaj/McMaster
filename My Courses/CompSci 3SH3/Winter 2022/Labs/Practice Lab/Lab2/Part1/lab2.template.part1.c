/*
 * The goal of Lab 02 is to get familiar and comfortable with how
 * kernel modules are created, loaded, and removed. You will be
 * exposed to several kernel-only functions.
 *
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date January 24th, 2022
 */

#include <linux/printk.h>
#include <linux/module.h>
#include <linux/kernel.h>

/*
 * * * * * *
 * How To  *
 * * * * * *
 *
 * 1. Define/create the entry function.
 *    [ i.e. simple_init() ]
 * 2. Define/create the exit function.
 *    [ i.e. simple_exit() ]
 * 3. Create modules that register entry/exit points.
 *    [ i.e. module_init(), module_exit() ]
 * 4. Specify module information
 *    [ i.e. MODULE_LICENSE, MODULE_DESCRIPTION, MODULE_AUTHOR ]
 */

/////////////////////////////////////////////////
// STEP 1: CREATE MODULE ENTRY POINT FUNCTION //
///////////////////////////////////////////////

/*
 * This function is invoked when the module is loaded into the
 * kernel. This function will serve as the module entry point. It
 * is kind of like the `main()` function, in the sense that it is
 * the first function to be executed.
 *
 * @name simple_init
 * @param void No parameter(s) is/are passed
 * @return int An integer which represents the success of the
 *             function. The numeric value `0` represents success,
 *             and all other values represent failure.
 */
RETURN FUNCTION(PARAM) {

    // 1a. Print "Loading Module" via `printk()`, which is the kernel
    //     equivalent of `printf()`. However, the output is sent to a
    //     kernel log buffer.
    // TODO

    // Note: Don't forget to add a newline at the end of the message.
    //       (i.e. "\n")

    // 1b. Redo (1a) but specify the priority flag ( KERN_INFO ).
    //     Note: KERN_INFO is defined as an informational message.
    // TODO

    // TIP: When using `printk()`, make sure you add a "\n" at the
    //      end. Failure to do so will produce unintended results.
    
    // 1c. Return `0` to indicate success.
    // TODO
}

////////////////////////////////////////////////
// STEP 2: CREATE MODULE EXIT POINT FUNCTION //
//////////////////////////////////////////////

/*
 * This function serves as the module exit point; this function will
 * be called when the module is removed from the kernel.
 *
 * @name simple_exit
 * @param void No parameter(s) is/are passed
 * @return void No type is returned
 */
RETURN FUNCTION(PARAM) {

    // 2a. Print "Removing Module" via `printk()` and specify the
    //     priority flag as ( KERN_INFO )
    // TODO

    // Note: Don't forget to add a newline at the end of the message.
    //       (i.e. "\n")
}

/////////////////////////////////////////////////////////////////
// STEP 3: CREATE MODULES THAT REGISTER ENTRY AND EXIT POINTS //
///////////////////////////////////////////////////////////////

// 3a. Create [ module_init(); ] function:
// TODO

// 3b. Create [ module_exit(); ] function:
// TODO

// Note: The names of these macros cannot be changed, where as the
// arguments can be any function. In other words, (module_init) is
// absolute and (simple_init) can be renamed to anything else.

/////////////////////////////////////////
// STEP 4: SPECIFY MODULE INFORMATION //
///////////////////////////////////////

// 4a. License information via [ MODULE_LICENSE(""); ]
//    (i.e. GPL, MIT, Beerware, etc.)
// TODO

// 4b. Brief description via [ MODULE_DESCRIPTION(""); ]
// TODO

// 4c. Author's name via [ MODULE_AUTHOR(""); ]
// TODO

// Note: Module information is not required for the code to compile.
// However, we include it because it is standard practice in
// developing kernel modules.

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
