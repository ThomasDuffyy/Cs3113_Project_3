#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // For sleep

#define BUFFER_SIZE 15
#define FILENAME "mytest.dat"

char buffer[BUFFER_SIZE];
int in = 0, out = 0; // Buffer pointers

sem_t empty; // Tracks empty slots
sem_t full;  // Tracks filled slots
sem_t mutex; // Mutual exclusion for buffer

void* producer(void* arg) {
    FILE* file = fopen(FILENAME, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        sem_wait(&empty); // Wait for an empty slot
        sem_wait(&mutex); // Enter critical section

        buffer[in] = ch;
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex); // Exit critical section
        sem_post(&full);  // Signal a filled slot
    }

    // Place end marker
    sem_wait(&empty);
    sem_wait(&mutex);

    buffer[in] = '*'; // Special end marker
    in = (in + 1) % BUFFER_SIZE;

    sem_post(&mutex);
    sem_post(&full);

    fclose(file); // Close the file after reading
    return NULL;
}

void* consumer(void* arg) {
    char ch;
    do {
        sem_wait(&full);  // Wait for a filled slot
        sem_wait(&mutex); // Enter critical section

        ch = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutex); // Exit critical section
        sem_post(&empty); // Signal an empty slot

        putchar(ch);
        fflush(stdout);
        sleep(1); // Simulate slower consumer
    } while (ch != '*');

    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // BUFFER_SIZE slots initially empty
    sem_init(&full, 0, 0);            // No slots are full initially
    sem_init(&mutex, 0, 1);           // Binary semaphore for mutual exclusion

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for threads to complete
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    printf("\nAll done!\n");
    return 0;
}
