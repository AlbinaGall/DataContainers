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

//#define ELEVATOR_CHECK

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

}