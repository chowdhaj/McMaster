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
void schedule() {
    Task *current;

    while (head != NULL) {
        current = pickNextTask();
        run(current,current->burst);
        delete(&head, current);
    }
}

/**
 * Returns the next task selected to run.
 * 
 * Determines the task in a list of tasks with the shortest CPU burst
 * time and returns it to the calling function. The task with the
 * shortest burst time is calculated by iterating through all the
 * tasks and finding the one with the shortest CPU burst time. This
 * entire operation is done in O(N) time. 
 *
 * @returns The Task struct with the shortest CPU burst time
 */
Task *pickNextTask() {

    struct node *temp;
    Task *hp = head->task;
    temp = head->next;

    // Iterate through linked list containing tasks
    while (temp != NULL) {

        // If current task has smaller burst time than next, then:
        if (temp->task->burst < hp->burst) {
            hp = temp->task; // Save it
        }

        // Go to next task in linked list
        temp = temp->next;
    }

    // Return task with shortest CPU burst time
    return hp;
}
