#include <iostream>
using namespace std;


int tabs = 0; //Для создания отступов
//Кол-во отступов высчитывается по кол-ву рекурсивного вхождения при выводе в фукцию print_tree

//Структура ветки
struct Branch
{
	int Data; //Поле данных
	Branch *LeftBranch; //УКАЗАТЕЛИ на соседние веточки
	Branch *RightBranch;
};


void file_output_tree(Branch* X);
//Функция внесения данных
void Add(int aData, Branch *&aBranch)
{
	//Если ветки не существует
	if (!aBranch)
	{ //создадим ее и зададим в нее данные
		aBranch = new Branch;
		aBranch->Data = aData;
		aBranch->LeftBranch = 0;
		aBranch->RightBranch = 0;
		return;
	}
	else //Иначе сверим вносимое
		if (aBranch->Data > aData)
		{ //Если оно меньше того, что в этой ветке - добавим влево
			Add(aData, aBranch->LeftBranch);
		}
		else
		{ //Иначе в ветку справа
			Add(aData, aBranch->RightBranch);
		};
}

//Функция вывода дерева
void print_tree(Branch *aBranch)
{
	if (!aBranch) return; //Если ветки не существует - выходим. Выводить нечего
	tabs++; //Иначе увеличим счетчик рекурсивно вызванных процедур
	//Который будет считать нам отступы для красивого вывода

	print_tree(aBranch->LeftBranch); //Выведем ветку и ее подветки слева

	for (int i = 0; i < tabs; i++) cout << "*"; //Потом отступы
	cout << aBranch->Data << endl; //Данные этой ветки


	print_tree(aBranch->RightBranch);//И ветки, что справа

	tabs--; //После уменьшим кол-во отступов
	return;
}

void FreeTree(Branch *aBranch)
{
	if (!aBranch) return;
	FreeTree(aBranch->LeftBranch);
	FreeTree(aBranch->RightBranch);
	delete aBranch;
	return;
}

//удаление
Branch* DeleteBranch(Branch* aBranch, int Data) {
	if (aBranch == NULL)
		return aBranch;

	if (Data == aBranch->Data) {

		Branch* tmp;
		if (aBranch->RightBranch == NULL)
			tmp = aBranch->LeftBranch;
		else {

			Branch* ptr = aBranch->RightBranch;
			if (ptr->LeftBranch == NULL) {
				ptr->LeftBranch = aBranch->LeftBranch;
				tmp = ptr;
			}
			else {

				Branch* pmin = ptr->LeftBranch;
				while (pmin->LeftBranch != NULL) {
					ptr = pmin;
					pmin = ptr->LeftBranch;
				}
				ptr->LeftBranch = pmin->RightBranch;
				pmin->LeftBranch = aBranch->LeftBranch;
				pmin->RightBranch = aBranch->RightBranch;
				tmp = pmin;
			}
		}

		delete aBranch;
		return tmp;
	}
	else if (Data < aBranch->Data)
		aBranch->LeftBranch = DeleteBranch(aBranch->LeftBranch, Data);
	else
		aBranch->RightBranch = DeleteBranch(aBranch->RightBranch, Data);
	if (aBranch->LeftBranch == NULL) { delete aBranch; return NULL; }
	return aBranch;
}

void OutputBranch(Branch* aBranch, int Data) {
	if (aBranch == NULL)
		return;

	if (Data == aBranch->Data) {

		if (aBranch->LeftBranch!=NULL)
		cout << "\t/"<< aBranch->LeftBranch->Data << endl;
		cout << aBranch->Data << endl;
		if (aBranch->RightBranch != NULL)
		cout << "\t\\" << aBranch->RightBranch->Data << endl;
		return;

	}
	else if (Data < aBranch->Data)
		OutputBranch(aBranch->LeftBranch, Data);
	else
		OutputBranch(aBranch->RightBranch, Data);
}


Branch *keyboard_tree()
{
	Branch *X = 0;
	int temp;
	string line;
	getline(cin, line);
	start = std::clock();
	char *currentWord = strtok(const_cast <char *> (line.c_str()), " ");
	while (currentWord) {
		temp = atoi(currentWord);
		Add(temp, X);
		currentWord = strtok(nullptr, " ");
	}
	time_create_keyboard = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\nСкорость: " << time_create_keyboard << endl;
	file_output_tree(X);
	return X;
}

Branch *random_tree()
{
	Branch *X = 0;
	int a = -99, b = 99, N;
	cout << "\n\nВведите N: ";
	cin >> N;
	int i;
	start = std::clock();
	for (i = 0; i < (N); i++)
	{
		Add((b - a) * (int)rand() / RAND_MAX + a, X);
	}
	time_create_random = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\nСкорость: " << time_create_random << endl;
	file_output_tree(X);
	return X;
}
Branch* file_input_tree()
{
	start = std::clock();
	string line;
	int temp;
	Branch *X = 0;
	ifstream in("array.txt");
	if (in.is_open())
	{
		while (getline(in, line))
		{
			char *currentWord = strtok(const_cast <char *> (line.c_str()), " ");
			while (currentWord) {
				temp = atoi(currentWord);
				Add(temp,X);
				currentWord = strtok(nullptr, " ");
			}

		}
	}
	in.close();		// закрываем файл
	time_create_infile = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\n\nСкорость: " << time_create_infile << endl;
	return X;
}

string tree_out;
void str_tree(Branch *aBranch)
{
	if (!aBranch) return; //Если ветки не существует - выходим. Выводить нечего
	tabs++; //Иначе увеличим счетчик рекурсивно вызванных процедур
	//Который будет считать нам отступы для красивого вывода

	str_tree(aBranch->LeftBranch); //Выведем ветку и ее подветки слева

	for (int i = 0; i < tabs; i++) tree_out+= "*"; //Потом отступы
	tree_out+=std::to_string(aBranch->Data); //Данные этой ветки
	tree_out += "\n";

	str_tree(aBranch->RightBranch);//И ветки, что справа

	tabs--; //После уменьшим кол-во отступов
	return;
}

void file_output_tree(Branch* X)
{
	tree_out = "";str_tree(X);
	ofstream output("tree.txt");
	output << tree_out;
	output.close();
}
