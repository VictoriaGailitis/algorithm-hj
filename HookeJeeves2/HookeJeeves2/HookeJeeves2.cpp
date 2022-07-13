// HookeJeeves2.cpp: определяет точку входа для консольного приложения.
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
	struct strct* HookeJeevs = &hj; //указатель на структуру

	std::cout << "Введите число переменных: ";
	std::cin >> n;
	
	std::cout << "Введите начальную точку x1,x2,...,xN: ";
	for (int i = 0; i < n; i++)
		std::cin >> hj.x[i];
	
	std::cout << "Введите длину шага: ";
	std::cin >> h;
    
	//Вычислить значение функции в в базисной точке
	for(int i = 0; i < n; i++)
	{
		hj.y[i] = hj.x[i];
		hj.p[i] = hj.x[i];
		hj.b[i] = hj.x[i];
	}

	hj.fi = calculate(hj.x);

	std::cout << "Начальное значение функции: " << hj.fi << std::endl;
	for (int i = 0; i < n; i++)
		std::cout << hj.x[i] << " ";
	std::cout << std::endl;

	flag = false;
	j = 0;
	hj.fb = hj.fi;

	while(true)
	{
		//Выполнить исследование
		research(HookeJeevs, h, n, j);
		std:: cout << "Пробный шаг " << hj.fz << std::endl;
		for (int i = 0; i < n; i++)
			std::cout << hj.x[i] << " ";
		std::cout << std::endl;
		//Если исследованы все текущие координаты
		if (j == n)
		{
			//Текущее значение меньше значения в базисной точке?
			if (hj.fi < (hj.fb - 1e-08))
			{
				//новая базисная точка
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

				std::cout << "Поиск по образцу: " << hj.fz << std::endl;
				for (int i = 0; i < n; i++)
					std::cout << hj.x[i] << " ";
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
					std::cout << "Замена базисной точки: " << hj.fz << std::endl;
					for (int i = 0; i < n; i++)
						std::cout << hj.x[i] << " ";
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
	for (int i = 0; i < n; i++)
		std::cout << "x[" << i+1 << "] = " << hj.p[i] << std::endl;
	std::cout << "Минимум функции равен: " << hj.fb << std::endl;

    system("pause");
}
 

