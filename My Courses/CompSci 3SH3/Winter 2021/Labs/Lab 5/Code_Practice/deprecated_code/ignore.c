/**
 * Returns the next task selected to run.
 */
Task *pickNextTask() {
    
    int found = 0;
    tmp = head->next;
    hpl = head->task;
    
    if (thread_index == -1) {
        
        thread_index++;
        found++;
        
        while (tmp != NULL) {
            if (tmp->task->priority < hpl->priority) {
                hpl = tmp->task;
                highest_priority = hpl->priority;
                thread_index++;
            }
            tmp = tmp->next;
        }
    } else {
        
        for (int i = 0; i < (thread_index - 1); i++) {
            tmp = tmp->next;
        }
        while (tmp != NULL) {
            if (tmp->task->priority == highest_priority) {
                found++;
                hpl = tmp->task;
                break;
            }
            thread_index++;
            tmp = tmp->next;
        }
    }
    
    if (found == 0) {
        thread_index = -1;
        highest_priority = 100;
        return pickNextTask();
    }
    return hpl;  
}
