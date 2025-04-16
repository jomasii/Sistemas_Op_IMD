#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int v=100;
void filho_incrementa(int *v){// Filho incrementa v usando ponteiros
  *v =*v +100;
}
int main(int argc, char **argv)
{
    pid_t pid=fork(); // Funcao usada para criar um novo processo
    if(pid==0){// Processo filho
      filho_incrementa(&v); // Filho incrementa v usando ponteiros
      printf("Sou o processo filho. v = %d.\n",v);
      exit(0); 
    }else if(pid>0){ // Processo pai
      wait(NULL); 
    }
    printf("Sou o processo pai. v = %d.\n",v);
    return 0;
}