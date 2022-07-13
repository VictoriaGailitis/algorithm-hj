// HookeJeeves2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include "funcs.h"

void main()
{
    setlocale(LC_ALL,"Russian");
	system("color F0");

	int n, j(0);
	double h;
	bool flag;

	strct hj;
	struct strct* HookeJeevs = &hj; //��������� �� ���������

	std::cout << "������� ����� ����������: ";
	std::cin >> n;
	
	std::cout << "������� ��������� ����� x1,x2,...,xN: ";
	for (int i = 0; i < n; i++)
		std::cin >> hj.x[i];
	
	std::cout << "������� ����� ����: ";
	std::cin >> h;
    
	//��������� �������� ������� � � �������� �����
	for(int i = 0; i < n; i++)
	{
		hj.y[i] = hj.x[i];
		hj.p[i] = hj.x[i];
		hj.b[i] = hj.x[i];
	}

	hj.fi = calculate(hj.x);

	std::cout << "��������� �������� �������: " << hj.fi << std::endl;
	for (int i = 0; i < n; i++)
		std::cout << hj.x[i] << " ";
	std::cout << std::endl;

	flag = false;
	j = 0;
	hj.fb = hj.fi;

	while(true)
	{
		//��������� ������������
		research(HookeJeevs, h, n, j);
		std:: cout << "������� ��� " << hj.fz << std::endl;
		for (int i = 0; i < n; i++)
			std::cout << hj.x[i] << " ";
		std::cout << std::endl;
		//���� ����������� ��� ������� ����������
		if (j == n)
		{
			//������� �������� ������ �������� � �������� �����?
			if (hj.fi < (hj.fb - 1e-08))
			{
				//����� �������� �����
				for (int i = 0; i < n; i++)
				{
					hj.p[i] = 2.*hj.y[i]-hj.b[i];
					hj.b[i] = hj.y[i];
					hj.x[i] = hj.p[i];
					hj.y[i] = hj.x[i];
				}
				hj.fz = calculate(hj.x);
				hj.fb = hj.fi;
				flag = true;
				hj.fi = hj.fz;

				std::cout << "����� �� �������: " << hj.fz << std::endl;
				for (int i = 0; i < n; i++)
					std::cout << hj.x[i] << " ";
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
					for (int i = 0; i < n; i++)
					{
						hj.p[i] = hj.b[i];
						hj.y[i] = hj.b[i];
						hj.x[i] = hj.b[i];
					}
					hj.fz = calculate(hj.x);
					flag = false;
					hj.fi = hj.fz;
					hj.fb = hj.fz;
					std::cout << "������ �������� �����: " << hj.fz << std::endl;
					for (int i = 0; i < n; i++)
						std::cout << hj.x[i] << " ";
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
	for (int i = 0; i < n; i++)
		std::cout << "x[" << i+1 << "] = " << hj.p[i] << std::endl;
	std::cout << "������� ������� �����: " << hj.fb << std::endl;

    system("pause");
}
 

