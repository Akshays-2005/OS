#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

struct Process {
    int cap, per, pno;
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

void sortonprio(int n, pro* p[]) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(p[j]->per > p[j+1]->per) {
                pro* temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}


void RMS(pro* p[], int n) {
    sortonprio(n, p);
    float utilization = 0;
    for (int i = 0; i < n; i++) {
        utilization += (float)p[i]->cap / p[i]->per;
    }
    float bound = n * (pow(2, 1.0/n) - 1);
    if (utilization > bound) {
        printf("Warning: Schedule may not be feasible (Utilization: %.2f, Bound: %.2f)\n",
               utilization, bound);
            return;
    }
    printf("\nRate Monotonic Schedule Execution:\n");
    for (int i = 0; i < n; i++) {
        enqueue(p[i]->pno);
        printf("Time %d: Executing process %d (Capacity: %d, Period: %d)\n",
               i, p[i]->pno, p[i]->cap, p[i]->per);
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

        printf("Enter process %d number: ", i+1);
        scanf("%d", &p[i]->pno);
        printf("Enter capacity: ");
        scanf("%d", &p[i]->cap);
        printf("Enter period: ");
        scanf("%d", &p[i]->per);
    }

    RMS(p, num);  // Call to RMS function

    // Cleanup
    for (int i = 0; i < num; i++) {
        free(p[i]);
    }
    return 0;
}

/* Output:
Enter the number of processes: 3
Enter process 1 number: 1
Enter capacity: 2
Enter period: 5
Enter process 2 number: 2
Enter capacity: 3
Enter period: 10
Enter process 3 number: 3
Enter capacity: 1
Enter period: 20

Rate Monotonic Schedule Execution:
Time 0: Executing process 1 (Capacity: 2, Period: 5)
Time 0: Process 1 completed
Time 1: Executing process 2 (Capacity: 3, Period: 10)
Time 1: Process 2 completed
Time 2: Executing process 3 (Capacity: 1, Period: 20)
Time 2: Process 3 completed
*/
