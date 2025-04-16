#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>

int n = 10;

int main(int argc, char **argv) {
    
    int segment_id = shmget(IPC_PRIVATE, sizeof(int), S_IRUSR | S_IWUSR);
    int *result = (int *)shmat(segment_id, NULL, 0);
    *result = 0;

    for (int i = 0; i <= n; i++) {
        pid_t pid = fork();
        
        if (pid < 0) {
            printf("Erro ao criar processo\n");
            return 1;
        } else if (pid == 0) {
            *result += i;
            printf("Processo %d: somou %d, resultado parcial = %d\n", getpid(), i, *result);
            
            shmdt(result);
            exit(0);
        } else {
            wait(NULL);
        }
    }

    printf("Soma dos primeiros %d números naturais: %d\n", n, *result);
    
    shmdt(result);
    shmctl(segment_id, IPC_RMID, NULL);
    
    return 0;
}