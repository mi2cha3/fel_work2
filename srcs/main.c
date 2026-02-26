// 支配方程式
// du/dt=κ d²(u)/dx² (0<x<π, t>0)
// 初期条件
// u(x,0)=sin⁡(x)
// 境界条件(両端0:ディリクレ条件)
// u(0,t)=0, u(π,t)=0

#include "../incs/diff_eq.h"

double g_kappa = 1.0;

void run_distribution(void)
{
	double time[] = {0.0, 0.1, 0.5, 1.0};
	double dt = 0.001;
	double dx = 0.1;
	int n = 4;
	FILE *fp_exp = fopen("dist_explicit.dat", "w");
	FILE *fp_imp = fopen("dist_implicit.dat", "w");
	FILE *fp_cn = fopen("dist_crank_nicolson.dat", "w");

	for (int i = 0; i < n; i++)
	{
		double l2_exp = 0.0, linf_exp = 0.0;
		double l2_imp = 0.0, linf_imp = 0.0;
		double l2_cn = 0.0, linf_cn = 0.0;
		euler_explicit(dt, dx, time[i], &l2_exp, &linf_exp, fp_exp);
		euler_implicit(dt, dx, time[i], &l2_imp, &linf_imp, fp_imp);
		crank_nicolson(dt, dx, time[i], &l2_cn, &linf_cn, fp_cn);
	}
	fclose(fp_exp);
	fclose(fp_imp);
	fclose(fp_cn);
}

void run_convergence_dx(void)
{
	double time = 1.0;
	double dt = 0.00001;
	double dx_list[] = {M_PI/10, M_PI/20, M_PI/40, M_PI/80};
	int n = 4;
	FILE *fp = fopen("conv_dx.dat", "w");

	for (int i = 0; i < n; i++)
	{
		double l2_exp = 0.0, linf_exp = 0.0;
		double l2_imp = 0.0, linf_imp = 0.0;
		double l2_cn = 0.0, linf_cn = 0.0;
		euler_explicit(dt, dx_list[i], time, &l2_exp, &linf_exp, NULL);
		euler_implicit(dt, dx_list[i], time, &l2_imp, &linf_imp, NULL);
		crank_nicolson(dt, dx_list[i], time, &l2_cn, &linf_cn, NULL);
		fprintf(fp, "%e %e %e %e %e %e %e\n", dx_list[i], l2_exp, linf_exp, l2_imp, linf_imp, l2_cn, linf_cn);
	}
	fclose(fp);
}

void run_convergence_dt(void)
{
	double time = 1.0;
	double dx = M_PI/100;
	double dt_list[] = {0.0004, 0.0002, 0.0001, 0.00005, 0.000025, 0.0000125}; // 陽解法の安定性条件(r<=0.5)を満たす範囲でdtを小さくする
	int n = 6;
	FILE *fp = fopen("conv_dt.dat", "w");

	for (int i = 0; i < n; i++)
	{
		double l2_exp = 0.0, linf_exp = 0.0;
		double l2_imp = 0.0, linf_imp = 0.0;
		double l2_cn = 0.0, linf_cn = 0.0;
		euler_explicit(dt_list[i], dx, time, &l2_exp, &linf_exp, NULL);
		euler_implicit(dt_list[i], dx, time, &l2_imp, &linf_imp, NULL);
		crank_nicolson(dt_list[i], dx, time, &l2_cn, &linf_cn, NULL);
		fprintf(fp, "%e %e %e %e %e %e %e\n", dt_list[i], l2_exp, linf_exp, l2_imp, linf_imp, l2_cn, linf_cn);
	}
	fclose(fp);
}

int main(void)
{
	//⓵
	run_distribution();
	//⓶
	run_convergence_dx();
	run_convergence_dt();
	return (0);
}
