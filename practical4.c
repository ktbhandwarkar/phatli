#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t room;
sem_t fork[5];

void *philosopher(void *n)
{
    int id = *(int *)n;

    printf("Philosopher %d is thinking\n", id);

    sem_wait(&room);

    sem_wait(&fork[id]);
    sem_wait(&fork[(id + 1) % 5]);

    printf("Philosopher %d is eating\n", id);
    sleep(1);

    sem_post(&fork[id]);
    sem_post(&fork[(id + 1) % 5]);

    sem_post(&room);

    printf("Philosopher %d finished eating\n", id);

    return NULL;
}

int main()
{
    pthread_t t[5];
    int id[5];
    int i;

    sem_init(&room, 0, 4);

    for(i = 0; i < 5; i++)
    {
        sem_init(&fork[i], 0, 1);
    }

    for(i = 0; i < 5; i++)
    {
        id[i] = i;
        pthread_create(&t[i], NULL, philosopher, &id[i]);
    }

    for(i = 0; i < 5; i++)
    {
        pthread_join(t[i], NULL);
    }

    sem_destroy(&room);

    for(i = 0; i < 5; i++)
    {
        sem_destroy(&fork[i]);
    }

    return 0;
}