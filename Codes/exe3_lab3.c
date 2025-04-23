#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int n = 10; // Soma dos primeiros n números naturais
int result = 0; // Variável para armazenar o resultado


typedef struct {
    int number;
} ThreadArgs;


void *addNumber(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    result += args->number;
    printf("Thread %ld: somou %d, resultado parcial = %d\n",
           pthread_self(), args->number, result);
    free(args);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[n+1];

    for (int i = 0; i <= n; i++) {

        ThreadArgs *args = malloc(sizeof(ThreadArgs));
        args->number = i;

   
        int status = pthread_create(&threads[i], NULL, addNumber, (void *)args);
        if (status != 0) {
            printf("Erro ao criar thread. Código %d\n", status);
            return 1;
        }

        pthread_join(threads[i], NULL);
    }

    printf("Soma dos primeiros %d números naturais: %d\n", n, result);

    return 0;
}