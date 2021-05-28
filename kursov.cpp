// kursov.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.graphics.h>
#include <string>
#include "menu.h"
#include "lab1.h"
#include "lab2.h"
#include "lab3.h"
#include "lab4.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const char* S[] = { "Лаб. 1", "Лаб. 2", "Лаб. 3", "Лаб. 4","Выход" };
	const char* S1[] = { "Клавиатура", "Печать на экран","Редактировать","Добавить запись","Студенты группы N.N","Топ 3 студента", "Количество м/ж","Кол. стипендиатов","Не стип, Хор/отл","Номер в списке ","Дата","Загрузить из файла","Выход" };
	const char* S2[] = { "М:Заполнить случайными числами", "М:Заполнить с клавиатуры", "М:Заполнить из файла", "М:Удалить","М:Вставить","М:Получить",
						"С:Заполнить случайными числами", "С:Заполнить с клавиатуры", "С:Заполнить из файла", "С:Удалить","С:Вставить","С:Получить", "Выход" };
	const char* S3[] = { "Преобразование","Вычисление","Выход" };
	const char* S4[] = { "Заполнить случайными числами", "Заполнить с клавиатуры", "Заполнить из файла", "Удалить","Вставить","Получить","Выход" };
	system("cls");
	clearscreen(0, 0, 0);
	string str;
	int m = 0, l = 0,p, cf, ct,data;
	//количество
	int N = 0;
	int M = 0;
	//массивы
	student *stud = new student[N];
	int *X = new int[M];
	Branch *tree = 0;
	List Y;
	cf = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	ct = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
	do {
		m = goriz_menu(m, S, 5, 0, 20);
		switch (m)
		{
#pragma region Lab1
		case 0://лаб1
			l = vertical_menu(l, S1, 12, 1);//вызов подменю
			switch (l)
			{
			case 0://ввод с клавиатуры
				cout << "\nВведите значение N \n";
				cin >> N;
				stud = new student[N];
				keyboard_massiv(stud, N);
				break;
			case 1://печать
				print_massiv(stud, N);
				_getch();
				break;
			case 2://редактировать запись
				edit_massiv(stud, N);
				break;
			case 3://добавить запись
				add_massiv(stud, &N);
				break;
			case 4://Студенты группы N.N
				print_group(stud, N);
				_getch();
				break;
			case 5://топ 3
				print_top(stud, N);
				_getch();
				break;
			case 6://кол ж и м
				print_sex(stud, N);
				_getch();
				break;
			case 7://кол стпендиатов
				print_stip(stud, N);
				_getch();
				break;
			case 8://Не стип, Хор/отл
				print_scor(stud, N);
				_getch();
				break;
			case 9://Номер в списке 
				print_gr_num(stud, N);
				_getch();
				break;
			case 10://Дата
				print_date(stud, N);
				_getch();
				break;
			case 11:
				stud=file_in( &N);
				break;
			}
			break;
#pragma endregion
#pragma region Lab2
		case 1://лаб2
			l = vertical_menu(l, S2, 13, 1);//вызов подменю
			switch (l)
			{
#pragma region array
			case 0://Заполнить случайными числами
				random_massiv(X, &M);
				print_massiv(X, M);
				_getch();
				break;
			case 1://Заполнить с клавиатуры
				cout << "\n\nВведите значения: \n";
				X = keyboard_massiv(&M);
				print_massiv(X, M);
				_getch();
				break;
			case 2://Заполнить из файла
				X=file_input(&M);
				print_massiv(X, M);
				_getch();
				break;
			case 3://М:Удалить"
				deleteArray(X, &M);
				print_massiv(X, M);
				_getch();
				break;
			case 4://"М:Вставить"
				X=insertArray(X, &M);
				print_massiv(X, M);
				_getch();
				break;
			case 5://"М:Получить"
				readElement(X, M);
				_getch();
				break;
#pragma endregion
#pragma region List
			case 6://Заполнить случайными числами
				Y=random_list();
				print_list(Y);
				_getch();
				break;
			case 7://Заполнить с клавиатуры
				cout << "\n\nВведите значения: \n";
				Y = keyboard_list();
				print_list(Y);
				_getch();
				break;
			case 8://Заполнить из файла
				Y = file_list();
				print_list(Y);
				_getch();
				break;
			case 9://М:Удалить"
				deleteList(&Y);
				print_list(Y);
				_getch();
				break;
			case 10://"М:Вставить"
				insertList(&Y);
				print_list(Y);
				_getch();
				break;
			case 11://"М:Получить"
				readElementList(Y);
				print_list(Y);
				_getch();
				break;
			}
			break;
#pragma endregion
#pragma endregion
#pragma region Lab3

		case 2:
			
			l = vertical_menu(l, S3, 3, 1);//вызов подменю
			switch (l)
			{
			case 0://преобразование
				cout << "\nВыберите пункт: \n1.  ИН -> ПостН\n2. ИН -> ПрН\n";
				cin >> p;
				cout << "\nВведите выражение: \n";
				cin.ignore();
				getline(cin, str);
				p--;
				switch (p)
				{
				case 0:
					cout<<endl<<preToPost(infixToPrefix(str));
					file_save(preToPost(infixToPrefix(str)),"ПостН.txt");
					break;
				case 1:
					cout << endl << infixToPrefix(str);
					file_save(preToPost(infixToPrefix(str)),"ПрН.txt");
					break;
				default:
					cout << "\nНеверный ввод! \n";
					break;
				}
				_getch();
				break;
			case 1://вычисление
				cout << "\nВыберите пункт: \n1.  Инфиксная нотация\n2. Префиксная нотация\n3. Постфикстная нотация \n";
				cin >> p;
				cout << "\nВведите выражение: \n";
				cin.ignore();
				getline(cin, str);
				p--;
				result = "";
				switch (p)
				{
				case 0:
					OPN(preToPost(infixToPrefix(str)));
					break;
				case 1:
					OPN(preToPost(str));
					break;
				case 2:
					OPN(str);
					break;
				default:
					cout << "\nНеверный ввод! \n";
					break;
				}
				file_save(result,"result.txt");
				_getch();
				break;
			}
			break;

#pragma endregion
#pragma region lab4
		case 3:

			l = vertical_menu(l, S4, 7, 1);//вызов подменю
			switch (l)
			{
			case 0://случ. числа
				tree= random_tree();
				print_tree(tree);
				_getch();
				break;
			case 1://клавиатура
				tree = keyboard_tree();
				print_tree(tree);
				_getch();
				break;
			case 2://файл
				tree = file_input_tree();
				print_tree(tree);
				_getch();
				break;
				//"Удалить", , "Получить"
			case 3:
				cout << "\nВведите значение которое необходимо удалить: \n";
				cin >> data;
				start = std::clock();
				DeleteBranch(tree, data);
				time_create_keyboard = (std::clock() - start) / (double)CLOCKS_PER_SEC;
				cout << "\n\nСкорость: " << time_create_keyboard << endl;
				print_tree(tree);
				_getch();
				break;
			case 4://"Вставить"
				cout << "\nВведите значение которое необходимо вставить: \n";
				cin >> data;
				start = std::clock();
				Add(data,tree);
				time_create_keyboard = (std::clock() - start) / (double)CLOCKS_PER_SEC;
				cout << "\n\nСкорость: " << time_create_keyboard << endl;
				print_tree(tree);
				_getch();
				break;
			case 5:
				cout << "\nВведите значение которое необходимо найти: \n";
				cin >> data;
				start = std::clock();
				OutputBranch(tree, data);
				time_create_keyboard = (std::clock() - start) / (double)CLOCKS_PER_SEC;
				cout << "\n\nСкорость: " << time_create_keyboard << endl;
				_getch();
				break;
			}

#pragma endregion

		}
		system("cls");
		clearscreen(0, 0, 0);
		l = 0;
	} while (m!=4);
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
