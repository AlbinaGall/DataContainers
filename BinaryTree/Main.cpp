//BinaryTree
#include <iostream>
using namespace std;

template<typename T>
class Tree {
	int count;
	class Element {
		T Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(T Data, Element* pLeft = nullptr, Element* pRight = nullptr) : Data(Data), pLeft(pLeft), pRight(pRight){
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
	int getCount() const {
		return count+1;
	}
	Tree() {
		this->Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	~Tree() {
		cout << "TDestructor:\t" << this << endl;
	}
	void insert(T Data, Element* Root) {
		if (this->Root == nullptr) {
			this->Root = new Element(Data);
			return;
			count++;
		}
		if (Root == nullptr)return;
		if (Data < Root->Data) {
			if (Root->pLeft == nullptr)
			{
				Root->pLeft = new Element(Data);
				count++;
			}
			else insert(Data, Root->pLeft);
		}

		if (Data > Root->Data) {
			if (Root->pRight)	insert(Data, Root->pRight); 
			else
			{
				Root->pRight = new Element(Data);
				count++;
			}
		}
	}
	void print(Element* Root)const {
		if (Root == nullptr) return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
	T MinValue(Element* Root)
	{
		if (Root->pLeft != nullptr) {
			return MinValue(Root->pLeft);
		}
		else {
			return Root->Data;
		}
	}
	T MaxValue(Element* Root)
	{
		if (Root->pRight != nullptr) {
			return MaxValue(Root->pRight);
		}
		else {
			return Root->Data;
		}
	}
	T Sum(Element* Root) {
		int left, right;
		if (Root != nullptr) {
			left = (Root->pLeft != nullptr) ? Sum(Root->pLeft) : 0;
			right = (Root->pRight != nullptr) ? Sum(Root->pRight) : 0;
			return left + right + Root->Data;
		}
		return 0;
	}

	double Avg(Element* Root) {
		return Sum(Root) / this->getCount();
	}
};

#define delimeter "\n/-----------------------------------------------------------------------------------/\n"

void main() {
	setlocale(LC_ALL, "");
	int size;
	cout << "Введите размер дерева: "; cin >> size;
	Tree<int> tree;
	for (int i = 0; i < size; i++) {
		tree.insert(rand() % 100, tree.getRoot());	//заполняем дерево случайными числами
	}
	tree.print(tree.getRoot()); cout << endl;
	cout << "Количество элементов в дереве: "<< tree.getCount() << endl;
	cout << "Минимальное значение: " << tree.MinValue(tree.getRoot()) << endl;
	cout << "Максимальное значение: " << tree.MaxValue(tree.getRoot()) << endl ;
	cout << "Сумма: " << tree.Sum(tree.getRoot()) << endl ;
	cout << "Среднее значение: " << tree.Avg(tree.getRoot()) << endl << delimeter;
//-----------------------------------------double----------------------------------------------
	Tree<double> tree2;
	for (int i = 0; i < size; i++) {
		tree2.insert((rand() % 100)*0.01, tree2.getRoot());	//заполняем дерево случайными числами
	}
	tree2.print(tree2.getRoot()); cout << endl;
	cout << "Количество элементов в дереве: " << tree2.getCount() << endl;
	cout << "Минимальное значение: " << tree2.MinValue(tree2.getRoot()) << endl;
	cout << "Максимальное значение: " << tree2.MaxValue(tree2.getRoot()) << endl;
	cout << "Сумма: " << tree2.Sum(tree2.getRoot()) << endl;
	cout << "Среднее значение: " << tree2.Avg(tree2.getRoot()) << endl << delimeter;
}