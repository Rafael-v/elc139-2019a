#include <stdio.h>
#include "mpi.h"

#define NUMERO_INICIAL 1000

int main(int argc, char **argv) {

   int pid, np, tag = 0;
   int source, dest;
   MPI_Status status;
   int num;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &pid);
   MPI_Comm_size(MPI_COMM_WORLD, &np);

   source = pid - 1;
   dest = pid + 1;

   if (pid == 0) {
      num = NUMERO_INICIAL;
      printf("Numero inicial: %d\n\n", num);
      num++;
      MPI_Send(&num, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
      printf("[pid %d] Numero enviado para o processo %d: %d\n", pid, dest, num);
   } else if (pid == np-1) {
      MPI_Recv(&num, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &status);
      printf("[pid %d] Numero recebido do processo %d: %d\n", pid, source, num);
      printf("\nResultado: %d\n", num);
   } else {
      MPI_Recv(&num, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &status);
      printf("[pid %d] Numero recebido do processo %d: %d\n", pid, source, num);
      num++;
      MPI_Send(&num, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
      printf("[pid %d] Numero enviado para o processo %d: %d\n", pid, dest, num);
   }

   MPI_Finalize();

   return 0;
}
