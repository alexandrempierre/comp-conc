/* File:     mpi_trap2.c
 * Purpose:  Use MPI to implement a parallel version of the trapezoidal
 *           rule.  This version accepts input of the endpoints of the
 *           interval and the number of trapezoids.
 *
 * Input:    The endpoints of the interval of integration and the number
 *           of trapezoids
 * Output:   Estimate of the integral from a to b of f(x)
 *           using the trapezoidal rule and n trapezoids.
 *
 * Compile:  mpicc -o mpi_trap mpi_trap.c
 * Run:      mpirun -np <number of processes> ./mpi_trap
 *
 * Algorithm:
 *    1.  Each process calculates "its" interval of
 *        integration.
 *    2.  Each process estimates the integral of f(x)
 *        over its interval using the trapezoidal rule.
 *    3a. Each process != 0 sends its integral to 0.
 *    3b. Process 0 sums the calculations received from
 *        the individual processes and prints the result.
 *
 * Note:  f(x) is all hardwired.
 *
 * IPP:   Section 3.3.2  (pp. 100 and ff.)
 */
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include <mpi.h>

/* Calculate local integral  */
double Trap(double left_endpt, double right_endpt, int trap_count,
   double base_len);

/* Function we're integrating */
double f(double x);

int main(int argc, char* argv[]) {
   int my_rank, comm_sz, n, local_n, ret;
   double a, b, h, local_a, local_b;
   double local_int, total_int;
   int source;
   double begin, end;

   if(argc<4) {
      printf("Digite: %s <inicio do intervalo> <final do intervalo> <numero de trapezios>\n", argv[0]);
      return 1;
   }

   ret = MPI_Init(&argc, &argv);
   if (ret == MPI_SUCCESS){
     MPI_Comm_size (MPI_COMM_WORLD, &comm_sz);
     MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
     printf ("Sou o processo %d de %d\n", my_rank, comm_sz);
   } else return 1;

   a = atoi(argv[1]);
   b = atoi(argv[2]);
   n = atoi(argv[3]);

   GET_TIME(begin);
   h = (b-a)/n;          /* h is the same for all processes */
   local_n = n/comm_sz;  /* So is the number of trapezoids  */

   /* Length of each process' interval of
    * integration = local_n*h.  So my interval
    * starts at: */
   local_a = a + my_rank*local_n*h;
   local_b = local_a + local_n*h;

   local_int = Trap(local_a, local_b, local_n, h);

   /* Add up the integrals calculated by each process */
   if (my_rank != 0) {
//!!!...completar (enviar resultado para o processo 0)!!!
    MPI_Send(local_int, 1, MPI_DOUBLE, 0, 99, MPI_COMM_WORLD);
   } else {
      total_int = local_int;
      for (source = 1; source < comm_sz; source++) {
//!!!...completar (receber resultado dos demais processos)!!!
          MPI_Send(local_int, 1, MPI_DOUBLE, 0, 99, MPI_COMM_WORLD);
          total_int += local_int;
      }
   }
   GET_TIME(end);

   /* Print the result */
   if (my_rank == 0) {
      printf("Valor estimado da integral de %.1f a %.1f = %.15f\n", a, b, total_int);
      printf("Tempo: %.5f\n", end - begin);
   }

   MPI_Finalize();

   return 0;
} /*  main  */


/*------------------------------------------------------------------
 * Function:     Trap
 * Purpose:      Serial function for estimating a definite integral
 *               using the trapezoidal rule
 * Input args:   left_endpt
 *               right_endpt
 *               trap_count
 *               base_len
 * Return val:   Trapezoidal rule estimate of integral from
 *               left_endpt to right_endpt using trap_count
 *               trapezoids
 */
double Trap(
      double left_endpt  /* in */,
      double right_endpt /* in */,
      int    trap_count  /* in */,
      double base_len    /* in */) {
   double estimate, x;
   int i;

   estimate = (f(left_endpt) + f(right_endpt))/2.0;
   for (i = 1; i <= trap_count-1; i++) {
      x = left_endpt + i*base_len;
      estimate += f(x);
   }
   estimate = estimate*base_len;

   return estimate;
} /*  Trap  */


/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 * Input args:  x
 */
double f(double x) {
   return x*x;
} /* f */
