//BinaryTree2
#include <iostream>
using namespace std;

template<typename T>
class Tree {
	class Element {
		T Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(T Data, Element* pLeft = nullptr, Element* pRight = nullptr) : Data(Data), pLeft(pLeft), pRight(pRight) {
			cout << "EConstructor:\t" << this << endl;
		}
		~Element() {
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;

	}*Root;
public:
	Element* getRoot() const {
		return Root;
	}
	Tree() {
		this->Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree() {
		for (int const* it = il.begin(); it != il.end(); it++) {
			insert(*it, this->Root);
		}
	}
	~Tree() {
		clear(Root);
		cout << "TDestructor:\t" << this << endl;
	}
	void print()const {
		print(this->Root);
		cout << endl;
	}
	void insert(T Data) {
		insert(Data, Root);
	}
	void erase(T Data) {
		erase(Data, this->Root);
	}
	T MinValue() const {
		return MinValue(Root);
	}
	T MaxValue() const {
		return MaxValue(Root);
	}
	T Count()const {
		return Count(Root);
	}
	T Sum() const{
		return Sum(Root);
	}
	double Avg() const{
		return double(Sum(Root)) / Count(Root);
	}
private:
	void insert(T Data, Element* Root) {
		if (this->Root == nullptr) {
			this->Root = new Element(Data);
			return;
			//count++;
		}
		if (Root == nullptr)return;
		if (Data < Root->Data) {
			if (Root->pLeft == nullptr)
			{
				Root->pLeft = new Element(Data);
				//count++;
			}
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data) {
			if (Root->pRight)	insert(Data, Root->pRight);
			else
			{
				Root->pRight = new Element(Data);
				//count++;
			}
		}
		else if (Data == Root->Data) { return; }
	}
	void erase(T Data, Element*& Root) {
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data) {
			if (Root->pLeft == nullptr && Root->pRight == nullptr) {
				delete Root;
				Root = nullptr;
			}
			else {
				if (Count(Root->pLeft) > Count(Root->pRight)) {
					Root->Data = MaxValue(Root->pLeft);
					erase(MaxValue(Root->pLeft), Root->pLeft);
				}
				else {
					Root->Data = MinValue(Root->pRight);
					erase(MinValue(Root->pRight), Root->pRight);
				}

			}
		}

	}
	void clear(Element* Root) {
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}

	void print(Element* Root)const {
		if (Root == nullptr) return;
		print(Root->pLeft);
		cout << Root->Data << "\t"; //cout << endl;
		print(Root->pRight);
	}
	T MinValue(Element* Root)const	{
		return Root->pLeft ? MinValue(Root->pLeft) :Root->Data;
	}
	T MaxValue(Element* Root)const	{
		return Root->pRight ? MaxValue(Root->pRight) : Root->Data;
	}
	T Count(Element* Root)const {
		/*if (Root != nullptr) {
			return Count(Root->pLeft) + Count(Root->pRight)+ 1;
		}
		return 0;*/
		return Root ? Count(Root->pLeft) + Count(Root->pRight) + 1:0;
	}

	T Sum(Element* Root)const {
		/*if (Root != nullptr) {
			return Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
		}
		return 0;*/
		return !Root? 0: Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}

};

#define delimeter "\n/-----------------------------------------------------------------------------------/\n"
//#define BASE_CHECK

void main() {
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int size;
	cout << "Введите размер дерева: "; cin >> size;
	Tree<int> tree;
	for (int i = 0; i < size; i++) {
		tree.insert(rand() % 100); //tree.getRoot());	//заполняем дерево случайными числами
	}
	tree.print(); cout << endl;//tree.getRoot()); 
	cout << "Количество элементов в дереве: " << tree.Count() << endl;
	cout << "Минимальное значение: " << tree.MinValue() << endl;
	cout << "Максимальное значение: " << tree.MaxValue() << endl;
	cout << "Сумма: " << tree.Sum() << endl;
	cout << "Среднее значение: " << tree.Avg() << endl << delimeter;
	//-----------------------------------------double----------------------------------------------
	Tree<double> tree2;
	for (int i = 0; i < size; i++) {
		tree2.insert((rand() % 100) * 0.01);	//заполняем дерево случайными числами
	}
	tree2.print(); cout << endl;
	cout << "Количество элементов в дереве: " << tree2.Count() << endl;
	cout << "Минимальное значение: " << tree2.MinValue() << endl;
	cout << "Максимальное значение: " << tree2.MaxValue() << endl;
	cout << "Сумма: " << tree2.Sum() << endl;
	cout << "Среднее значение: " << tree2.Avg() << endl << delimeter;
#endif //BASE_CHECK
	Tree<int> tree = { 50,25,80,16,32,64,85,58,75,84,91 };//Идеально сбалансированное бинарное дерево
	tree.print();
	int value;
	cout << "Введите удаляемое значение: "; cin >> value;
	tree.erase(value);
	tree.print();
}