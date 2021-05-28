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
//���������� �������� �������� �������
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
					cout << "\n�������� ���������!\n";
				else
				{
					int64_t num2 = stack_.back();
					stack_.pop_back();
					if (stack_.size() == 0)
						cout << "\n�������� ���������!\n";
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
	result+= "���������: " + std::to_string(stack_.back());
	std::cout <<endl<<"���������: "<< stack_.back();

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

//��������� ������� � �����������
string infixToPostfix(string infix)
{
	infix = '(' + infix + ')';
	int l = infix.size();
	stack<char> char_stack;
	string output_str="";

	for (int i = 0; i < l; i++) {

		// ���� ������
		// �������, �������� ��� � output_str.
		if (isalpha(infix[i]) || isdigit(infix[i]))
		{
			output_str += infix[i];
			output_str += " ";
		}

		// ���� ������
		// �(�, ��������� ��� � ����.
		else if (infix[i] == '(')
			char_stack.push('(');

		// ���� ������
		// �)�, ������� � �������� � output_str �� �����
		// ���� �� ���������� ������ "(".
		else if (infix[i] == ')') {
			while (char_stack.top() != '(') {
				output_str += char_stack.top();
				output_str += " ";
				char_stack.pop();
			}

			// ������� '(' �� �����
			char_stack.pop();
		}

		// �������� ������
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

				// �������� ������� �������� �  ����
				char_stack.push(infix[i]);
			}
		}
	}
	return output_str;
}


//��������� � ����������
string infixToPrefix(string infix)
{
	int l = infix.size();

	//  ������ ������
	reverse(infix.begin(), infix.end());

	// �������� (��) � ��������
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

	// ������
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

// ���������� � �����������
string preToPost(string pre_exp)
{

	stack<string> s;
	// ����� ������
	int length = pre_exp.size();
	int number = 0;
	bool flag;
	//������ ����� ������
	for (int i = length - 1; i >= 0; i--)
	{
		// �������� ��� ���
		if (isOperator(pre_exp[i]))
		{
			// ��������� ��� �������� � ����
			string op1 = s.top();
			s.pop();
			if (s.size() == 0)
			{
				cout << "������!";
				return "";
			}
			string op2 = s.top();
			s.pop();

			// ��������� ��������� � ��������
			string temp = op1+" " + op2 + " " + pre_exp[i] + " ";

			//��������� ������ � ����
			s.push(temp);
			flag = false;
		}

		// ���� ����� ��� �������  ��� ������
		else {
			if (pre_exp[i] == ' '&& flag == true)
				//��������� ������� � ����
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

	// �� ������ ����� � ����� �������� ������ ���������
	return s.top();
}


void file_save(string X,string name)
{
	ofstream output(name, std::ios::app);
	output << X<<endl;
	output.close();
}
