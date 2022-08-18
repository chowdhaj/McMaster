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

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>  // For `task_struct` and `init_task`

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
 * 4. Define/create a procedure that prints the required members
 *    of `init_task`.
 *    [ i.e. print_init_PCB() ]
 * 5. Specify module information
 *    [ i.e. MODULE_LICENSE, MODULE_DESCRIPTION, MODULE_AUTHOR ]
 */

///////////////////////////////////////////////////////////////
// STEP 4: CREATE PROCEDURE TO PRINT DATA STRUCTURE MEMBERS //
/////////////////////////////////////////////////////////////

/*
 * Prints the following members of the `task_struct` data structure:
 *   - pid
 *   - state
 *   - flags
 *   - rt_priority
 *   - policy (process)
 *   - tgid
 * The kernel priority flag is set to KERN_INFO.
 *
 * @name print_init_PCB
 * @param void No parameter(s) is/are passed
 * @return int An integer which represents the success of the
 *             function. The numeric value `0` represents success,
 *             and all other values represent failure.
 */
RETURN print_init_PCB(PARAM) {

    // 0. Before we get started, we need to peak inside the "sched.h"
    //    header file, to understand what we are dealing with. For
    //    starters, we can locate the "sched.h" header file via:
    //    `locate sched.h`.
    // TODO

    // 0a. But wait, there's an issue, which file is it and where is
    //     it located? To keep it short and simple, it is:
    //     /usr/src/linux-headers-4.4.0-87/include/linux/sched.h

    // 0b. Open the "sched.h" header file using a text editor and
    //     find the location where `task_struct` is defined.
    //     Hint: Using a text editor, like `nano`, search for
    //     "struct task_struct {", without the quotes.
    // TODO

    // 1. There are 3-ish ways to access the members of 'init_task',
    //    which is a struct, more specifically `task_struct`.

    // 1a The first way to do this is to create a struct pointer, and
    //    point to `init_task`.

    // 1b. Declare a `task_struct` pointer. To do this, use the de-
    //     reference operator ( asterisk : * ). For simplicity, call
    //     it `task`.
    // TODO

    // 1c. Initialize `task` to point to `init_task`. To achieve
    //     this use the reference operator ( ampersand : & ).
    // TODO

    // Note: Make sure you add a "\n" (newline) at the end of every
    //       `printk()` statement. This is to avoid unintended
    //       behavior.

    // 1d. Print members of the `init_task` struct, via `task`. The
    //     first member to access/print is `pid`.
    //     For example: (task->pid)
    // TODO

    // 1e. Print the `state` value of `init_task`.
    // TODO

    // 1f. Print the `flags` value of `init_task`.
    // TODO

    // 1g. Print `rt_priority`
    // TODO

    // 1h. Print (process) `policy`
    // TODO

    // 1i. Print `tgid`
    // TODO

    // Note: The `free()` function is not used anywhere, because
    //       `malloc()` is not used anywhere. It is helpful to think
    //       of the two as opposites; yin and yang - you cannot use
    //       one without the other. If we allocate memory, then we
    //       need to free it - to prevent dangling pointers, which can
    //       lead to serious security vulnerabilities via UAF; stands
    //       for (use-after-free).

    // 2. The second way to do this is to directly access the members
    //    of `init_task`. Take the code from (1) and repurpose it to
    //    directly access the members of `init_task` without the use
    //    of `task`, or any other pointer. Use the dot operator ( . )
    //    instead of the arrow operator ( -> ).

    // 2a. Access and print `pid`, directly.
    //     For example: (init_task.pid)
    // TODO

    // 2b. Print `state`.
    // TODO

    // 2c. Print `flags`.
    // TODO

    // 2d. Print `rt_priority`.
    // TODO

    // 2e. Print (process) `policy`.
    // TODO

    // 2f. Print `tgid`.
    // TODO

    // 3. The third-ish way to access the members of `init_task` is
    //    semantically identical to the first way, minus the syntactic
    //    sugar. In other words, instead of using the arrow operator
    //    ( -> ), use the asterisk ( * ) and dot ( . ) operator.
    //     For example: ((* task).pid)

    // 3a. Access and print `pid`, by de-referencing `task`.
    // TODO

    // 3b. Print `state`.
    // TODO

    // 3c. Print `flags`.
    // TODO

    // 3d. Print `rt_priority`.
    // TODO

    // 3e. Print (process) `policy`.
    // TODO

    // 3f. Print `tgid`.
    // TODO

    // 4. You might be wondering how does this work? It works because
    //    `task` is a pointer to `init_task`. So the asterisk ( * )
    //    operator is first used to "convert" the pointer into the
    //    actual data. Then, the dot ( . ) operator is used to access
    //    the members, similar to how it was done in (2). In other
    //    words, `(*task)` is the same as `init_task`, because
    //    both point to the same location in memory.

    // 4. Return `0` to indicate success.
    // TODO
}

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
 *             function. The value numeric value `0` represents
 *             success, and all other values represent failure.
 */
RETURN FUNCTION(PARAM) {

    // 1a. Print "Loading Module" via `printk()`, which is the kernel
    //     equivalent of `printf()`. However, the output is sent to a
    //     kernel log buffer. Don't forget to specify the priority
    //     flag, KERN_INFO.
    // TODO

    // 1b. Call the `print_init_PCB()` function, and make sure you
    //     check the return value (i.e. int) to make sure it executes
    //     successfully. Be sure to use the appropriate priority flag
    //     when printing an error message to the kernel log buffer.
    // TODO

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
// STEP 5: SPECIFY MODULE INFORMATION //
///////////////////////////////////////

// 5a. License information via [ MODULE_LICENSE(""); ]
//    (i.e. GPL, MIT, Beerware, etc.)
// TODO

// 5b. Brief description via [ MODULE_DESCRIPTION(""); ]
// TODO

// 5c. Author's name via [ MODULE_AUTHOR(""); ]
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
 * b) Insert module via [ sudo insmod part2.ko ]
 * c) Verify module is loaded via [ lsmod ]
 * d) Check kernel log buffer via [ dmesg ]
 * e) Remove module via [ sudo rmmod part2 ]
 * f) Check kernel log buffer
 * g) Verify module is removed by listing modules
 */
