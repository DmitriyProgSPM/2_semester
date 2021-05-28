#pragma once
#pragma warning(disable:4996)
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
#include "function.h"
using namespace std;
//���������� ������� ������ ��������, ���������� ���������� � ��������� :
//���, ���, ����� ������, ����� � ������ ������, ������ �� ��������� ������
//(����� 3 �������� � 5 ������������������ �������), ����� ��������*, �������
//������� � �������� ��� ��������� ������*.���� � ��������� ������ ��� ����
//��������� ������ �������������� � ���� students*.
//�������� �������, ����������� �������� �� �����������(���� ������ �
//	����������) :
//	1 �������� ����� ������ � ��������.
//	2 �������� ��������� � ��� ��������� ������.
//	3 ����� ���� ������ � ���������.
//	4 ����� ���������� ��� ���� ��������� ������ N.N � ����������������
//	�������������.
//	5 ����� ���� ����� �������� ��������� � ��������� �� �������� �������
//	������ �� ��������� ������.
//	6 ����� ���������� ��������� �������� � �������� ����.
//	7 ����������� ���������� ���������, ������� ����� �������� ���������
//	(��������� �����������, ���� � �������� ��� ����� � ����� ����� ��������).*
//	8 ����� ������ � ���������, ������� �� �������� ���������; ������ ������ ��
//	������� � ��������; ������ ������ �� ��������;
//9 ����� ������ � ���������, ������� ����� � ������ � k.
//10 ����� ���� �������, ��������� � ����, ������� ������ ������������.�����
//���� �������, ��������� ����� �������.����� ���� �������, ��������� ��
//�������.*

const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%d.%m.%Y %X", &tstruct);

	return buf;
}
// ������� �������������� ����� � ������
char* IntToStr(int n)
{
	char s[40], t, *temp;
	int i, k;
	int sign = 0;
	i = 0;
	k = n;
	if (k < 0)
	{
		sign = 1;
		k = -k;
	}
	do {
		t = k % 10;
		k = k / 10;
		s[i] = t | 0x30;
		i++;
	} while (k > 0);
	if (sign == 1)
	{
		s[i] = '-';
		i++;
	}
	temp = new char[i];
	k = 0;
	i--;
	while (i >= 0) {
		temp[k] = s[i];
		i--; k++;
	}
	temp[k] = '\0';
	return(temp);
}
struct student {
	string fio;
	char sex;
	int group;
	int num_in_group;
	int scor[8];
	string	form_ob;
	string d_t;		
	student(string fio,char sex,int group,int num_in_group, int scor[8], string	form_ob, string d_t)
	{
		this->fio = fio;
		this->sex= sex;
		this->group= group;
		this->num_in_group= num_in_group;
		this->scor[8]= scor[8];
		this->form_ob= form_ob;
		this->d_t= d_t;
	}
	student()
	{
		this->fio = "";
		this->sex =' ';
		this->group = 0;
		this->num_in_group = 0;
		this->form_ob = "";
		this->d_t = "";
	}
	bool check_gr(int group)
	{
		if (this->group == group)
			return true;
		else
			return false;
	}
	bool check_num_in_group(int num_in_group)
	{
		if (this->num_in_group == num_in_group)
			return true;
		else
			return false;
	}
	bool check_scor(int score)
	{
		for (int i = 0;i < 8;i++)
		{
			if (scor[i] < score)
				return false;
		}
		return true;
	}
	bool stip() //�� ����������
	{
		if (form_ob != "���")
			return false;
		for (int i = 0;i < 8;i++)
		{
			if (scor[i]<4)
				return false;
		}
		return true;
	}

	bool check_sex()
	{
		if (this->sex == '�')
			return true;
		else
			return false;
	}
	double sr_ball()
	{
		int sum=0;
		for (int i = 0;i < 8;i++)
		{
			sum += scor[i];
		}
		return sum/ 8.;
	}
	bool today(string date)
	{
		if (d_t.find(date) == -1)
			return false;
		else
			return true;

	}
	bool noon()
	{
		if ((d_t.find(" 00") == -1)&(d_t.find(" 01") == -1)&
			(d_t.find(" 02") == -1)&(d_t.find(" 03") == -1)&
			(d_t.find(" 04") == -1)&(d_t.find(" 05") == -1)&
			(d_t.find(" 06") == -1)&(d_t.find(" 07") == -1)&
			(d_t.find(" 08") == -1)&(d_t.find(" 09") == -1)&
			(d_t.find(" 10") == -1)&(d_t.find(" 11") == -1))
			return false;
		else
			return true;

	}
};
std::ostream& operator << (std::ostream &os, const student &stud)
{
	string str;
	str = "\n���: "+stud.fio+"\n���: "+ stud.sex+"\n����� ������: "+ IntToStr(stud.group)  +"\n����� � ������: "+ IntToStr(stud.num_in_group)
		+"\n��������: \n";
	for (int i = 0;i < 8;i++)
	{
		str =str+IntToStr(stud.scor[i]) + " ";
	}
	str += "\n����� ��������: " + stud.form_ob;
	str += "\n����� ���������: " + stud.d_t;
	return os << str;
}
std::istream& operator >> (std::istream& in, student& stud)
{
	cout << "������� ���: ";
	in >> stud.fio;
	cout << "������� ���(�/�): ";
	in >> stud.sex;
	cout << "������� ����� ������: ";
	in >> stud.group;
	cout << "������� ����� � ������: ";
	in >> stud.num_in_group;
	cout << "������� ������ �� ���������: ";
	for (int i = 0;i < 3;i++)
	{
		cout << "������� " << i+1 << ": ";
		in >> stud.scor[i];
	}
	cout << "������� ������ �� ���. �������: \n";
	for (int i = 3;i < 8;i++)
	{
		cout << "���. ���. " << i -2<<": ";
		in >> stud.scor[i];
	}
	cout << "������� ����� �������� (���/�����): ";
	in >> stud.form_ob;
	stud.d_t = currentDateTime();
	return in;
}

void file_out(student* stud, int N)
{
	ofstream output("student.txt");
	for (int i = 0; i < N; i++)
		output << stud[i].fio << "\n"
		<< stud[i].group << "\n" 
		<< stud[i].num_in_group	<< "\n" 
		<< stud[i].sex << "\n"
		<< stud[i].form_ob << "\n"
		<< stud[i].scor[0] << " "
		<< stud[i].scor[1] << " "
		<< stud[i].scor[2] << " "
		<< stud[i].scor[3] << " "
		<< stud[i].scor[4] << " "
		<< stud[i].scor[5] << " "
		<< stud[i].scor[6] << " "
		<< stud[i].scor[7] << "\n"
		<< stud[i].d_t+"\n";
	output.close();
}
student* file_in(int *N)
{
	student* stud= NULL;
	student temp;
	string line;
	ifstream in("student.txt");
	(*N) = 0;
	if (in.is_open())
	{
		while (getline(in, line))
		{
			temp.fio = line;
			getline(in, line);
			temp.group = atoi(line.c_str());
			getline(in, line);
			temp.num_in_group = atoi(line.c_str());
			getline(in, line);
			temp.sex = line[0];
			getline(in, line);
			temp.form_ob = line;
			for (int i = 0; i < 8; i++)
				in >> temp.scor[i];
			getline(in, line);
			getline(in, line);
			temp.d_t = line;
			stud = addElemet(stud, (*N), temp);
			(*N)++;

		}
	}
	in.close();		// ��������� ����
	return stud;

}

void keyboard_massiv(student* stud, int N)
{
	for (int i = 0; i < N; i++)
	{
		cout << "\n������� ������ ��������: \n";
		cin >> stud[i];
	}
	file_out(stud, N);
}
void print_massiv(student* stud, int N)
{
	for (int i = 0; i < N; i++)
		cout <<"\n ������� "<<i+1<<": "<< stud[i];

}
void edit_massiv(student* stud, int N)
{
	int num;
	cout << "\n������� ����� ������������� ������ (�� 0 �� " << N - 1<<")\n";
	cin >> num;
	if (num<0 & num>=N)
		cout << "\n������!\n ";
	else
	{
		cout << "\n�������������� ������: \n";
		cin >> stud[num];
	}
	file_out(stud, N);

}
void add_massiv(student* stud, int *N)
{
	student st;
	cout << "\n������� ������ ��������: \n";
	cin >> st;
	stud=addElemet(stud, (*N), st);
	(*N)++;
	file_out(stud, (*N));
}
//	4 ����� ���������� ��� ���� ��������� ������ N.N � ����������������
//	�������������.
void print_group(student* stud, int N)
{
	int num;
	cout << "\n������� ����� ������: ";
	cin >> num;
	for (int i = 0; i < N; i++)
		if (stud[i].check_gr(num))
		cout << "\n ������� " << i + 1 << ": " << stud[i];

}
//	5 ����� ���� ����� �������� ��������� � ��������� �� �������� �������
//	������ �� ��������� ������.
void print_top(student* stud, int N)
{
	student *st = new student[N];
	student temp;
	st = copyArray(stud,N);
	double max = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N-1; j++)
		{
			if (st[j].sr_ball()< st[j+1].sr_ball())
			{
				temp = st[j];
				st[j] = st[j + 1];
				st[j + 1] = temp;
			}
		}
	}
	for (int i = 0; (i < N)&(i<3); i++)
		cout << "\n ������� " << i + 1 << ": " << st[i];

}
//	6 ����� ���������� ��������� �������� � �������� ����.
void print_sex(student* stud, int N)
{
	int male = 0, female = 0;
	for (int i = 0; i < N; i++)
	{
		if (stud[i].check_sex())
			male++;
		else
			female++;
	}
	cout << "\n ���������� ������: " << male << "\n ���������� �������: " << female;
}

//	7 ����������� ���������� ���������, ������� ����� �������� ���������
void print_stip(student* stud, int N)
{
	int st = 0;
	for (int i = 0; i < N; i++)
	{
		if (stud[i].stip())
			st++;
	}
	cout << "\n ���������� ������������: " << st << "\n ";
}
//	8 ����� ������ � ���������, ������� �� �������� ���������; ������ ������ ��
//	������� � ��������; ������ ������ �� ��������;
void print_scor(student* stud, int N)
{
	int st = 0,h_o=0,o=0;
	for (int i = 0; i < N; i++)
	{
		if (!stud[i].stip())
			st++;
		if (stud[i].check_scor(4))
			h_o++;
		if (stud[i].check_scor(5))
			o++;
	}
	cout << "\n ���������� �� ������������: " << st << "\n ";
	cout << "\n ���������� ����������: " << h_o << "\n ";
	cout << "\n ���������� ����������: " << o << "\n ";
}

//9 ����� ������ � ���������, ������� ����� � ������ � k.
void print_gr_num(student* stud, int N)
{
	int num = 0;
	cout << "\n������� ����� � ������: ";
	cin >> num;
	for (int i = 0; i < N; i++)
	{
		if (stud[i].check_num_in_group(num))
			cout <<"\n"<< stud[i] << "\n";
	}
}

//10 ����� ���� �������, ��������� � ����, ������� ������ ������������.�����
//���� �������, ��������� ����� �������.����� ���� �������, ��������� ��
//�������.*
void print_date(student* stud, int N)
{
	string num = "";
	cout << "\n������� ���� � ������� ��.��.����: ";
	cin >> num;
	for (int i = 0; i < N; i++)
	{
		if (stud[i].today(num))
			cout << "\n" << stud[i] << "\n";
	}
	cout << "\n��� ������ ��������� �� �������: ";
	for (int i = 0; i < N; i++)
		if (stud[i].noon())
		cout << "\n ������� " << i + 1 << ": " << stud[i];
	cout << "\n��� ������ ��������� ����� �������: ";
	for (int i = 0; i < N; i++)
		if (!stud[i].noon())
			cout << "\n ������� " << i + 1 << ": " << stud[i];
}