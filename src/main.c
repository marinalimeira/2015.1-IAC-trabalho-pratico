#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[], char *envp[]) {

  struct rusage rusage;
  int pid = fork();
  int i;
  double seconds;
  clock_t hour, hour_last;

  if (pid < 0){
    perror ("Error: ");
  } else if (pid > 0) {
    for (i = 0; i < 10; i++){
      if (i != 1){
        do{
          hour = clock();
          seconds = (hour - hour_last) / (double)CLOCKS_PER_SEC;
        } while(seconds < 1);
      hour_last = hour;
      }
      else{
        hour_last = clock();
      }
      getrusage(pid, &rusage);
      printf("Uso da Memória: %ld\n", rusage.ru_maxrss);
    /* by Lage:
     * guarde a cada segundo o consumo de memória (em Kilobytes) e
     * CPU (em porcentagem) do processo filho
     * após 10 segundos de execução, mate o proceso filho*/
      printf("Uso de algo: %ld\n", rusage.ru_stime.tv_sec);
    }

    kill(pid, SIGKILL);
  } else {
    // tá no processo filho
    if (strcmp(argv[1], "cpu") == 0) {
      for (;;) {} //uso de cpu
    } else if (strcmp(argv[1], "cpu-mem") == 0) {
      for (;;) { //uso de cpu + memória
        malloc(sizeof(1));
      }
    }
     /* rusage.ru_mxrss //memoria
     *       .ru_utime.tv_sec //cpu
     *long   ru_maxrss;
       struct timeval ru_utime; user CPU time used*/
  }

  return 0;
}
