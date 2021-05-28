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
//Необходимо создать массив структур, содержащий информацию о студентах :
//ФИО, пол, номер группы, номер в списке группы, оценки за прошедшую сессию
//(всего 3 экзамена и 5 дифференцированных зачетов), форма обучения*, отметка
//времени о внесении или изменении данных*.Ввод и изменение данных обо всех
//студентах должен осуществляться в файл students*.
//Написать функции, реализующие операции со структурами(ввод данных с
//	клавиатуры) :
//	1 Создание новой записи о студенте.
//	2 Внесение изменений в уже имеющуюся запись.
//	3 Вывод всех данных о студентах.
//	4 Вывод информации обо всех студентах группы N.N – инициализируется
//	пользователем.
//	5 Вывод топа самых успешных студентов с наивысшим по рейтингу средним
//	баллом за прошедшую сессию.
//	6 Вывод количества студентов мужского и женского пола.
//	7 Определение количества студентов, которые будут получать стипендию
//	(стипендия начисляется, если у студента нет троек и очная форма обучения).*
//	8 Вывод данных о студентах, которые не получают стипендию; учатся только на
//	«хорошо» и «отлично»; учатся только на «отлично»;
//9 Вывод данных о студентах, имеющих номер в списке – k.
//10 Вывод всех записей, сделанных в день, который введет пользователь.Вывод
//всех записей, сделанных после полудня.Вывод всех записей, сделанных до
//полудня.*

const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%d.%m.%Y %X", &tstruct);

	return buf;
}
// Функция преобразования числа в строку
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
	bool stip() //со стипендией
	{
		if (form_ob != "очн")
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
		if (this->sex == 'м')
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
	str = "\nФИО: "+stud.fio+"\nПол: "+ stud.sex+"\nНомер группы: "+ IntToStr(stud.group)  +"\nНомер в группе: "+ IntToStr(stud.num_in_group)
		+"\nЭкзамены: \n";
	for (int i = 0;i < 8;i++)
	{
		str =str+IntToStr(stud.scor[i]) + " ";
	}
	str += "\nФорма обучения: " + stud.form_ob;
	str += "\nВремя изменения: " + stud.d_t;
	return os << str;
}
std::istream& operator >> (std::istream& in, student& stud)
{
	cout << "Введите ФИО: ";
	in >> stud.fio;
	cout << "Введите пол(м/ж): ";
	in >> stud.sex;
	cout << "Введите номер группы: ";
	in >> stud.group;
	cout << "Введите номер в группе: ";
	in >> stud.num_in_group;
	cout << "Введите оценки по экзаменам: ";
	for (int i = 0;i < 3;i++)
	{
		cout << "Экзамен " << i+1 << ": ";
		in >> stud.scor[i];
	}
	cout << "Введите оценки по диф. зачетам: \n";
	for (int i = 3;i < 8;i++)
	{
		cout << "Диф. зач. " << i -2<<": ";
		in >> stud.scor[i];
	}
	cout << "Введите форму обучения (очн/заочн): ";
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
	in.close();		// закрываем файл
	return stud;

}

void keyboard_massiv(student* stud, int N)
{
	for (int i = 0; i < N; i++)
	{
		cout << "\nВведите данные студента: \n";
		cin >> stud[i];
	}
	file_out(stud, N);
}
void print_massiv(student* stud, int N)
{
	for (int i = 0; i < N; i++)
		cout <<"\n Студент "<<i+1<<": "<< stud[i];

}
void edit_massiv(student* stud, int N)
{
	int num;
	cout << "\nВведите номер редактируемой записи (от 0 до " << N - 1<<")\n";
	cin >> num;
	if (num<0 & num>=N)
		cout << "\nОшибка!\n ";
	else
	{
		cout << "\nРедактирование записи: \n";
		cin >> stud[num];
	}
	file_out(stud, N);

}
void add_massiv(student* stud, int *N)
{
	student st;
	cout << "\nВведите данные студента: \n";
	cin >> st;
	stud=addElemet(stud, (*N), st);
	(*N)++;
	file_out(stud, (*N));
}
//	4 Вывод информации обо всех студентах группы N.N – инициализируется
//	пользователем.
void print_group(student* stud, int N)
{
	int num;
	cout << "\nВведите номер группы: ";
	cin >> num;
	for (int i = 0; i < N; i++)
		if (stud[i].check_gr(num))
		cout << "\n Студент " << i + 1 << ": " << stud[i];

}
//	5 Вывод топа самых успешных студентов с наивысшим по рейтингу средним
//	баллом за прошедшую сессию.
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
		cout << "\n Студент " << i + 1 << ": " << st[i];

}
//	6 Вывод количества студентов мужского и женского пола.
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
	cout << "\n Количество парней: " << male << "\n Количество девушек: " << female;
}

//	7 Определение количества студентов, которые будут получать стипендию
void print_stip(student* stud, int N)
{
	int st = 0;
	for (int i = 0; i < N; i++)
	{
		if (stud[i].stip())
			st++;
	}
	cout << "\n Количество стипендиатов: " << st << "\n ";
}
//	8 Вывод данных о студентах, которые не получают стипендию; учатся только на
//	«хорошо» и «отлично»; учатся только на «отлично»;
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
	cout << "\n Количество не стипендиатов: " << st << "\n ";
	cout << "\n Количество хорошистов: " << h_o << "\n ";
	cout << "\n Количество отличников: " << o << "\n ";
}

//9 Вывод данных о студентах, имеющих номер в списке – k.
void print_gr_num(student* stud, int N)
{
	int num = 0;
	cout << "\nВведите номер в списке: ";
	cin >> num;
	for (int i = 0; i < N; i++)
	{
		if (stud[i].check_num_in_group(num))
			cout <<"\n"<< stud[i] << "\n";
	}
}

//10 Вывод всех записей, сделанных в день, который введет пользователь.Вывод
//всех записей, сделанных после полудня.Вывод всех записей, сделанных до
//полудня.*
void print_date(student* stud, int N)
{
	string num = "";
	cout << "\nВведите дату в формате дд.мм.гггг: ";
	cin >> num;
	for (int i = 0; i < N; i++)
	{
		if (stud[i].today(num))
			cout << "\n" << stud[i] << "\n";
	}
	cout << "\nВсе записи сделанные до полудня: ";
	for (int i = 0; i < N; i++)
		if (stud[i].noon())
		cout << "\n Студент " << i + 1 << ": " << stud[i];
	cout << "\nВсе записи сделанные после полудня: ";
	for (int i = 0; i < N; i++)
		if (!stud[i].noon())
			cout << "\n Студент " << i + 1 << ": " << stud[i];
}