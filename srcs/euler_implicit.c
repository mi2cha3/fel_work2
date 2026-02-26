#include "../incs/diff_eq.h"

extern double g_kappa;

double euler_implicit(double dt, double dx, double time, double *l_2, double *l_inf, FILE *fp_dist)
{
	int t_steps = round(time / dt);
	int x_steps = round(M_PI / dx);
	double r = g_kappa * dt / (dx * dx);
	double rho = (2.0 * r / (1.0 + 2.0 * r)) * cos(M_PI / x_steps);
	double omega = 2.0 / (1.0 + sqrt(1.0 - rho * rho));

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
			u[k + 1][i] = u[k][i];

		int iter = 0;
		double max_error = 1.0;
		double tolerance = 1e-6;

		while (max_error > tolerance && iter < 10000)
		{
			max_error = 0.0;

			for (int i = 1; i < x_steps; i++)
			{
				double old_val = u[k + 1][i];

			// ガウス・ザイデルの仮更新値
				double u_star = (u[k][i] + r * u[k + 1][i - 1] + r * u[k + 1][i + 1]) / (1.0 + 2.0 * r);

			// SOR法による実際の更新
				u[k + 1][i] = (1.0 - omega) * old_val + omega * u_star;

				double current_error = fabs(u[k + 1][i] - old_val);
				if (current_error > max_error)
					max_error = current_error;
			}
			iter++;
		}
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
