#include "../incs/diff_eq.h"

extern double g_kappa;

double euler_explicit(double dt, double dx, double time, double *l_2, double *l_inf, FILE *fp_dist)
{
	int t_steps = round(time / dt);
	int x_steps = round(M_PI / dx);
	double r = g_kappa * dt / (dx * dx);

	double **u = (double **)calloc(t_steps + 1, sizeof(double *));
	if (!u)
		exit(1);
	for (int i = 0; i <= t_steps; i++)
	{
		u[i] = (double *)calloc(x_steps + 1, sizeof(double));
		if (!u[i])
			exit(1);
	}

	init_u(u, x_steps, dx, t_steps);

	for (int k = 0; k < t_steps; k++)
	{
		for (int i = 1; i < x_steps; i++)
			u[k + 1][i] = u[k][i] + r * (u[k][i + 1] - 2.0 * u[k][i] + u[k][i - 1]);
	}

	if (fp_dist)
	{
		for (int i = 0; i <= x_steps; i++)
			fprintf(fp_dist, "%e %e %e\n", i * dx, u[t_steps][i], exact(time, i * dx));
		fprintf(fp_dist, "\n\n");
	}

	calc_diff(u, l_2, l_inf, t_steps, x_steps, dt, dx);
	free_index(u, t_steps);
	return 0.0;
}
