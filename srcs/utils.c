#include "../incs/diff_eq.h"

extern double g_kappa;

void	init_u(double **u, int x_steps, double dx, int t_steps)
{
	for (int i = 0; i <= x_steps; i++)
		u[0][i] = sin(i * dx);
	for (int n = 0; n <= t_steps; n++)
	{
		u[n][0] = 0.0;
		u[n][x_steps] = 0.0;
	}
}

double exact(double t, double x)
{
	return (exp(-g_kappa * t) * sin(x));
}

void	calc_diff(double **u, double *l_2, double *l_inf, int t_steps, int x_steps, double dt, double dx)
{
	double diff = 0.0;

		for (int i = 0; i<=x_steps; i++)
		{
			diff = u[t_steps][i] - exact(t_steps * dt, i * dx);
			if (fabs(diff) > *l_inf)
				*l_inf = fabs(diff);
			*l_2 += diff * diff * dx;
		}
	*l_2 = sqrt(*l_2);
}



void	free_index(double **u, int t_steps)
{
	for (int i = 0; i<=t_steps; i++)
	{
		free(u[i]);
	}
	free(u);
}

