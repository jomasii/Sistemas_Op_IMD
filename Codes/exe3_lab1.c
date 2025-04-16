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
    pid_t pid_filho=fork(); // Funcao usada para criar um novo processo
    
    if(pid_filho==0){// Processo filho
      filho_incrementa(&v);
      pid_t pid_neto=fork();// Crio um novo filho
      
      if(pid_neto==0){ // Processo neto
        filho_incrementa(&v);
        printf("Sou o processo neto. v = %d.\n",v);
      }
      
      else if(pid_neto>0){ // Processo filho
        wait(NULL); 
        printf("Sou o processo filho. v = %d.\n",v);
      }
      exit(0); 
    }
    
    else if(pid_filho>0){ 
      wait(NULL); 
    }
    
    printf("Sou o processo pai. v = %d.\n",v);
    return 0;
}