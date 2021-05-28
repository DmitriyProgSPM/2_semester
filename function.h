#pragma once

template <typename T>
T* createArray(T *Array, int N) //�������� ������������� �������
{
	return Array = new T[N];
}
template <typename T>
T * addElemet(T *Array, int N, T st) //���������� �������� � ����� �������
{
	T *temp = NULL;
	int numTemp = N + 1;
	temp = createArray(temp, numTemp); // ������� ��������� ������
	for (int i = 0; i < N; i++)
	{
		temp[i] = Array[i]; // �������� ������ �� ������� �������
	}
	temp[N] = st;
	return temp;
}
template <typename T>
T * copyArray(T *Array, int N)
{
	T *temp = NULL;
	temp = createArray(temp, N); // ������� ��������� ������
	for (int i = 0; i < N; i++)
	{
		temp[i] = Array[i]; // �������� ������ �� ������� �������
	}
	return temp;
}
