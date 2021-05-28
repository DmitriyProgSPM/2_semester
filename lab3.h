#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <cctype>
#include<stdio.h>
#include<stdlib.h>
#include <stack>

#pragma warning(disable:4996)
using namespace std;
string result;
//вычисление обратной польской нотации
void OPN(string expression)
{
	map<char, function<int64_t(const int64_t&, const int64_t&)>> operations;
	operations['+'] = [](const int64_t& a, const int64_t& b) constexpr { return a + b; };
	operations['-'] = [](const int64_t& a, const int64_t& b) constexpr { return a - b; };
	operations['*'] = [](const int64_t& a, const int64_t& b) constexpr { return a * b; };
	operations['/'] = [](const int64_t& a, const int64_t& b) constexpr { return a / b; };
	if (expression == "")
		return;
	vector<int64_t> stack_;
	int64_t number = 0;
	bool flag = true;
	for (const auto& i : expression)
	{
		if (isdigit(i))
		{
			number *= 10;
			number += (i - '0');
			flag = true;
		}
		else
		{
			if (i != ' ')
			{
				if (stack_.size() == 0)
					cout << "\nНеверное выражение!\n";
				else
				{
					int64_t num2 = stack_.back();
					stack_.pop_back();
					if (stack_.size() == 0)
						cout << "\nНеверное выражение!\n";
					int64_t num1 = stack_.back();
					stack_.pop_back();
					stack_.push_back(operations[i](num1, num2));
					result+= "\n" +std::to_string(num1) +i + std::to_string(num2) + '=' + std::to_string(operations[i](num1, num2)) +"\n";
					cout << "\n" << num1 << i << num2 << "=" << operations[i](num1, num2) << endl;
					flag = false;
				}
			}
			else if (i == ' ' && flag)
			{
				stack_.push_back(number);
				number = 0;
			}
		}
	}
	result+= "Результат: " + std::to_string(stack_.back());
	std::cout <<endl<<"Результат: "<< stack_.back();

}

bool isOperator_(char c)
{
	return (!isalpha(c) && !isdigit(c));
}

int getPriority(char C)
{
	if (C == '-' || C == '+')
		return 1;
	else if (C == '*' || C == '/')
		return 2;
	else if (C == '^')
		return 3;
	return 0;
}

//Инфиксная нотация в постфиксную
string infixToPostfix(string infix)
{
	infix = '(' + infix + ')';
	int l = infix.size();
	stack<char> char_stack;
	string output_str="";

	for (int i = 0; i < l; i++) {

		// Если символ
		// операнд, добавьте его в output_str.
		if (isalpha(infix[i]) || isdigit(infix[i]))
		{
			output_str += infix[i];
			output_str += " ";
		}

		// Если символ
		// ‘(‘, поместите его в стек.
		else if (infix[i] == '(')
			char_stack.push('(');

		// Если символ
		// ‘)’, удалить и добавить в output_str из стека
		// пока не встретится символ "(".
		else if (infix[i] == ')') {
			while (char_stack.top() != '(') {
				output_str += char_stack.top();
				output_str += " ";
				char_stack.pop();
			}

			// удалить '(' из стека
			char_stack.pop();
		}

		// оператор найден
		else {
			if (isOperator_(char_stack.top())) {
				while (
					(getPriority(infix[i])
						<= getPriority(char_stack.top()))
					|| (getPriority(infix[i])
						<= getPriority(char_stack.top())
						&& infix[i] == '^')) {
					output_str += char_stack.top() ;

					output_str += " ";
					char_stack.pop();
				}

				// добавить текущий оператор в  стек
				char_stack.push(infix[i]);
			}
		}
	}
	return output_str;
}


//инфиксная в префиксную
string infixToPrefix(string infix)
{
	int l = infix.size();

	//  реверс строки
	reverse(infix.begin(), infix.end());

	// Заменить (на) и наоборот
	for (int i = 0; i < l; i++) {

		if (infix[i] == '(') {
			infix[i] = ')';
			i++;
		}
		else if (infix[i] == ')') {
			infix[i] = '(';
			i++;
		}
	}

	string prefix = infixToPostfix(infix);

	// реверс
	reverse(prefix.begin(), prefix.end());

	return prefix;
}

bool isOperator(char x)
{
	switch (x) {
	case '+':
	case '-':
	case '/':
	case '*':
		return true;
	}
	return false;
}

// префиксная в постфиксную
string preToPost(string pre_exp)
{

	stack<string> s;
	// длина строки
	int length = pre_exp.size();
	int number = 0;
	bool flag;
	//читаем права налево
	for (int i = length - 1; i >= 0; i--)
	{
		// оператор или нет
		if (isOperator(pre_exp[i]))
		{
			// добавляем два операнда в стек
			string op1 = s.top();
			s.pop();
			if (s.size() == 0)
			{
				cout << "Ошибка!";
				return "";
			}
			string op2 = s.top();
			s.pop();

			// соединяем операторы и операнды
			string temp = op1+" " + op2 + " " + pre_exp[i] + " ";

			//добавляем строку в стек
			s.push(temp);
			flag = false;
		}

		// если сивол или операнд  или пробел
		else {
			if (pre_exp[i] == ' '&& flag == true)
				//добавляем операнд в стек
			{
				s.push(std::to_string(number));
				number = 0;
			}
			else if (isdigit(pre_exp[i]))
			{
				number *= 10;
				number += (pre_exp[i] - '0');
				flag = true;
			}
		}
	}

	// на данном этапе в стеке осталось только выражение
	return s.top();
}


void file_save(string X,string name)
{
	ofstream output(name, std::ios::app);
	output << X<<endl;
	output.close();
}
