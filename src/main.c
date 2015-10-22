#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[], char *envp[]) {

  /* struct rusage rusage; */
  int pid = fork();
  int i;
  double count_time;
  double seconds;
  clock_t hour, second_last;
  char cmd[50];

  if (pid < 0){
    perror ("Error: ");
  } else if (pid > 0) {
    sprintf(cmd, "ps -p %d -o %%cpu,rss | tee -a result.txt", pid);
    system(cmd);
    for (i = 1; i <= 10; i++){
      second_last = clock();
      do {
        hour = clock();
        seconds = (hour - second_last) / (double)CLOCKS_PER_SEC;
      } while(seconds < 1);

      sprintf(cmd, "ps -p %d -o %%cpu,rss | tee -a result.txt", pid);
      system(cmd);
    }
    //gerar novos gráficos 
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
  }

  return 0;
}
