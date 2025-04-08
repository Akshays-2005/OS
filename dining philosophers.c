#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // for sleep()
#include <semaphore.h>
#include <windows.h>  // Required for semaphore simulation on Windows

#define MAX 100

int hungry[MAX];        // Hungry philosopher positions
int eaten[MAX] = {0};   // Track eating status
int hungry_count = 0;

sem_t mutex;

// wait and signal wrappers
void wait_(sem_t* s) {
    sem_wait(s);
}

void signal_(sem_t* s) {
    sem_post(s);
}

// Print all hungry philosophers as waiting
void print_waiting() {
    for (int i = 0; i < hungry_count; i++) {
        printf("P %d is waiting\n", hungry[i]);
    }
}

// Simulate eating using semaphores
void simulate_eating(int eat_limit) {
    int finished = 0;

    // Init semaphore with eat limit (1 or 2)
    sem_init(&mutex, 0, eat_limit);

    while (finished < hungry_count) {
        print_waiting();

        int served = 0;
        for (int i = 0; i < hungry_count && served < eat_limit; i++) {
            if (!eaten[i]) {
                wait_(&mutex);
                printf("P %d is granted to eat\n", hungry[i]);

                // Simulate eating
                sleep(1);

                printf("P %d has finished eating\n", hungry[i]);
                signal_(&mutex);

                eaten[i] = 1;
                served++;
                finished++;
            }
        }
    }

    sem_destroy(&mutex);
}
int main() {
    int total_philosophers;
    int choice;

    printf("Enter the total number of philosophers: ");
    scanf("%d", &total_philosophers);

    printf("How many are hungry: ");
    scanf("%d", &hungry_count);

    for (int i = 0; i < hungry_count; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, total_philosophers);
        scanf("%d", &hungry[i]);
    }

    do {
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Reset eaten state
        for (int i = 0; i < hungry_count; i++) {
            eaten[i] = 0;
        }

        if (choice == 1) {
            printf("Allow one philosopher to eat at any time\n");
            simulate_eating(1);
        } else if (choice == 2) {
            printf("Allow two philosophers to eat at any time\n");
            simulate_eating(2);
        }

    } while (choice != 3);

    return 0;
}

/* Output:
Enter the total number of philosophers: 5
How many are hungry: 3
Enter philosopher 1 position (1 to 5): 2
Enter philosopher 2 position (1 to 5): 4
Enter philosopher 3 position (1 to 5): 5

1. One can eat at a time
2. Two can eat at a time
3. Exit
Enter your choice: 1
Allow one philosopher to eat at any time
P 2 is waiting
P 4 is waiting
P 5 is waiting
P 2 is granted to eat
P 2 has finished eating
P 2 is waiting
P 4 is waiting
P 5 is waiting
P 4 is granted to eat
P 4 has finished eating
P 2 is waiting
P 4 is waiting
P 5 is waiting
P 5 is granted to eat
P 5 has finished eating

1. One can eat at a time
2. Two can eat at a time
3. Exit
Enter your choice: 2
Allow two philosophers to eat at any time
P 2 is waiting
P 4 is waiting
P 5 is waiting
P 2 is granted to eat
P 2 has finished eating
P 4 is granted to eat
P 4 has finished eating
P 2 is waiting
P 4 is waiting
P 5 is waiting
P 5 is granted to eat
P 5 has finished eating

1. One can eat at a time
2. Two can eat at a time
3. Exit
Enter your choice: 3
*/
