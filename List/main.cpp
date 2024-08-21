#include<iostream>

using namespace std;
#define tab "\t"

class List
{
	class Element
	{
		int Data;		
		Element* pNext;	
		Element* pPrev;	
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class List;
	}*Head, * Tail;	
	
	size_t size;	
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}

		//				Comparison operators:
		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
	}

		const int& operator*()const
		{
			return Temp->Data;
		}
		};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstIterator() {}

		ConstIterator& operator++()
		{
			//Prefix increment
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			//Suffix increment
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstReverseIterator() {}

		//				Increment/Decrement:
		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		int& operator*()
		{
			return Temp->Data;
		}
	};

	ConstIterator begin()const
	{
		return Head;
	}
	Iterator begin()
	{
		return Head;
	}

	ConstIterator end()const
	{
		return nullptr;
	}
	Iterator end()
	{
		return nullptr;
	}

	ConstReverseIterator rbegin()const
	{
		return Tail;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}

	ConstReverseIterator rend()const
	{
		return nullptr;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			//push_front(*it);
			push_back(*it);
		}
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "CopyConstructor:" << this << endl;
	}
	~List()
	{
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//						Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	//						Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			////1) Создаем новый элемент:
			//Element* New = new Element(Data);
			////2) Привязываем новый элемент к началу списка:
			//New->pNext = Head;
			////3) Привязываем головной элемент списка к новому элементу:
			//Head->pPrev = New;
			////4) Смещаем Голову на новый элемент:
			//Head = New;

			Head = Head->pPrev = new Element(Data, Head);
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			////1) Создаем новый элемент:
			//Element* New = new Element(Data);
			////2) Включаем новый элемент в список:
			//New->pPrev = Tail;
			//Tail->pNext = New;
			////3) Смещаем Хвост на новый элемент:
			//Tail = New;

			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		}
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > size)return;
		if (Index == 0)return push_front(Data);
		if (Index == size)return push_back(Data);
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}

		/*Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;*/

		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);

		size++;
	}

	//					Removing elements:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			//1) Смещаем Голову на следующий элемент:
			Head = Head->pNext;

			//2) Удаляем элемент 'Head->pPrev' из памяти:
			delete Head->pPrev;

			//3) Зануляем указатель 'Head->pPrev':
			Head->pPrev = nullptr;
		}
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
		}
		//if (Head == Tail)return pop_front();
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}

	//					Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов в списке: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов в списке: " << size << endl;
	}
};

List operator+(const List& left, const List& right)
{
	List buffer = left;
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		//*it *= 10;
	}
	return buffer;
}

//#define BASE_CHECK
//#define ITERATORS_CHECK
#define OPERATOR_PLUS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)cout << i << tab; cout << endl;

	//List::Iterator it;
	//const int jt = *it;

	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

#ifdef OPERATOR_PLUS_CHECK
	List list1 = { 3, 5, 8, 13, 21 };
	List list2 = { 34, 55, 89 };
	List list3 = list1 + list2;
	for (int i : list1) cout << i << tab; cout << endl;
	for (int i : list2) cout << i << tab; cout << endl;
	for (int i : list3) cout << i << tab; cout << endl;

	for (List::Iterator it = list3.begin(); it != list3.end(); ++it)
	{
		*it *= 100;
	}
	for (int i : list3) cout << i << tab; cout << endl;
#endif // OPERATOR_PLUS_CHECK

}