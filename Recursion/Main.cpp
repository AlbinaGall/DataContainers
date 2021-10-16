#include <iostream>
#include<conio.h>
using namespace std;

#define VK_UP 72
#define VK_DOWN 80

void elevator_down(int level) {
	//условие выхода
	if (level == 0)return;
	cout << level<< " этаж" << endl;
	elevator_down(level - 1);//Рекурсивный вызов
}

void elevator_up(int level) {
	//условие выхода
	if (level == 0)return;
	elevator_up(level - 1);//Рекурсивный вызов
	cout << level << " этаж" << endl;
}

//#define ELEVATOR_CHECK

void main() {
	setlocale(LC_ALL, "Russian");
	//cout << "Hello, World!";
	//main();//рекурсивный вызов ф-ии main() неуправляемый и бесконечный
#ifdef ELEVATOR_CHECK
	int n, dir=0;
	cout << "\nВыберете направление поездки стрелками вверх или вниз: "; dir=_getch();cout << _getch();
	if (dir == VK_UP) {
		cout << "\nВведите номер этажа: "; cin >> n;
		elevator_up(n);
	}
	else if(dir==VK_DOWN) {
		cout << "\nВведите номер этажа: "; cin >> n;
		elevator_down(n);
	}
#endif	//ELEVATOR_CHECK

}