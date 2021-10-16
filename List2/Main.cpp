#include <iostream>
using namespace std;

class List
{
	class Element {
		//static int count;
		int Data;		//значение эл-та
		Element* pNext; //адрес следующего эл-та
		Element* pPrev; //адрес предыдущего элемента
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) : Data(Data), pNext(pNext), pPrev(pPrev) {
			//count++;
			cout << "EConstructor:\t" << this << endl;
		}
		~Element() {
			//count--;
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail;
	//int Element::count = 0;
	size_t size;
public:
	class Iterator {
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp) {
			cout << "ItConstructor: " << this << endl;
		}
		~Iterator() {
			cout << "ItDestructor: " << this << endl;

		}
		Iterator& operator++() {
			Temp = Temp->pNext;
			return *this;
		}
		bool operator==(const Iterator& other)const {
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const {
			return this->Temp != other.Temp;
		}
		int& operator*() {
			return Temp->Data;
		}
	};
	Iterator begin() { return this->Head; }
	Iterator end() { return nullptr; }

	class ReverseIterator {
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr) :Temp(Temp) {
			cout << "RevItConstructor: " << this << endl;
		}
		~ReverseIterator() {
			cout << "RevItDestructor: " << this << endl;

		}
		ReverseIterator& operator--() {
			Temp = Temp->pPrev;
			return *this;
		}
		bool operator==(const ReverseIterator& other)const {
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)const {
			return this->Temp != other.Temp;
		}
		int& operator*() {
			return Temp->Data;
		}
	};
	ReverseIterator rbegin() { return this->Head; }
	ReverseIterator rend() { return nullptr; }

	size_t get_size()const {
		return this->size;
	}
	List() {
		//Конструктор по умолчанию - создает пустой список элементов
		//Head=Tail=nullptr;
		Head = nullptr;
		Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}

	List(const initializer_list<int>& il) :List() { //делегируем конструктор по умолчанию,
													//чтобы не создавать пустой список вручную
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++) {
			this->push_back(*it);
		}
	}

	List(const List& other) :List() {
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)	push_back(Temp->Data);
	}
	
	~List() {
		while (Head) pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	// Operators:
	List& operator=(const List& other) {
		//1. Удаляем старое значние объекта
		while (Head)pop_front();
		//2. Выполняем побитовое копирование
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)	push_back(Temp->Data);
		return *this;
	}
	//    Adding elements
	void push_front(int Data) {
		if (Head == nullptr && Tail == nullptr) {
			Head = Tail = new Element(Data);
		}
		else {
			Element* New = new Element(Data);
			New->pNext = Head;
			Head->pPrev = New;
			Head = New;
		}
		size++;
	}

	void push_back(int Data) {
		if (Head == nullptr && Tail == nullptr) return	push_front(Data);
		Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
		size++;
	}
	void insert(int Index, int Data) {
		if (Index == 0)return push_front(Data);
		if (Index >= size) return push_back(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		New->pPrev = Temp->pPrev;
		Temp->pNext = New;
		size++;
	}
	// Removing Elements
	void pop_front() {
		Element* del = Head;
		Head = Head->pNext;
		delete del;
		size--;
	}
	void pop_back() {
		Element* Temp = Head;
		while (Temp->pNext->pNext)	Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void erase(int Index) {
		if (Index == 0)return pop_front();
		if (Index >= size) return pop_back();
		Element* Temp = Head;
		Temp->pNext = Temp->pNext->pNext;
		for (int i = 0; i < Index - 1; i++) delete Temp;
		size--;
	}
	//Вывод элементов на экран
	void print()const {
		Element* Temp = Head;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext) {
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		}
		cout << "Кол-во эл-тов списка: " << size << endl;
	}
	void reverse_print()const {
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev) {
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		}
		cout << "Кол-во эл-тов списка: " << size << endl;
	}
};



void main() {
	setlocale(LC_ALL, "Russian");

	/*int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++) {
		list.push_front(rand() % 100);
	}
	list.print();
	list.reverse_print();
	/*list.push_front(111);
	list.print();
	list.reverse_print();
	list.push_back(9999);
	list.print();
	list.reverse_print();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index,value);
	list.print();
	list.reverse_print();
	list.pop_back();
	list.print();
	int index;
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();*/

	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		cout << arr[i] << "\t";
	}
	cout << endl;

	
	for (int i = (sizeof(arr) / sizeof(int)); i >0 ; i--) {
		cout << arr[i] << "\t";
	}
	cout << endl;
	
	//for (type i : container){
		//i - итератор
	//	cout<<i<<"\t";
	//}
	List list = { 0, 1, 2, 3, 5, 8, 13, 21 };
	for (int i : list) {
		cout << i << "\t";
	}
	cout << endl;

}