//ForwardList
#include <iostream>
using namespace std;

template<typename T>

class ForwardList {
	class Element {
		static int count;
		T Data;		//�������� ��-��
		Element* pNext; //����� ���������� ��-��
	public:
		Element(T Data, Element* pNext = nullptr) : Data(Data), pNext(pNext) {
			cout << "EConstructor:\t" << this << endl;
		}
		~Element() {
			cout << "EDestructor:\t" << this << endl;
		}
		friend class ForwardList;
	}* Head;	//������ ������ - ��������� �� ��������� ������� ������ (�������)
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
		//����������� �� ��������� - ������� ������ ������ ���������
		Head = nullptr;
		size = 0;
		//���� ������ ��������� �� ���� - ������ ����(�� �������� ��-���)
		cout << "LConstructor:\t" << this << endl;


	}
	ForwardList(const initializer_list<T>& il) :ForwardList(){ //���������� ����������� �� ���������,
																//����� �� ��������� ������ ������ �������
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
		//1. ������� ������ ����e��� �������
		while (Head)pop_front();
		//2. ��������� ��������� �����������
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)	push_back(Temp->Data);
		return *this;
	}
//    Adding elements
	void push_front(T Data) {
		//1. ������� ����� �������:
		Element* New = new Element(Data);
		//2. ����������� ��������� ������� � ������
		New->pNext = Head;
		//3. �������, ��� ����� ������� ������ ��������� ������� ������
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
		//1.���������� ����� ���������� ��������
		Element* del = Head;
		//2.��������� ������� �� ������
		Head = Head->pNext;
		//3.������� ������� �� ������
		delete del;
		size--;
}
	void pop_back() {
		//1.������� �� ����� ������
		Element* Temp = Head;
		while (Temp->pNext->pNext)	Temp = Temp->pNext;
		//2.������� ������ �� ������
		delete Temp->pNext;
		//3. "��������" �� ��������� ��������	
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
		
		//cout << "���-�� ��-��� ������: " << size << endl;
		//cout << "����� ���-�� ��-���: " << Element::count << endl;
	}
};

#define delimiter  "\n----------------------------------------------------\n"
//#define BASE_CHECK

void main() {
	setlocale(LC_ALL, "Russian");
#ifdef BASE_CHECK
	int n; cout << "������� ������ ������: "; cin >> n;
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
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
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