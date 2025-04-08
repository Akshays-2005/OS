#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_PROCESSES 100

struct Process {
    int cap, per, pno, deadline;
};
typedef struct Process pro;

int queue[MAX_PROCESSES], front = -1, rear = -1;

void enqueue(int item) {
    if (rear >= MAX_PROCESSES - 1) {
        printf("Queue is full\n");
        return;
    }
    if (front == -1) front = 0;
    rear++;
    queue[rear] = item;
}

int dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue[front++];
}

// Function to sort processes based on earliest deadline
void sortOnDeadline(int n, pro* p[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j]->deadline > p[j+1]->deadline) {
                pro* temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void EDF(pro* p[], int n) {
    sortOnDeadline(n, p);

    float utilization = 0;
    for (int i = 0; i < n; i++) {
        utilization += (float)p[i]->cap / p[i]->per;
    }

    if (utilization > 1) {
        printf("Warning: Schedule may not be feasible (Utilization: %.2f)\n", utilization);
        return;
    }

    printf("\nEarliest Deadline First Schedule Execution:\n");
    for (int i = 0; i < n; i++) {
        enqueue(p[i]->pno);
        printf("Time %d: Executing process %d (Capacity: %d, Period: %d, Deadline: %d)\n",
               i, p[i]->pno, p[i]->cap, p[i]->per, p[i]->deadline);
        int completed = dequeue();
        if (completed != -1) {
            printf("Time %d: Process %d completed\n", i, completed);
        }
    }
}

int main() {
    int num;
    printf("Enter the number of processes: ");
    if (scanf("%d", &num) != 1 || num <= 0 || num > MAX_PROCESSES) {
        printf("Invalid input\n");
        return 1;
    }

    pro* p[MAX_PROCESSES];
    for (int i = 0; i < num; i++) {
        p[i] = malloc(sizeof(pro));
        if (!p[i]) {
            printf("Memory allocation failed\n");
            for (int j = 0; j < i; j++) free(p[j]);
            return 1;
        }

        printf("Enter process %d number: ", i + 1);
        scanf("%d", &p[i]->pno);
        printf("Enter capacity: ");
        scanf("%d", &p[i]->cap);
        printf("Enter period: ");
        scanf("%d", &p[i]->per);
        p[i]->deadline = p[i]->per;  // Initial deadline is set to period
    }

    EDF(p, num);  // Call to EDF function

    // Cleanup
    for (int i = 0; i < num; i++) {
        free(p[i]);
    }
    return 0;
}

/*Output:
Enter the number of processes: 2
Enter process 1 number: 1
Enter capacity: 25
Enter period: 50
Enter process 2 number: 2
Enter capacity: 35
Enter period: 80

Earliest Deadline First Schedule Execution:
Time 0: Executing process 1 (Capacity: 25, Period: 50, Deadline: 50)
Time 0: Process 1 completed
Time 1: Executing process 2 (Capacity: 35, Period: 80, Deadline: 80)
Time 1: Process 2 completed
*/
