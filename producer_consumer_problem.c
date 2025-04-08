#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;
int item = 0;
sem_t empty, full;
pthread_mutex_t mutex;

void *producer() {
    if (count == BUFFER_SIZE) {
        printf("Buffer is full!\n");
        return NULL;
    }

    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    buffer[count] = ++item;
    printf("Producer has produced: Item %d\n", item);
    count++;

    pthread_mutex_unlock(&mutex);
    sem_post(&full);

    return NULL;
}

void *consumer() {
    if (count == 0) {
        printf("Buffer is empty!\n");
        return NULL;
    }

    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    int consumedItem = buffer[count - 1];
    printf("Consumer has consumed: Item %d\n", consumedItem);
    count--;

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);

    return NULL;
}

int main() {
    int choice;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    while (1) {
        printf("\nEnter 1.Producer 2.Consumer 3.Exit\nEnter your choice: ");
        scanf("%d", &choice);

        pthread_t thread;
        switch(choice){
            case 1: pthread_create(&thread, NULL, (void *)producer, NULL);
                break;
            case 2: pthread_create(&thread, NULL, (void *)consumer, NULL);
                break;
            case 3: exit(0);
                break;
            default: printf("Invalid choice! Try again.\n");
                break;
        }
        pthread_join(thread, NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
