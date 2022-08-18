/**
 * Implementation of various scheduling algorithms.
 *
 * Priority scheduling
 */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

struct node *head = NULL;

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

    while (head != NULL) {
        current = pickNextTask();

        run(current,current->burst);

        delete(&head, current);
    }
}

/**
 * Returns the next task selected to run.
 */
Task *pickNextTask()
{
struct node *temp;
Task *hp = head->task;
temp = head->next;

    while (temp != NULL) {
        if (temp->task->priority > hp->priority)
            hp = temp->task;

        temp = temp->next;
    }

    return hp;
}
