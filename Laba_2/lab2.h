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
//2 ����������� �������� �������� ������������� ������� �. 1
std::clock_t start;
double time_create_keyboard;
double time_create_random;
double time_create_infile;

void file_output(int* X, int N);





//X) ������������ ������ ���������� ��������� � �������, ������� �����
//������������� ����������� ���������� �������(0 �� 99);
void random_massiv(int* X, int *N )
{
	int a=0,  b=99;
	cout << "\n\n������� N: ";
	cin >> (*N);
	int i;
	start = std::clock();
	for (i = 0; i < (*N); i++)
	{
		X[i] = (b - a) * (int)rand() / RAND_MAX + a;
	}
	time_create_random = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\n��������: "<< time_create_random<<endl;

	file_output(X, (*N));
}

//�) ������������ ������ � ������� �������� �������, N ������������
//������������� �� ���������� ��������� ���������;
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
	cout << "\n\n��������: " << time_create_keyboard << endl;
	file_output(X, (*N));
	return X;
}
//�) ������ ����������� � �����, N ������������ ��� ���������� ���������
//������� � �����.
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
	in.close();		// ��������� ����
	time_create_infile = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\n��������: " << time_create_infile << endl;
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
	cout << "\n\n������ �������" << endl;
	for (int i = 0; i < N; i++)
		cout << X[i] << " ";

}
//3 �������, �������� � ��������� �������� �������.�������� � ���������
//�������� ���������� ����������� �� ������� � �� ��������.

//�������� �� �������
void del_ind(int* X, int* N, int index)
{
	start = std::clock();
	for (int i = index; i < (*N); ++i)
	{
		X[i] = X[i + 1];
	}
	--(*N);
	double time_del = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\n��������: " << time_del << endl;
}

//�������� �� �������
void del(int* X, int* N)
{
	int temp;
	cout << "\n������� �������� ������� ���������� �������: \n";
	cin >> temp;
	start = std::clock();
	for (int i = 0; i < (*N); i++)
	{
		if (X[i] == temp)
		{
			del_ind(X, N, i);
			double time_del = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "\n\n��������: " << time_del << endl;
			return;
		}
	}
	cout << "\n�������� �� �������!\n";
}

void deleteArray(int* X, int* N)
{
	int pos;
	int temp;
	cout << "\n��������: \n1. �������� �� �������!\n2. �������� �� ��������!\n\n";
	cin >> pos;
	if (pos == 1)
	{
		cout << "\n������� ������ �������� ������� ���������� �������: \n";
		cin >> temp;
		if (temp<0&temp>=(*N))
			cout << "\n�������� ������! \n";
		else
			del_ind(X, N, temp);
	}
	else if (pos == 2)
	{
		del(X, N);
	}
	else cout << "\n������! \n";

}

int* insertArray(int* X, int* N)
{
	int temp;
	cout << "\n������� �������� ������ ��������: ";
	cin >> temp;
	start = std::clock();
	X=addElemet(X, (*N), temp);
	(*N)++;
	double time_ins = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\n��������: " << time_ins << endl;
	return X;
}

//��������� �������� ���������� ����������� �� ������� � �� ��������.
void readElement(int *X, int N)
{
	int pos;
	int temp;
	cout << "\n��������: \n1. ��������� �� �������!\n2. ��������� �� ��������!\n\n";
	cin >> pos;
	if (pos == 1)
	{
		cout << "\n������� ������ �������� ������� ���������� ��������: \n";
		cin >> temp;
		if (temp < 0 & temp >= N)
			cout << "\n�������� ������! \n";
		else
		{

			start = std::clock();
			cout << "\nX[" << temp << "]= " << X[temp];
			double time = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "\n\n��������: " << time << endl;
		}
	}
	else if (pos == 2)
	{
		cout << "\n�������  �������� ������ �������� ���������� ��������: \n";
		cin >> temp;
		start = std::clock();
		for (int i = 0; i < N; i++)
		{
			if (X[i] == temp)
			{
				cout << "\n" << temp << " = X[" << i<<"]";
				double time = (std::clock() - start) / (double)CLOCKS_PER_SEC;
				cout << "\n\n��������: " << time << endl;
				return;
			}
		}
		cout << "\n�������� �� �������!\n";
	}
	else cout << "\n������! \n";
}



/// ���������� ������
//5 ������������ ����������� ������ ����������� N, ���:
//X) ������������ ������ ���������� ��������� � ������, �������
//����� ������������� ����������� ���������� �������(0 �� 99);
//�) ������������ ������ � ������� �������� ������, N ������������
//������������� �� ���������� ��������� ���������;
//�) ������ ����������� � �����, N ������������ ��� ���������� ��������� ������
//� �����.
//6 ����������� �������� �������� ����������� ������ �. 5
//7 �������, �������� � ��������� �������� ����������� ������.�������� �
//��������� �������� ���������� ����������� �� ������� � �� ��������.
//8 ����������� �������� �������, �������� � ��������� �������� �����������
//������ �. 7
//������ ���� ����������� ������� ������� ������ �����������, ���� ����
//�����������(���� � ������ / ������� ��� ���������, �� ������ ������ ������� �
//	�� ���� ����� �������� ������������).���������� �������� ����������.���
//	����� ������ 1�4 � 5�8 ������ ��������� ���������� ��������.

//X) ������������ ������ ���������� ��������� � ������, �������
//����� ������������� ����������� ���������� �������(0 �� 99);
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
	cout << "\n\n������� N: ";
	cin >> N;
	int i;
	start = std::clock();
	for (i = 0; i < (N); i++)
	{
		X.AddTail((b - a) * (int)rand() / RAND_MAX + a);
	}
	time_create_random = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\n��������: " << time_create_random << endl;

	file_output_list(X);
	return X;
}

//�) ������������ ������ � ������� �������� �������, N ������������
//������������� �� ���������� ��������� ���������;
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
	cout << "\n\n��������: " << time_create_keyboard << endl;
	file_output_list(X);
	return X;
}
//�) ������ ����������� � �����, N ������������ ��� ���������� ���������
//������� � �����.
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
	in.close();		// ��������� ����
	time_create_infile = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\n��������: " << time_create_infile << endl;
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
	cout << "\n��������: \n1. �������� �� �������!\n2. �������� �� ��������!\n\n";
	cin >> pos;
	if (pos == 1)
	{
		cout << "\n������� ������ �������� ������� ���������� �������: \n";
		cin >> temp;
		if (temp < 1 & temp > (*X).GetCount())
			cout << "\n�������� ������! \n";
		else
			(*X).Del(temp);
	}
	else if (pos == 2)
	{
		cout << "\n������� �������� ������� ���������� �������: \n";
		cin >> temp;
		(*X).Del((*X).FindPos(temp));
	}
	else cout << "\n������! \n";

}

void insertList(List *X)
{
	int temp;
	cout << "\n������� �������� ������ ��������: ";
	cin >> temp;
	start = std::clock();
	(*X).AddTail(temp);
	double time_ins = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\n��������: " << time_ins << endl;

}

//��������� �������� ���������� ����������� �� ������� � �� ��������.
void readElementList(List X)
{
	int pos;
	int temp;
	cout << "\n��������: \n1. ��������� �� �������!\n2. ��������� �� ��������!\n\n";
	cin >> pos;
	if (pos == 1)
	{
		cout << "\n������� ������ �������� ������� ���������� ��������: \n";
		cin >> temp;
		if (temp < 1 & temp > X.GetCount())
			cout << "\n�������� ������! \n";
		else
		{

			start = std::clock();
			 X.Print(temp);
			double time = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "\n\n��������: " << time << endl;
		}
	}
	else if (pos == 2)
	{
		cout << "\n�������  �������� ������ �������� ���������� ��������: \n";
		cin >> temp;
		start = std::clock();
		int i=X.FindPos(temp);
		double time = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		cout << "\n\n��������: " << time << endl;
		if (i == -1)
			cout << "\n�������� �� �������!\n";
		else
			cout << "\n������: "<<i<<endl;
	}
	else cout << "\n������! \n";
}