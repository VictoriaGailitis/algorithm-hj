// HookeJeeves2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>

using namespace std;
const int lim = 10;

int i, j, n;
double h, fi, fb, fz;
double x[lim], y[lim], b[lim], p[lim];
bool flag;

double calculate(double *x)
{
	if (x[0] < 0. || x[1] < 0. || (x[0] + x[1] < 4.))
		return 1.7e+38;
	else
		return 3.*x[0]*x[0] + 4.*x[0]*x[1] + 5.*x[1]*x[1];
}

void research()
{
	//��������� �� ���
	x[j] = y[j] + h;
	fz = calculate(x);
	for(i = 0; i < n; i++)
	{
		if (fz < fi)
		{
			y[j] = x[j];
			fz = calculate(x);
		}
		else
		{
			//��������� �� ���
			x[j] = y[j] - h;
			fz = calculate(x);
			if (fz < fi)
			{
				y[j] = x[j];
				fz = calculate(x);
			}
			else
			{
				//�������� ��������� ��������
				x[j] = y[j];
				fz = calculate(x);
			}
		}
	}
	fi = fz;
}

void main()
{
    setlocale(LC_ALL,"Russian");
	
	std::cout << "������� ����� ����������: ";
	std::cin >> n;
	
	std::cout << "������� ��������� ����� x1,x2,...,xN: ";
	for (i = 0; i < n; i++)
		std::cin >> x[i];
	
	std::cout << "������� ����� ����: ";
	std::cin >> h;
    
	//��������� �������� ������� � � �������� �����
	for(i = 0; i < n; i++)
	{
		y[i] = x[i];
		p[i] = x[i];
		b[i] = x[i];
	}

	fi = calculate(x);

	std::cout << "��������� �������� �������: " << fi << std::endl;
	for (i = 0; i < n; i++)
		std::cout << x[i] << " ";
	std::cout << std::endl;

	//��������� ������������
	flag = false;
	j = 0;
	fb = fi;

	while(true)
	{
		research();
		std:: cout << "������� ��� " << fz << std::endl;
		for (i = 0; i < n; i++)
			std::cout << x[i] << " ";
		std::cout << std::endl;
		//���� ����������� ��� ������� ����������
		if (j == n)
		{
			//������� �������� ������ �������� � �������� �����?
			if (fi < (fb - 1e-08))
			{
				//����� �������� �����
				for (i = 0; i < n; i++)
				{
					p[i] = 2.*y[i]-b[i];
					b[i] = y[i];
					x[i] = p[i];
					y[i] = x[i];
				}
				fz = calculate(x);
				fb = fi;
				flag = true;
				fi = fz;

				std::cout << "����� �� �������: " << fz << std::endl;
				for (i = 0; i < n; i++)
					std::cout << x[i] << " ";
				std::cout << std::endl;
				j = 0;
				//����� ������������
				continue;
			}
			else
			{
				if (flag) //���� �������� ����� �������� �����
				{
					//������ �������� �����
					for (i = 0; i < n; i++)
					{
						p[i] = b[i];
						y[i] = b[i];
						x[i] = b[i];
					}
					fz = calculate(x);
					flag = false;
					fi = fz;
					fb = fz;
					std::cout << "������ �������� �����: " << fz << std::endl;
					for (i = 0; i < n; i++)
						std::cout << x[i] << " ";
					std::cout << std::endl;
					j = 0;
					continue;
				}
				else
				{
					//��������� ���
					h /= 10;
					std::cout << "��������� ����� ����" << std::endl;
					if (h < 1e-06) break; //��������� ������, ���� ��� ������� ���
					j = 0;
					continue;
				}
			}
		}
		else
		{
			j++;
			continue;
		}
	}

	std::cout << "������� ������" << std::endl;
	for (i = 0; i < n; i++)
		std::cout << "x[" << i+1 << "] = " << p[i] << std::endl;
	std::cout << "������� ������� �����: " << fb << std::endl;

    system("pause");
}
 

