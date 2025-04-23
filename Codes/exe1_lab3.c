#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>

int numberOfThreads=5;

void *printHello(void *tid){
  printf("Ola, eu sou a thread %d.\n", (int)(size_t) tid);
  pthread_exit(NULL);
}

int main(int argc, char **argv)
{
  pthread_t threads[numberOfThreads];
  for (int i=0;i<numberOfThreads;i++){
    // Criando uma thread e passando para ela a funcao printHello
    int status=pthread_create(&threads[i],NULL,printHello,(void *)(size_t) i);

    if(status!=0){
      printf("Erro na criacao da thread %d. Codigo de erro %d.",i, status);
      return 1;
    }

    // pthread_join(threads[i],NULL);
  }

  // Adicionada esta linha para substituir o pthread_join
  pthread_exit(NULL);

  return 0;
}