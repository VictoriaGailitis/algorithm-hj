const int lim = 10;

struct strct
{
	double fi, fb, fz;
	double x[lim], y[lim], b[lim], p[lim];
};

double calculate(double *x);
void research(struct strct *hj , double h, int n, int j);