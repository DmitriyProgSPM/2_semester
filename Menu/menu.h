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

/*m-�������� ����� ����, punkt - ������ � �������� ����, n - ���������� ������� ����, 
l - ������ ���� �� ��� �, k - ����� ������ ���� */
int goriz_menu(int m, const char* punkt[], int n, int l, int k)//�������������� ����
{
	int  nach, i;
	char ch;
	hStdont = GetStdHandle(STD_OUTPUT_HANDLE);//����������
	cci.bVisible = false;//�������� ������
	SetConsoleCursorInfo(hStdont, &cci);
	do {
		nach = 0;
		for (i = 0; i < n; i++)
		{
			Len = strlen(punkt[i]);//����� i ������ ����
			coord.X = nach;
			coord.Y = l;
			if (m == i)//�������� ����� ����
				Attr = BACKGROUND_GREEN | BACKGROUND_INTENSITY; //�����������
			else
				Attr = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED; //
			cur.X = nach;
			cur.Y = l;
			SetConsoleCursorPosition(hStdont, cur);
			cout<< punkt[i]; //�������� ������ ����
			FillConsoleOutputAttribute(hStdont, Attr, Len+1, coord, &Wr); //������������� ��� ������ (���� ��������� ����)
			nach += (Len + 1);//� ������ ������� �� ��� � �������� ���������� ����� ����
		}
		ch = _getch();//��� ������� �������
		switch (ch)
		{//���� �����
		case left1:if (m == 0)m = n - 1; //���� ������� ������ �����, �� ���������� �������� ���������
				   else m--; break; //����� �� �������� ���������� �� ���� ����� �����
			//���� �����
		case right1:if (m == n - 1) m = 0;//���� ������� ��������� �����, �� ���������� �������� �����
					else m++;//����� �� ����� ������
		}
	} while (ch != enter && ch != esc); //����������� �� ��� ��� ���� �� ����� esc ��� enter
	if (ch == esc) m = n - 1; // ���� ����� esc �������� ���������� ����� ���� �����
	DeleteObject(hStdont); //������� ���������� 
	return m;//���������� m
}

/*m-�������� ����� ����, punkt - ������ � �������� ����, n - ���������� ������� ����,
nac - ������ ���� �� ��� �*/
int vertical_menu(int m, const char* punkt[], int n, int nac)//������������ ����
{

	hStdont = GetStdHandle(STD_OUTPUT_HANDLE);//����������
	cci.bVisible = false;//�������� ������
	SetConsoleCursorInfo(hStdont, &cci1);
	do {
		nach = nac;
		for (i = 0; i < n; i++)
		{
			Len = strlen(punkt[i]);//����� �������� ������ ����
			coord.X = 0;//������ �� ��� �
			coord.Y = nach;//������ �� ��� �
			if (m == i)//�������� ����� ����
				Attr = BACKGROUND_GREEN | BACKGROUND_INTENSITY;//���� �������
			else
				Attr = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED;
			cur.X = 0;
			cur.Y = nach;
			SetConsoleCursorPosition(hStdont, cur);
			cout<< punkt[i];//������� ����� ����
			FillConsoleOutputAttribute(hStdont, Attr, 35, coord, &Wr);//������������ ���
			nach++;
		}
		ch = _getch();//��� �������
		switch (ch)
		{
		case down:if (m == 0)m = n - 1;//���� ������� ������ - �������� ���������� ���������
				  else m--; break; //����� �� ����� ����
		case up:if (m == n - 1) m = 0; //���� ������� ��������� - �������� ���������� ������
				else m++; //����� �� ����� ����
		}
	} while (ch != enter && ch != esc); //���� �� ������ enter ��� esc
	if (ch == esc) m = n - 1; //�������� ���������� �����
	DeleteObject(hStdont);
	return m;
}


void clearscreen(int r, int g, int b) //������� ������
{
	HWND hwnd = GetConsoleWindow();//����
	RECT rc; //��������� ������, ������ � ������������ ��������������
	GetClientRect(hwnd, &rc);//��������� ���������� ������� ������� ����
	HDC hdc = GetDC(hwnd);
	hPen = CreatePen(PS_SOLID, 4, RGB(r, g, b));
	hOldPen = (HPEN)SelectObject(hdc, hPen);
	hBrush = CreateSolidBrush(RGB(r, g, b));
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom); //������ ������������� �� ������� ������ � �������� ������
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}
