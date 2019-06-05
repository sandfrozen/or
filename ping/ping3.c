/* C Example */
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

  MPI_Init(&argc, &argv);             // inicjowanie MPI
  t_start = MPI_Wtime();
  MPI_Comm_rank(MPI_COMM_WORLD, &id); // zwrocenie numer procesu
  MPI_Comm_size(MPI_COMM_WORLD, &p);  // zwrocenie liczby procesow
  printf("Proces %d Start %ld\n", id, limit);
  
  while (numer_odbicia < limit)
  {
    if (id == 0)
    {
      MPI_Request reqtab[2];
      MPI_Status stattab[2];
      numer_odbicia++;
      MPI_Isend(&numer_odbicia, 1, MPI_LONG, 1, 0, MPI_COMM_WORLD, &reqtab[0]);
      MPI_Irecv(&numer_odbicia, 1, MPI_LONG, 1, 0, MPI_COMM_WORLD, &stattab[1]);
      MPI_Waitall(2, reqtab, stattab);
    }
    else
    {
      MPI_Request reqtab[2];
      MPI_Status stattab[2];
      MPI_Irecv(&numer_odbicia, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD, &reqtab[0]);
      numer_odbicia++;
      MPI_Isend(&numer_odbicia, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD, &stattab[1]);
      MPI_Waitall(2, reqtab, stattab);
    }
  }
  t_stop = MPI_Wtime();
  printf("Proces %d number odbicia: %ld. Czas: %f\n", id, numer_odbicia, t_stop);
  MPI_Finalize();
  return 0;
}