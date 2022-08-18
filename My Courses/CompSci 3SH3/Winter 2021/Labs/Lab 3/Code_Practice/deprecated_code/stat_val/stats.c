#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUMBER_OF_THREADS 3

// Global variables
int size, minimum, maximum;
float average;

// Function prototypes for helper methods
int print_greeting_message(void);
int is_argument_size_valid(int argc);
int set_array_size(int argc);
int print_synopsis(int argc);
int print_result();

// Function prototypes for threads
void *thread_func_calc_avg(void *arr);
void *thread_func_calc_max(void *arr);
void *thread_func_calc_min(void *arr);

int main(int argc, char *argv[]) {
        
    if (is_argument_size_valid(argc)) {
        print_greeting_message();
        print_synopsis(argc);
        set_array_size(argc);
    } else {
        return 1;
    }
    
    int nums[size];

    // Copy contents of args to array
    for (int i = 1; i < argc; i++) {
        // Print numbers in 'argv' 
        // Useful for debugging
        //printf("%s ", argv[i]);
        nums[i-1] = atoi(argv[i]);
    }
    
    //pthread_t thread_statistics[NUMBER_OF_THREADS];

    // Declare threads
    pthread_t thread_avg,
              thread_max,
              thread_min;
              
    // Create threads
    
    int status[NUMBER_OF_THREADS];

    status[0] = pthread_create(&thread_avg, NULL,
        thread_func_calc_avg, (void *)nums);

    status[1] = pthread_create(&thread_max, NULL,
        thread_func_calc_max, (void *)nums);

    status[2] = pthread_create(&thread_min, NULL,
        thread_func_calc_min, (void *)nums);
        
    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        if (status[i] == 0) {
            printf("Thread #%d created successfully\n", i);
        }
    }

    // Join threads
    status[0] = pthread_join(thread_avg, NULL);
    status[1] = pthread_join(thread_max, NULL);
    status[2] = pthread_join(thread_min, NULL);
    
    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        if (status[i] == 0) {
            printf("Thread #%d joined successfully\n", i);
        }
    }
    
    // Print result
    print_result();
    printf("END\n");

    return 0;
}

// Thread function to compute maximum
void *thread_func_calc_avg(void *arr) {
    
    pthread_t id = pthread_self();
    
    int *nums = (int *) arr;

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += nums[i];
    }
    average = (float) sum / (float) size;

    printf("Thread #%lu finished\n", id);
    pthread_exit(0);
}

// Thread function to compute minimum
void *thread_func_calc_min(void *arr) {
    
    pthread_t id = pthread_self();
    
    int *nums = (int *) arr;

    minimum = nums[0];
    for (int i = 1; i < size; i++) {
        if (minimum > nums[i]) {
            minimum = nums[i];
        }
    }
    printf("Thread #%lu finished\n", id);
    pthread_exit(0);
}

void *thread_func_calc_max(void *arr) {
    
    pthread_t id = pthread_self();
    
    int *nums = (int *) arr;

    maximum = nums[0];
    for (int i = 1; i < size; i++) {
        if (maximum < nums[i]) {
            maximum = nums[i];
        }
    }
    printf("Thread #%lu finished\n", id);
    pthread_exit(0);
}

/*
int create_all_threads(int thread_int_id, int arr[]) {
    
    int status = -1;
    
    switch(thread_int_id) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        default:
            status = -1;
            break;
        
        
    }
    
    return status;
    
}
*/

// Print the result of the stats computation
int print_result() {
    
    printf("=======================\n");
    printf("Average is: %.2f\n", average);
    printf("Maximum is: %d\n",   maximum);
    printf("Minimum is: %d\n",   minimum);
    printf("=======================\n");
    
    return 0;
}

// Set the size of the array
int set_array_size(int argc) {
    
    size = (argc - 1);
    return 0;
    
}

int print_synopsis(int argc) {

    printf("%s %d %s", 
        "There are", 
        (argc - 1),
        "numbers to compute statisics for\n");
        
    return 0;
}

// Print greeting message
int print_greeting_message(void) {
    
    printf("|----------------------|\n");
    printf("| Basic Stats Analyzer |\n");
    printf("| Via Threads In C     |\n");
    printf("|----------------------|\n");
    
    return 0;
}

// Check if the arguments in main are correct size
int is_argument_size_valid(int size) {
        
    if (size >= 2) {
        return 1;
    } else {
        printf("%s%s %d %s", 
            "Invalid Number Of Arguments\n",
            "Please provide more than", 
            size, 
            "argument\n");
    }
    return 0;
}
