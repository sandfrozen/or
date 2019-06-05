/* C Example */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define LIMIT_ODBIC 100000000 // 10 mln

int main(int argc, char *argv[])
{
  int id, p;
  long numer_odbicia = 0, limit = LIMIT_ODBIC;
  if( argc == 2) {
     limit = atol(argv[1]);
  }
  double t_start, t_stop;
  double t_w_start, t_w_stop;
  MPI_Status status; // status powrotu z funkcji recieve

  MPI_Init(&argc, &argv);             // inicjowanie MPI
  t_start = MPI_Wtime();
  // t_w_start = MPI_Wtick();
  MPI_Comm_rank(MPI_COMM_WORLD, &id); // zwrocenie numer procesu
  MPI_Comm_size(MPI_COMM_WORLD, &p);  // zwrocenie liczby procesow
  printf("Proces %d Start %ld\n", id, limit);

  while (numer_odbicia < limit)
  {
    if (id == 0)
    {
      numer_odbicia++;
      MPI_Send(&numer_odbicia, 1, MPI_LONG, 1, 0, MPI_COMM_WORLD);
      // printf("Wyslano z 0 number odbicia: %d\n", numer_odbicia);
      MPI_Recv(&numer_odbicia, 1, MPI_LONG, 1, 0, MPI_COMM_WORLD, &status);

    }
    else
    {
      MPI_Recv(&numer_odbicia, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD, &status);
      numer_odbicia++;
      MPI_Send(&numer_odbicia, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD);
      // printf("Wyslano z 1 number odbicia: %d\n", numer_odbicia);
    }
  }
  t_stop = MPI_Wtime();
  // t_w_stop = MPI_Wtick();
  printf("Proces %d number odbicia: %ld. Czas start: %f  - Czas stop: %f = %f\n", id, numer_odbicia, t_start, t_stop, t_stop-t_start);
  // printf("Proces %d MPIWtick: %f\n", id, t_w_stop);
  MPI_Finalize();
  return 0;
}