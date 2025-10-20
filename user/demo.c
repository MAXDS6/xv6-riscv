#include "kernel/types.h"
#include "user/user.h"

#define N_CHILDREN 10

int main() {
  int i;
  int pid;

  printf("Iniciando prueba de Lottery Scheduling con %d procesos...\n", N_CHILDREN);

  for (i = 0; i < N_CHILDREN; i++) {
    pid = fork();
    if (pid == 0) { // Proceso hijo
      int tickets = 50 * (i + 1);
      settickets(tickets);

      // Bucle de trabajo intensivo para consumir CPU
      volatile unsigned long long counter = 0;
      while (counter < 1000000000) {
        counter++;
      }

      printf("Hijo %d (pid %d) con %d tickets terminó.\n", i + 1, getpid(), tickets);
      exit(0);
    }
  }

  // El padre espera a que todos los hijos terminen
  for (i = 0; i < N_CHILDREN; i++) {
    wait(0);
  }

  printf("Prueba completada. Presiona Ctrl+P para ver el estado de los procesos.\n");
  exit(0);
}
