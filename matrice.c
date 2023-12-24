#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define Thread 10
#define N 10

int n1, m1, n2, m2;
int tompon[N];
int count = 0;

pthread_mutex_t mutex;
sem_t semFull, semEmpty;

int B[N][N]; 
int A[N][N]; 
int C[N][N];

void *producer(void *args)
{
    int row = *(int *)args;
    int somme;

    for (int col = 0; col < m2; col++)
    {
        
        somme = 0;
        for (int i = 0; i < m1; i++)
        {
            somme += B[row][i] * A[i][col];
        }

       
        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutex);
        tompon[count] = somme;
        count++;
        pthread_mutex_unlock(&mutex);
        sem_post(&semFull);
    }

    free(args);
    pthread_exit(NULL);
}

void *consumer(void *args)
{
    int col = *(int *)args;
    int result;

    for (int row = 0; row < n1; row++)
    {
      
        sem_wait(&semFull);
        pthread_mutex_lock(&mutex);
        count--;
        result = tompon[count];
        pthread_mutex_unlock(&mutex);
        sem_post(&semEmpty);

     
        C[row][col] = result;
    }

    free(args);
    pthread_exit(NULL);
}

int main()
{
    
    n1 = m1 = n2 = m2 = 4; 

    
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            B[i][j] = rand() % 100;
        }
    }

    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            A[i][j] = rand() % 100; 
        }
    }

    pthread_t producers[Thread], consumers[Thread];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&semFull, 0, 0);
    sem_init(&semEmpty, 0, N);

   
    printf("La Matrice A:\n");
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("La Matrice B:\n");
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

  
    for (int i = 0; i < n1; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        pthread_create(&producers[i], NULL, producer, (void *)a);
    }


    for (int i = 0; i < m2; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        pthread_create(&consumers[i], NULL, consumer, (void *)a);
    }


    for (int i = 0; i < n1; i++)
    {
        pthread_join(producers[i], NULL);
    }


    for (int i = 0; i < m2; i++)
    {
        pthread_join(consumers[i], NULL);
    }


    printf("La Matrice C:\n");
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&semFull);
    sem_destroy(&semEmpty);

    return 0;
}

