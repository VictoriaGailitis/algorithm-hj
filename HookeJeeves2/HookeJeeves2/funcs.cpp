#include "stdafx.h"
#include <iostream>
#include "funcs.h"

double calculate(double *x)
{
	if (x[0] < 0. || x[1] < 0. || (x[0] + x[1] < 4.))
		return 1.7e+38;
	else
		return 3.*x[0]*x[0] + 4.*x[0]*x[1] + 5.*x[1]*x[1];
}

void research(struct strct *hj , double h, int n, int j)
{
	//увеличить на шаг
	hj->x[j] = hj->y[j] + h;
	hj->fz = calculate(hj->x);
	for(int i = 0; i < n; i++)
	{
		if (hj->fz < hj->fi)
		{
			hj->y[j] = hj->x[j];
			hj->fz = calculate(hj->x);
		}
		else
		{
			//уменьшить на шаг
			hj->x[j] = hj->y[j] - h;
			hj->fz = calculate(hj->x);
			if (hj->fz < hj->fi)
			{
				hj->y[j] = hj->x[j];
				hj->fz = calculate(hj->x);
			}
			else
			{
				//оставить начальное значение
				hj->x[j] = hj->y[j];
				hj->fz = calculate(hj->x);
			}
		}
	}
	hj->fi = hj->fz;
}
