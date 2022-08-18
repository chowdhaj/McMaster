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

struct node *head = NULL;

// pointer to the struct containing the next task
struct node *tmp;

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
        }
        else {
            run(current, current->burst);
            
            current->burst = 0;

            printf("Task %s finished.\n",current->name);        
            delete(&head, current);
        }

    }
}

/**
 * Returns the next task selected to run.
 */
Task *pickNextTask()
{
    Task *nextTask = tmp->task;

    if (tmp->next == NULL)
        tmp = head;
    else
        tmp = tmp->next;

    return nextTask;
}
