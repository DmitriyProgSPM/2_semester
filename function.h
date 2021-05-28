#pragma once

template <typename T>
T* createArray(T *Array, int N) //создание динамического массива
{
	return Array = new T[N];
}
template <typename T>
T * addElemet(T *Array, int N, T st) //добавление элемента в конец массива
{
	T *temp = NULL;
	int numTemp = N + 1;
	temp = createArray(temp, numTemp); // создаем временный массив
	for (int i = 0; i < N; i++)
	{
		temp[i] = Array[i]; // копируем данные со старого массива
	}
	temp[N] = st;
	return temp;
}
template <typename T>
T * copyArray(T *Array, int N)
{
	T *temp = NULL;
	temp = createArray(temp, N); // создаем временный массив
	for (int i = 0; i < N; i++)
	{
		temp[i] = Array[i]; // копируем данные со старого массива
	}
	return temp;
}
