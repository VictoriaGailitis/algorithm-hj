// HookeJeeves2.cpp: определяет точку входа для консольного приложения.
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
	//увеличить на шаг
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
			//уменьшить на шаг
			x[j] = y[j] - h;
			fz = calculate(x);
			if (fz < fi)
			{
				y[j] = x[j];
				fz = calculate(x);
			}
			else
			{
				//оставить начальное значение
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
	
	std::cout << "Введите число переменных: ";
	std::cin >> n;
	
	std::cout << "Введите начальную точку x1,x2,...,xN: ";
	for (i = 0; i < n; i++)
		std::cin >> x[i];
	
	std::cout << "Введите длину шага: ";
	std::cin >> h;
    
	//Вычислить значение функции в в базисной точке
	for(i = 0; i < n; i++)
	{
		y[i] = x[i];
		p[i] = x[i];
		b[i] = x[i];
	}

	fi = calculate(x);

	std::cout << "Начальное значение функции: " << fi << std::endl;
	for (i = 0; i < n; i++)
		std::cout << x[i] << " ";
	std::cout << std::endl;

	//Выполнить исследование
	flag = false;
	j = 0;
	fb = fi;

	while(true)
	{
		research();
		std:: cout << "Пробный шаг " << fz << std::endl;
		for (i = 0; i < n; i++)
			std::cout << x[i] << " ";
		std::cout << std::endl;
		//Если исследованы все текущие координаты
		if (j == n)
		{
			//Текущее значение меньше значения в базисной точке?
			if (fi < (fb - 1e-08))
			{
				//новая базисная точка
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

				std::cout << "Поиск по образцу: " << fz << std::endl;
				for (i = 0; i < n; i++)
					std::cout << x[i] << " ";
				std::cout << std::endl;
				j = 0;
				//новое исследование
				continue;
			}
			else
			{
				if (flag) //если получена новая базисная точка
				{
					//замена базисной точки
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
					std::cout << "Замена базисной точки: " << fz << std::endl;
					for (i = 0; i < n; i++)
						std::cout << x[i] << " ";
					std::cout << std::endl;
					j = 0;
					continue;
				}
				else
				{
					//уменьшить шаг
					h /= 10;
					std::cout << "Уменьшить длину шага" << std::endl;
					if (h < 1e-06) break; //закончить работу, если шаг слишком мал
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

	std::cout << "Минимум найден" << std::endl;
	for (i = 0; i < n; i++)
		std::cout << "x[" << i+1 << "] = " << p[i] << std::endl;
	std::cout << "Минимум функции равен: " << fb << std::endl;

    system("pause");
}
 

