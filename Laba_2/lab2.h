#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <string>
#include <time.h>
#include <istream>
#include <ostream>
#include <list>
#include <algorithm>
#include <functional>
#include <iterator>
#include <string>
#include <sstream>
#include <ctime>
#include "function.h"
#include "list.h"
using namespace std;
#pragma warning(disable : 4996)
//2 Определение скорости создания динамического массива п. 1
std::clock_t start;
double time_create_keyboard;
double time_create_random;
double time_create_infile;

void file_output(int* X, int N);





//X) пользователь вводит количество элементов в массиве, который будет
//автоматически заполняться случайными числами(0 до 99);
void random_massiv(int* X, int *N )
{
	int a=0,  b=99;
	cout << "\n\nВведите N: ";
	cin >> (*N);
	int i;
	start = std::clock();
	for (i = 0; i < (*N); i++)
	{
		X[i] = (b - a) * (int)rand() / RAND_MAX + a;
	}
	time_create_random = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\nСкорость: "<< time_create_random<<endl;

	file_output(X, (*N));
}

//б) пользователь вводит в консоль элементы массива, N определяется
//автоматически по количеству введенных элементов;
int* keyboard_massiv(int *N)
{
	(*N) = 0;
	int temp;
	int* X = new int[0];
	string line;
	getline(cin, line);
	start = std::clock();
	char *currentWord = strtok(const_cast <char *> (line.c_str()), " ");
	while (currentWord) {
		temp = atoi(currentWord);
		X=addElemet(X,(*N), temp);
		(*N)++;
		currentWord = strtok(nullptr, " ");
	}
	time_create_keyboard = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\nСкорость: " << time_create_keyboard << endl;
	file_output(X, (*N));
	return X;
}
//в) массив считывается с файла, N определяется как количество элементов
//массива в файле.
int* file_input( int *N)
{
	start = std::clock();
	string line;
	int temp;
	int *X=new int[(*N)];
	ifstream in("array.txt");
	(*N) = 0;
	if (in.is_open())
	{
		while (getline(in, line))
		{
			char *currentWord = strtok(const_cast <char *> (line.c_str()), " ");
			while (currentWord) {
				temp = atoi(currentWord);
				X=addElemet(X, (*N), temp);
				(*N)++;
				currentWord = strtok(nullptr, " ");
			}

		}
	}
	in.close();		// закрываем файл
	time_create_infile = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\nСкорость: " << time_create_infile << endl;
	return X;
}

void file_output(int* X, int N)
{
	ofstream output("array.txt");
	for (int i = 0; i < N; i++)
		output << X[i] << " ";
	output.close();
}
void print_massiv(int* X, int N)
{
	cout << "\n\nПечать массива" << endl;
	for (int i = 0; i < N; i++)
		cout << X[i] << " ";

}
//3 Вставка, удаление и получение элемента массива.Удаление и получение
//элемента необходимо реализовать по индексу и по значению.

//удаление по индексу
void del_ind(int* X, int* N, int index)
{
	start = std::clock();
	for (int i = index; i < (*N); ++i)
	{
		X[i] = X[i + 1];
	}
	--(*N);
	double time_del = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\nСкорость: " << time_del << endl;
}

//удаление по значеню
void del(int* X, int* N)
{
	int temp;
	cout << "\nВведите значение которое необходимо удалить: \n";
	cin >> temp;
	start = std::clock();
	for (int i = 0; i < (*N); i++)
	{
		if (X[i] == temp)
		{
			del_ind(X, N, i);
			double time_del = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "\n\nСкорость: " << time_del << endl;
			return;
		}
	}
	cout << "\nЗначение не найдено!\n";
}

void deleteArray(int* X, int* N)
{
	int pos;
	int temp;
	cout << "\nВыберите: \n1. Удаление по индексу!\n2. Удаление по значению!\n\n";
	cin >> pos;
	if (pos == 1)
	{
		cout << "\nВведите индекс значения которое необходимо удалить: \n";
		cin >> temp;
		if (temp<0&temp>=(*N))
			cout << "\nНеверный индекс! \n";
		else
			del_ind(X, N, temp);
	}
	else if (pos == 2)
	{
		del(X, N);
	}
	else cout << "\nОшибка! \n";

}

int* insertArray(int* X, int* N)
{
	int temp;
	cout << "\nВведите значение нового элемента: ";
	cin >> temp;
	start = std::clock();
	X=addElemet(X, (*N), temp);
	(*N)++;
	double time_ins = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\nСкорость: " << time_ins << endl;
	return X;
}

//получение элемента необходимо реализовать по индексу и по значению.
void readElement(int *X, int N)
{
	int pos;
	int temp;
	cout << "\nВыберите: \n1. Получение по индексу!\n2. Получение по значению!\n\n";
	cin >> pos;
	if (pos == 1)
	{
		cout << "\nВведите индекс значения которое необходимо получить: \n";
		cin >> temp;
		if (temp < 0 & temp >= N)
			cout << "\nНеверный индекс! \n";
		else
		{

			start = std::clock();
			cout << "\nX[" << temp << "]= " << X[temp];
			double time = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "\n\nСкорость: " << time << endl;
		}
	}
	else if (pos == 2)
	{
		cout << "\nВведите  значение индекс которого необходимо получить: \n";
		cin >> temp;
		start = std::clock();
		for (int i = 0; i < N; i++)
		{
			if (X[i] == temp)
			{
				cout << "\n" << temp << " = X[" << i<<"]";
				double time = (std::clock() - start) / (double)CLOCKS_PER_SEC;
				cout << "\n\nСкорость: " << time << endl;
				return;
			}
		}
		cout << "\nЗначение не найдено!\n";
	}
	else cout << "\nОшибка! \n";
}



/// двусвязный список
//5 Формирование двусвязного списка размерности N, где:
//X) пользователь вводит количество элементов в списке, который
//будет автоматически заполняться случайными числами(0 до 99);
//б) пользователь вводит в консоль элементы списка, N определяется
//автоматически по количеству введенных элементов;
//в) список считывается с файла, N определяется как количество элементов списка
//в файле.
//6 Определение скорости создания двусвязного списка п. 5
//7 Вставка, удаление и получение элемента двусвязного списка.Удаление и
//получение элемента необходимо реализовать по индексу и по значению.
//8 Определение скорости вставки, удаление и получения элемента двусвязного
//списка п. 7
//Должна быть возможность запуска каждого пункта многократно, если есть
//возможность(если в списке / массиве нет элементов, то нельзя ничего удалить и
//	об этом нужно сообщить пользователю).Необходимо сравнить результаты.Для
//	этого пункты 1–4 и 5–8 должны принимать одинаковые значения.

//X) пользователь вводит количество элементов в списке, который
//будет автоматически заполняться случайными числами(0 до 99);
void file_output_list(List X)
{
	ofstream output("array.txt");
	for (int i = 0; i < X.GetCount(); i++)
		output << X.ReturnEL(i) << " ";
	output.close();
}

List random_list()
{
	List X;
	int N;
	int a = 0, b = 99;
	cout << "\n\nВведите N: ";
	cin >> N;
	int i;
	start = std::clock();
	for (i = 0; i < (N); i++)
	{
		X.AddTail((b - a) * (int)rand() / RAND_MAX + a);
	}
	time_create_random = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\nСкорость: " << time_create_random << endl;

	file_output_list(X);
	return X;
}

//б) пользователь вводит в консоль элементы массива, N определяется
//автоматически по количеству введенных элементов;
List keyboard_list()
{
	List X;
	int temp;
	string line;
	getline(cin, line);
	start = std::clock();
	char *currentWord = strtok(const_cast <char *> (line.c_str()), " ");
	while (currentWord) {
		temp = atoi(currentWord);
		X.AddTail(temp);
		currentWord = strtok(nullptr, " ");
	}
	time_create_keyboard = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\nСкорость: " << time_create_keyboard << endl;
	file_output_list(X);
	return X;
}
//в) массив считывается с файла, N определяется как количество элементов
//массива в файле.
List file_list()
{
	start = std::clock();
	string line;
	int temp;
	List X;
	ifstream in("array.txt");
	if (in.is_open())
	{
		while (getline(in, line))
		{
			char *currentWord = strtok(const_cast <char *> (line.c_str()), " ");
			while (currentWord) {
				temp = atoi(currentWord);
				X.AddTail(temp);
				currentWord = strtok(nullptr, " ");
			}

		}
	}
	in.close();		// закрываем файл
	time_create_infile = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\nСкорость: " << time_create_infile << endl;
	return X;
}


void print_list(List X)
{
	X.Print();
}

void deleteList(List *X)
{
	int pos;
	int temp;
	cout << "\nВыберите: \n1. Удаление по индексу!\n2. Удаление по значению!\n\n";
	cin >> pos;
	if (pos == 1)
	{
		cout << "\nВведите индекс значения которое необходимо удалить: \n";
		cin >> temp;
		if (temp < 1 & temp > (*X).GetCount())
			cout << "\nНеверный индекс! \n";
		else
			(*X).Del(temp);
	}
	else if (pos == 2)
	{
		cout << "\nВведите значение которое необходимо удалить: \n";
		cin >> temp;
		(*X).Del((*X).FindPos(temp));
	}
	else cout << "\nОшибка! \n";

}

void insertList(List *X)
{
	int temp;
	cout << "\nВведите значение нового элемента: ";
	cin >> temp;
	start = std::clock();
	(*X).AddTail(temp);
	double time_ins = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\nСкорость: " << time_ins << endl;

}

//получение элемента необходимо реализовать по индексу и по значению.
void readElementList(List X)
{
	int pos;
	int temp;
	cout << "\nВыберите: \n1. Получение по индексу!\n2. Получение по значению!\n\n";
	cin >> pos;
	if (pos == 1)
	{
		cout << "\nВведите индекс значения которое необходимо получить: \n";
		cin >> temp;
		if (temp < 1 & temp > X.GetCount())
			cout << "\nНеверный индекс! \n";
		else
		{

			start = std::clock();
			 X.Print(temp);
			double time = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "\n\nСкорость: " << time << endl;
		}
	}
	else if (pos == 2)
	{
		cout << "\nВведите  значение индекс которого необходимо получить: \n";
		cin >> temp;
		start = std::clock();
		int i=X.FindPos(temp);
		double time = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		cout << "\n\nСкорость: " << time << endl;
		if (i == -1)
			cout << "\nЗначение не найдено!\n";
		else
			cout << "\nИндекс: "<<i<<endl;
	}
	else cout << "\nОшибка! \n";
}