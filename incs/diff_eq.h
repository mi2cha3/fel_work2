
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef DIFF_EQ
#define DIFF_EQ
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void	init_u(double **u, int x_steps, double dx, int t_steps);
double exact(double t, double x);
void	calc_diff(double **u, double *l_2, double *l_inf, int t_steps, int x_steps, double dt, double dx);
void	free_index(double **u, int t_steps);



double euler_explicit(double dt, double dx, double time, double *l_2, double *l_inf, FILE *fp_dist);
double euler_implicit(double dt, double dx, double time, double *l_2, double *l_inf, FILE *fp_dist);
double crank_nicolson(double dt, double dx, double time, double *l_2, double *l_inf, FILE *fp_dist);

#endif