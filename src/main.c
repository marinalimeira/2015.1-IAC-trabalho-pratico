#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
  printf("hey");

  struct rusage *rusage;
  int pid = fork();

  if (pid < 0){
    //não funfou
    printf("error");
  } else if (pid > 0) {
    // tá no processo pai, tem que medir as coisas
    // daqui a cada seg
    getrusage(pid, rusage);
    printf("%ld", rusage->ru_maxrss);
    //printar a cada dez segudos 
    // fora do loop medir o negocio
    /* printf("%ld", rusage->ru_utime.tv_sec); */
  } else {
    // tá no processo filho
    if (strcmp(argv[1], "cpu") == 0) {
      //uso de cpu
      for (;;) {}
    } else if (strcmp(argv[1], "cpu-mem") == 0) {
      //uso de cpu + memória
      for (;;) {
        malloc(sizeof(1));
      }
    }
     /* rusage.ru_mxrss //memoria
     *       .ru_utime.tv_sec //cpu
     *long   ru_maxrss;
       struct timeval ru_utime; user CPU time used*/
  }
}
