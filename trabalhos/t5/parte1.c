#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

#define WORKSIZE 1000000
#define REPETITIONS 2000

long wtime(){

   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec*1000000 + t.tv_usec;
}

int main(int argc, char **argv) {

   int pid, np = 4, tag = 0;
   MPI_Status status;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &pid);
   MPI_Comm_size(MPI_COMM_WORLD, &np);

   int wsize = (argc == 3) ? atoi(argv[1]) : WORKSIZE;
   int repeat = (argc == 3) ? atoi(argv[2]) : REPETITIONS;

   // cria e preenche vetores
   int i, k, size = wsize*np;
   double* a = (double*)malloc(wsize*np*sizeof(double));
   for (i = 0; i < size; i++)
      a[i] = 1;
   double* b = (double*)malloc(wsize*np*sizeof(double));
   for (i = 0; i < size; i++)
      b[i] = 1.0;

   // calcula produto escalar
   long start_time = wtime();
   double mysum;
   int start = pid * wsize;
   int end = start + wsize;
   for (k = 0; k < repeat; k++) {
      mysum = 0.0;
      for (i = start; i < end ; i++) {
         mysum += (a[i] * b[i]);
      }
   }

   if (pid == 0) {
      int source;
      double sum, totalsum = mysum;

      for (source = 1; source < np; source++) {
         MPI_Recv(&sum, 1, MPI_DOUBLE, source, 0, MPI_COMM_WORLD, &status);
         totalsum += sum;
      }

      long end_time = wtime();
      printf("%f\n", totalsum);
      printf("%d process(es), %ld usec\n", np, (long)(end_time - start_time));
   } else {
      MPI_Send(&mysum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
   }

   free(a);
   free(b);

   MPI_Finalize();

   return 0;
}
