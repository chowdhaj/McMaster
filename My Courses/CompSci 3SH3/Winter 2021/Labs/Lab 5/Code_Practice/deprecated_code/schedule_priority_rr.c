/**
 * Implementation of various scheduling algorithms.
 *
 * Round-robin scheduling
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

// head of the list
struct node *head     = NULL;

// pointer to the struct containing the next task
struct node *tmp      = NULL;

//struct node *prev_hpt = NULL;

Task *hpl = NULL;

// Global variables to track linked list
int most_important = MAX_PRIORITY;
int highest_priority = MAX_PRIORITY;
int thread_index = -1;

// Function prototype
Task *pickNextTask();

// add a new task to the list of tasks
void add(char *name, int priority, int burst) {
    // first create the new task
    Task *newTask = (Task *) malloc(sizeof(Task));

    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;

    // insert the new task into the list of tasks
    insert(&head, newTask);
}

/**
 * Run the priority scheduler
 */
void schedule()
{
    Task *current;

    tmp = head;

    while (head != NULL) {

        current = pickNextTask();

        if (current->burst > QUANTUM) {
            run(current, QUANTUM);
            current->burst -= QUANTUM;
            thread_index++;
        }
        else {
            run(current, current->burst);
            current->burst = 0; // Optional

            printf("Task %s finished.\n", current->name);
            delete(&head, current);
        }
    }
}

/**
 * Returns the next task selected to run.
 */
Task *pickNextTask() {

    int found = 0;

    // Reset data types to beginning of linked list
    tmp = head->next;
    hpl = head->task;

    // Iterate linked list from beginning
    if (thread_index == -1) {

        thread_index++;
        found++;

        // Iterate through entire linked list
        while (tmp != NULL) {

            // Find task with highest priority
            if (tmp->task->priority < hpl->priority) {
                hpl = tmp->task; // Save it here
                highest_priority = hpl->priority;
                thread_index++;
            }

            // Go to next task/process
            tmp = tmp->next;
        }

    // Iterate linked list from previous index
    } else {

        /* 
         * Restore data types to previous index
         * The previous index is where the previously executed
         *   task is located in the linked list
         */ 
        for (int i = 0; i < (thread_index - 1); i++) {
            // if (tmp->task->priority == highest_priority) found++; 
            tmp = tmp->next;
        }

        // Iterate through remaining linked list
        while (tmp != NULL) {

            /* 
             * If a task in the remaining list has the same priority
             *   as the previously executed task, then return it to
             *   the 'schedule()' function
             */
            if (tmp->task->priority == highest_priority) {
                found++;
                hpl = tmp->task;
                return hpl;
            }
            thread_index++;
            tmp = tmp->next;
        }
    }

    /* 
     * If a task with the same priority as the previous task was not
     *   found, then reset the thread index, and call this function
     *   again to find the next task/process with the highest
     *   priority
     */
    if (found == 0) {
        thread_index = -1; // Reset thread index
        highest_priority = MAX_PRIORITY; // Reset highest priority
        return pickNextTask(); // Return the result
    }

    // Return task with highest priority
    return hpl;
}

/**
 * IGNORE EVERYTHING BELOW ME
 */

/*

Task *pickNextTask() {

    struct node *temp;
    Task *hp = head->task;
    temp = head->next;

    Task *nextTask = tmp->task;

    if (tmp->next == NULL) {
        tmp = head;
    } else {
        // TODO: Implement priority

        // if priority of next task is smaller, go to head
        // otherwise continue down the linked list

        tmp = tmp->next;

    }

    return nextTask;
}
*/

/*

Task *pickNextTask() {
struct node *temp;
Task *hp = head->task;
temp = head->next;

    while (temp != NULL) {
        if (temp->task->priority > hp->priority) {
            hp = temp->task;
        }
        else if (temp->task->priority == hp -> priority) {
           printf("%s Same Priority As %s\n", temp->task->name, hp->name);
        }

        temp = temp->next;
    }

    return hp;
}
*/

/*

Task *pickNextTask() {

    Task *nextTask = tmp->task;

    if (tmp->next == NULL)
        tmp = head;
    else
        tmp = tmp->next;

    return nextTask;
}
*/

/*
    while (temp != NULL) {
        if (temp->task->priority > hp->priority) {
            hp = temp->task;
        }

        temp = temp->next;
    }
*/
