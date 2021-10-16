//Recurtion
#include <iostream>
#include<conio.h>
using namespace std;

#define VK_UP 72
#define VK_DOWN 80

void elevator_down(int level) {
	//������� ������
	if (level == 0)return;
	cout << level<< " ����" << endl;
	elevator_down(level - 1);//����������� �����
}

void elevator_up(int level) {
	//������� ������
	if (level == 0)return;
	elevator_up(level - 1);//����������� �����
	cout << level << " ����" << endl;
}

int factorial(int n) {
	if (n == 0)return 1;
	for (int i = 1; i <= n; i++)
	{
		return  n * factorial(n-1);
	}
}

int power(int base, int exponent) {
	if (base == 0 && exponent == 0)return 0; 
	else if (base == 0 && exponent != 0)return 0; 
	else if  (exponent == 0) return 1; 
	for (int i = 0; i < exponent; i++)
	{
		return base * power(base, exponent - 1);;
	}
}

//#define ELEVATOR_CHECK
#define FACTORIAL_AND_POWER

void main() {
	setlocale(LC_ALL, "Russian");
	//cout << "Hello, World!";
	//main();//����������� ����� �-�� main() ������������� � �����������
#ifdef ELEVATOR_CHECK
	int n, dir=0;
	cout << "\n�������� ����������� ������� ��������� ����� ��� ����: "; dir=_getch();cout << _getch();
	if (dir == VK_UP) {
		cout << "\n������� ����� �����: "; cin >> n;
		elevator_up(n);
	}
	else if(dir==VK_DOWN) {
		cout << "\n������� ����� �����: "; cin >> n;
		elevator_down(n);
	}
#endif	//ELEVATOR_CHECK

#ifdef FACTORIAL_AND_POWER
	int n, exponent;
	cout << "������� ����� �����: "; cin >> n;
	cout << "��������� " << n << " �����: " << factorial(n) << endl;

	cout << "������� ����� (���������� �������): "; cin >> exponent;
	cout << "���������: " <<  power(n,exponent) << endl;
#endif //FACTORIAL_AND_POWER
}