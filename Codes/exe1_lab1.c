#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("Sou o processo %d, sou o pai de todos.\n",getpid());
    fork();
    fork();
    fork();
    fork();
    while(1){
      pid_t pid=wait(NULL); 
      
      if(pid==-1){ 
        printf("Sou o processo %d, serei encerrado agora.\n",getpid());
        exit(0);
      }
      
      else{
        printf("Sou o processo %d, meu filho %d terminou a sua execucao.\n",getpid(),pid);
      }
    }

    return 0;
}
