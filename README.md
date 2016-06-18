# Randomized-Incremental-Algorithm
###Solving Linear Equation
Implement the randomized incremental algorithm to compute the maximum of a linear
objective function of four variables under a set of linear inequalities.
You should write a function

```sh
int rand_lp(int n, double *A, double *b, double *c, double *result)
```

which has as parameters the number of inequalities n, the coefficient matrix A and
right-hand side b, the coefficients of the objective function c, as well as the result
vector result, which contains the optimum values for the four variables x0, . . . , x3.
It returns an integer, which is the number of recomputations at the top level taken
by the algorithm to reach the optimum.

Your function should solve the LP problem

```sh
max c[0]x0 + c[1]x1 + c[2]x2 + c[3]x3
A[0][0]x0 + · · · + A[0][3]x3 ≤ b[0]
A[1][0]x0 + · · · + A[1][3]x3 ≤ b[1]
.
.
.
A[n − 1][0]x0 + · · · + A[n − 1][3]x3 ≤ b[n − 1]
```

```sh
x0 ≥ 0, x1 ≥ 0, · · · , x3 ≥ 0
```

***The matrix is a 4 X n matrix with n fairly large, so do not make any assumptions
on the size of the matrix; any additional storage you need should be allocated dynamically.***


####Compilation
```sh
gcc rand_lp.c -o rand_lp.out"
./rand_lp.out
```
For segmentation fault use:
```sh
ulimit -s unlimited
```
***Takes different time to execute for every execution due to random permutation.***
