/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>
#include "task.h"

// run this task for the specified time slice
void run(Task *task, int slice) {
    printf("Running Task: [N = %s] [P = %d] [B = %d] for %d units.\n",
        task->name, task->priority, task->burst, slice);
}
