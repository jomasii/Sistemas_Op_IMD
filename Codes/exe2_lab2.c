#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>

int n = 20;

int main(int argc, char **argv) {
    int segment_id = shmget(IPC_PRIVATE, (n+1)*sizeof(int), S_IRUSR | S_IWUSR);
    int *fib = (int *)shmat(segment_id, NULL, 0);

    pid_t pid = fork();
    
    if (pid < 0) {
        printf("Erro ao criar processo filho\n");
        return 1;
    } else if (pid == 0) { 
        fib[0] = 0;
        if (n > 0) fib[1] = 1;
        
        for (int i = 2; i <= n; i++) {
            fib[i] = fib[i-1] + fib[i-2];
        }
        
        shmdt(fib);
        exit(0);
    } else { // Processo pai
        wait(NULL);
        
        printf("Sequência de Fibonacci (primeiros %d termos):\n", n);
        for (int i = 0; i <= n; i++) {
            printf("%d ", fib[i]);
        }
        printf("\n");
        
        // Limpeza
        shmdt(fib);
        shmctl(segment_id, IPC_RMID, NULL);
    }
    
    return 0;
}
