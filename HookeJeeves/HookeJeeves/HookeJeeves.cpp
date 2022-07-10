// HookeJeeves.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>

const int lim = 10;

double calculate(double *x)
{
	if (x[0] < 0. || x[1] < 0. || (x[0] + x[1] < 4.))
		return 1.7e+38;
	else
		return 3.*x[0]*x[0] + 4.*x[0]*x[1] + 5.*x[1]*x[1];
}
void _tmain()
{
	setlocale(LC_ALL, "Russian");

	int i, j, n, fe;
	double k, h, ps, bs, fb, fi, fz;
	double x[lim], y[lim], b[lim], p[lim];

	std::cout << "������� ����� ����������: ";
	std::cin >> n;
	
	std::cout << "������� ��������� ����� x1,x2,...,xN: ";
	for (i = 0; i < n; i++)
		std::cin >> x[i];
	
	std::cout << "������� ����� ����: ";
	std::cin >> h;

	k = h;
	fe = 0;

	for(i = 0; i < n; i++)
	{
		y[i] = x[i];
		p[i] = x[i];
		b[i] = x[i];
	}

	fi = calculate(x);
	fe++;

	std::cout << "��������� �������� �������: " << fi << std::endl;

	for (i = 0; i < n; i++)
		std::cout << x[i] << " ";
	std::cout << std::endl;

	ps = 0;
	bs = 1;
	j = 0;
	fb = fi;

	one: x[j] = y[j] + k;
	fz = calculate(x);
	fe++;
	if (fz < fi) goto two;
	x[j] = y[j] - k;
	fz = calculate(x);
	fe++;
	if (fz < fi) goto two;
	x[j] = y[j];
	goto three;
	two:
		y[j] = x[j];
	three:
		fz = calculate(x);
		fe++;

	fi = fz;
	std:: cout << "������� ��� " << fz << std::endl;
	for (i = 0; i < n; i++)
		std::cout << x[i] << " ";
	std::cout << std::endl;
	
	if (j == n) goto fourth;
	j++;
	goto one;
	fourth:
		if (fi < (fb - 1e-08)) goto seven;

	if (ps == 1 && bs == 0) goto five;
	goto six;
	five:
		for (i = 0; i < n; i++)
		{
			p[i] = b[i];
			y[i] = b[i];
			x[i] = b[i];
		}

	fz = calculate(x);
	fe++;
	bs = 1;
	ps = 0;
	fi = fz;
	fb = fz;

	std::cout << "������ �������� �����: " << fz << std::endl;
	for (i = 0; i < n; i++)
		std::cout << x[i] << " ";
	std::cout << std::endl;

	j = 0;
	goto one;
	six: k /= 10;
	std::cout << "��������� ����� ����" << std::endl;
	if (k < 1e-06) goto eight;
	j = 0;
	goto one;
	seven:
		for (i = 0; i < n; i++)
		{
			p[i] = 2.*y[i]-b[i];
			b[i] = y[i];
			x[i] = p[i];
			y[i] = x[i];
		}

	fz = calculate(x);
	fe++;
	fb = fi;
	ps = 1;
	bs = 0;
	fi = fz;
	std::cout << "����� �� �������: " << fz << std::endl;
	for (i = 0; i < n; i++)
		std::cout << x[i] << " ";
	std::cout << std::endl;
	j = 0;
	goto one;
eight: std::cout << "������� ������" << std::endl;
	for (i = 0; i < n; i++)
		std::cout << "x[" << i << "] = " << p[i] << std::endl;
	std::cout << "������� ������� �����: " << fb << std::endl;
	std::cout << "���������� ���������� ������� �����: " << fe << std::endl;
	system("pause");
}
