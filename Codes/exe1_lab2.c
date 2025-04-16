#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    
    int segment_id = shmget(IPC_PRIVATE, sizeof(int), S_IRUSR | S_IWUSR);
    
    int *shared_memory = (int *)shmat(segment_id, NULL, 0);
    *shared_memory = 0; 

    for (int i = 0; i < 2; i++) {
        pid_t pid = fork();
        
        if (pid < 0) {
            printf("Erro ao criar processo filho\n");
            return 1;
        } else if (pid == 0) { 
            *shared_memory += 100;
            printf("Filho %d alterou o valor para: %d\n", getpid(), *shared_memory);
           
            shmdt(shared_memory);
            exit(0);
        }
    }

    wait(NULL);
    wait(NULL);
    
    printf("Valor final na memória compartilhada: %d\n", *shared_memory);
    
    
    shmdt(shared_memory);
    shmctl(segment_id, IPC_RMID, NULL);
    
    return 0;
}
