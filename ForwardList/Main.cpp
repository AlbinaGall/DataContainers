//ForwardList
#include <iostream>
using namespace std;

template<typename T>

class ForwardList {
	class Element {
		static int count;
		T Data;		//значение эл-та
		Element* pNext; //адрес следующего эл-та
	public:
		Element(T Data, Element* pNext = nullptr) : Data(Data), pNext(pNext) {
			cout << "EConstructor:\t" << this << endl;
		}
		~Element() {
			cout << "EDestructor:\t" << this << endl;
		}
		friend class ForwardList;
	}* Head;	//голова списка - указывает на начальный элемент списка (нулевой)
	size_t size;
public:
	class Iterator{
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

	ForwardList(){
		//Конструктор по умолчанию - создает пустой список элементов
		Head = nullptr;
		size = 0;
		//Если голова указывает на ноль - список пуст(не содержит эл-тов)
		cout << "LConstructor:\t" << this << endl;


	}
	ForwardList(const initializer_list<T>& il) :ForwardList(){ //делегируем конструктор по умолчанию,
																//чтобы не создавать пустой список вручную
		cout << typeid(il.begin()).name()<<endl;
		for (T const* it = il.begin(); it != il.end(); it++) {
			this->push_back(*it);
		}
	}
	ForwardList(const ForwardList<T>& other) :ForwardList() {
		for ( Element* Temp = other.Head; Temp; Temp = Temp->pNext)	push_back(Temp->Data);
	}

	~ForwardList(){
		while (Head) pop_front();
		cout << "LDestructor:\t" << this << endl; 		
	}
	// Operators:
	ForwardList<T>& operator=(const ForwardList<T>& other){
		//1. Удаляем старое значeние объекта
		while (Head)pop_front();
		//2. Выполняем побитовое копирование
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)	push_back(Temp->Data);
		return *this;
	}
//    Adding elements
	void push_front(T Data) {
		//1. Создаем новый элемент:
		Element* New = new Element(Data);
		//2. Прикрепляем созданный элемент к списку
		New->pNext = Head;
		//3. Говорим, что новый элемент теперь начальный элемент списка
		Head = New;
		size++;
	}

	void push_back(T Data) {
		if (Head == nullptr) return	push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext) {
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Index,T Data) {
		if (Index == 0)return push_front(Data);
		if (Index >= size) return push_back(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}
// Removing Elements
	void pop_front() {
		//1.Запоминаем адрес удаляемого элемента
		Element* del = Head;
		//2.Исключаем элемент из списка
		Head = Head->pNext;
		//3.Удаляем элемент из памяти
		delete del;
		size--;
}
	void pop_back() {
		//1.Доходим до конца списка
		Element* Temp = Head;
		while (Temp->pNext->pNext)	Temp = Temp->pNext;
		//2.Удаляем элемнт из памяти
		delete Temp->pNext;
		//3. "Забываем" об удаленном элементе	
		Temp->pNext = nullptr;
		size--;
	}
	void print()const {
		Element* Temp = Head;
		/*while (Temp!=nullptr) {
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/
		for (Element* Temp = Head; Temp; Temp = Temp->pNext) {
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		}
		
		//cout << "Кол-во эл-тов списка: " << size << endl;
		//cout << "Общее кол-во эл-тов: " << Element::count << endl;
	}
};

#define delimiter  "\n----------------------------------------------------\n"
//#define BASE_CHECK

void main() {
	setlocale(LC_ALL, "Russian");
#ifdef BASE_CHECK
	int n; cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++) {
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	//list.push_back(123);
	list.print();
	//list.pop_front();
	//list.print();
	//list.pop_back();
	//list.print();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
#endif //BASE_CHECK
	ForwardList<int> list = { 3,5,8,13,21 };
	list.print();
	cout << delimiter << endl;
	for (int i : list) {
		cout << i << "\t";
	}
	cout << endl;
	cout << delimiter << endl;

	double arr[] = { 3.4,5.8,13.1,21.9 };
	for (int i = 0; i < sizeof(arr) / sizeof(double); i++) {
		cout << arr[i] << "\t";
	}
	cout << endl;
	/*for (ForwardList::Iterator it = list.begin(); it != list.end(); ++it) {
		cout << *it << endl;
	}
	cout << endl;
	cout << delimiter << endl;
	/*ForwardList list2 = list;
	list2.print();
	ForwardList list3;
	list3 = list2;
	list3.print();*/
}