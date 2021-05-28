#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
#define up 80
#define down 72
#define left1 75
#define right1 77
#define enter 13
#define esc 27
HPEN hPen, hOldPen;
HBRUSH hBrush, hOldBrush;
HANDLE hStdont;
CONSOLE_CURSOR_INFO cci1, cci;
COORD coord, cur;
DWORD Len, Wr;
WORD Attr;
int  nach, i;
char ch;
#define DX 20
#define DY 20

/*m-активный пункт меню, punkt - массив с пунктами меню, n - количество пунктов меню, 
l - начало меню по оси У, k - длина пункта меню */
int goriz_menu(int m, const char* punkt[], int n, int l, int k)//горизонтальное меню
{
	int  nach, i;
	char ch;
	hStdont = GetStdHandle(STD_OUTPUT_HANDLE);//дескриптор
	cci.bVisible = false;//скрываем курсор
	SetConsoleCursorInfo(hStdont, &cci);
	do {
		nach = 0;
		for (i = 0; i < n; i++)
		{
			Len = strlen(punkt[i]);//длина i пункта меню
			coord.X = nach;
			coord.Y = l;
			if (m == i)//активный пункт меню
				Attr = BACKGROUND_GREEN | BACKGROUND_INTENSITY; //яркозеленый
			else
				Attr = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED; //
			cur.X = nach;
			cur.Y = l;
			SetConsoleCursorPosition(hStdont, cur);
			cout<< punkt[i]; //название пункта меню
			FillConsoleOutputAttribute(hStdont, Attr, Len+1, coord, &Wr); //устанавливаем фон текста (цвет определен выше)
			nach += (Len + 1);//с какого момента по оси х начинает рисоваться пункт меню
		}
		ch = _getch();//код нажатой клавиши
		switch (ch)
		{//если влево
		case left1:if (m == 0)m = n - 1; //если активен первый пункт, то становится активным последний
				   else m--; break; //иначе на активным становится на один пункт левее
			//если право
		case right1:if (m == n - 1) m = 0;//если активен последний пункт, то становится активным левый
					else m++;//иначе на пункт правее
		}
	} while (ch != enter && ch != esc); //выполняется то тех пор пока не нажат esc или enter
	if (ch == esc) m = n - 1; // если нажат esc активным становится пункт меню выход
	DeleteObject(hStdont); //удаляем дескриптор 
	return m;//возвращаем m
}

/*m-активный пункт меню, punkt - массив с пунктами меню, n - количество пунктов меню,
nac - начало меню по оси У*/
int vertical_menu(int m, const char* punkt[], int n, int nac)//вертикальное меню
{

	hStdont = GetStdHandle(STD_OUTPUT_HANDLE);//дескриптор
	cci.bVisible = false;//скрываем курсор
	SetConsoleCursorInfo(hStdont, &cci1);
	do {
		nach = nac;
		for (i = 0; i < n; i++)
		{
			Len = strlen(punkt[i]);//длина текущего пункта меню
			coord.X = 0;//начало по оси Х
			coord.Y = nach;//начало по оси У
			if (m == i)//активный пункт меню
				Attr = BACKGROUND_GREEN | BACKGROUND_INTENSITY;//ярко зеленый
			else
				Attr = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED;
			cur.X = 0;
			cur.Y = nach;
			SetConsoleCursorPosition(hStdont, cur);
			cout<< punkt[i];//выводим пункт меню
			FillConsoleOutputAttribute(hStdont, Attr, 35, coord, &Wr);//утанавливаем фон
			nach++;
		}
		ch = _getch();//код клавиши
		switch (ch)
		{
		case down:if (m == 0)m = n - 1;//если активен первый - активным становится последний
				  else m--; break; //иначе на пункт выше
		case up:if (m == n - 1) m = 0; //если активен последний - активным становится первый
				else m++; //иначе на пункт ниже
		}
	} while (ch != enter && ch != esc); //пока не нажали enter или esc
	if (ch == esc) m = n - 1; //активным становится выход
	DeleteObject(hStdont);
	return m;
}


void clearscreen(int r, int g, int b) //очистка экрана
{
	HWND hwnd = GetConsoleWindow();//окно
	RECT rc; //Описывает ширину, высоту и расположение прямоугольника
	GetClientRect(hwnd, &rc);//извлекает координаты рабочей области окна
	HDC hdc = GetDC(hwnd);
	hPen = CreatePen(PS_SOLID, 4, RGB(r, g, b));
	hOldPen = (HPEN)SelectObject(hdc, hPen);
	hBrush = CreateSolidBrush(RGB(r, g, b));
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom); //рисуем прямоугольник по размеру экрана с заданным цветом
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}
