#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int n = 20; // Número de elementos da sequência
int fib[21]; // Array para armazenar a sequência (n+1 elementos)


void *calcFib(void *arg) {
    fib[0] = 0;
    if (n > 0) fib[1] = 1;

    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;

    printf("Criando thread para calcular Fibonacci...\n");


    int status = pthread_create(&thread, NULL, calcFib, NULL);
    if (status != 0) {
        printf("Erro ao criar thread. Código %d\n", status);
        return 1;
    }


    pthread_join(thread, NULL);


    printf("Sequência de Fibonacci (primeiros %d termos):\n", n);
    for (int i = 0; i <= n; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");

    return 0;
}