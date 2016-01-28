/* File:    trap.c
 * Purpose: Calculate definite integral using trapezoidal 
 *          rule.
 *
 * Input:   a, b, n
 * Output:  Estimate of integral from a to b of f(x)
 *          using n trapezoids.
 *
 * Compile: gcc -o trap trap.c
 * Usage:   ./trap
 *
 * Note:    The function f(x) is hardwired.
 *
 * IPP:     Section 3.2.1 (pp. 94 and ff.) and 5.2 (p. 216)
 */

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

double f(double x);    /* Function we're integrating */
double Trap(double a, double b, int n, double h);

int main(int argc, char* argv[]) {
   double  integral;   /* Store result in integral   */
   double  a, b;       /* Left and right endpoints   */
   int     n;          /* Number of trapezoids       */
   double  h;          /* Height of trapezoids       */
   double begin, end;

   if(argc<4) {
      printf("Digite: %s <inicio do intervalo> <final do intervalo> <numero de trapezios>\n", argv[0]);
      return 1;
   }

   a = atoi(argv[1]);
   b = atoi(argv[2]);
   n = atoi(argv[3]);

   GET_TIME(begin);
   h = (b-a)/n;
   integral = Trap(a, b, n, h);
   GET_TIME(end);
   
   printf("Valor estimado da integral de %.1f a %.1f = %.15f\n", a, b, integral);
   printf("Tempo: %.5f\n", end - begin);

   return 0;
}  /* main */

/*------------------------------------------------------------------
 * Function:    Trap
 * Purpose:     Estimate integral from a to b of f using trap rule and
 *              n trapezoids
 * Input args:  a, b, n, h
 * Return val:  Estimate of the integral 
 */
double Trap(double a, double b, int n, double h) {
   double integral;
   int k;

   integral = (f(a) + f(b))/2.0;
   for (k = 1; k <= n-1; k++) {
     integral += f(a+k*h);
   }
   integral = integral*h;

   return integral;
}  /* Trap */

/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 * Input args:  x
 */
double f(double x) {
   double return_val;

   return_val = x*x;
   return return_val;
}  /* f */
