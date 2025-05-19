#include <stdio.h>
#include <stdlib.h>
#define MAX_TASKS 10
typedef struct
{
    int id;
    int period;
    int execution_time;
    int remaining_time;
} Task;
int compare_tasks(const void *a, const void *b)
{
    Task *t1 = (Task *)a;
    Task *t2 = (Task *)b;
    return t1->period - t2->period;
}
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int lcm(int a, int b)
{
    return (a * b) / gcd(a, b);
}
void execute_task(Task *task, int time)
{
    printf("Time %3d: Executing Task %d\n", time, task->id);
    task->remaining_time--;
}
int main(void)
{
    int n;
    printf("Enter number of tasks: ");
    scanf("%d", &n);
    if (n > MAX_TASKS)
    {
        printf("Number of tasks exceeds maximum (%d).\n", MAX_TASKS);
        return 1;
    }
    Task tasks[MAX_TASKS];
    for (int i = 0; i < n; i++)
    {
        printf("Enter Task %d (id period execution_time): ", i + 1);
        scanf("%d %d %d", &tasks[i].id, &tasks[i].period, &tasks[i].execution_time);
        tasks[i].remaining_time = tasks[i].execution_time;
    }
    qsort(tasks, n, sizeof(Task), compare_tasks);
    int hyperperiod = tasks[0].period;
    for (int i = 1; i < n; i++)
    {
        hyperperiod = lcm(hyperperiod, tasks[i].period);
    }
    printf("\nHyperperiod = %d time units\n\n", hyperperiod);
    for (int time = 0; time < hyperperiod; time++)
    {
        for (int i = 0; i < n; i++)
        {
            if (time % tasks[i].period == 0)
            {
                tasks[i].remaining_time = tasks[i].execution_time;
            }
        }
        Task *current_task = NULL;
        for (int i = 0; i < n; i++)
        {
            if (tasks[i].remaining_time > 0)
            {
                current_task = &tasks[i];
                break;
            }
        }
        if (current_task != NULL)
        {
            execute_task(current_task, time);
        }
        else
        {
            printf("Time %3d: Idle\n", time);
        }
    }
    return 0;
}
