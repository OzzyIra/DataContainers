#include <iostream>
using namespace std;

#define tab "\t"
#define delimeter "\n-----------------------------------------\n"

class Element
{
    int Data;
    Element* pNext;
    static int count;
public:
    Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
    {
        count++;
        cout << "Econstructor\t" << this << endl;
    }
    ~Element()
    {
        count--;
        cout << "DEconstructor\t" << this << endl;
    }
    friend class Iterator;
    friend class ForwardList;
};
int Element::count = 0;
class Iterator
{
    Element* Temp;
public:
    Iterator(Element* Temp) :Temp(Temp)
    {
        cout << "IConstructor:\t" << this << endl;
    }
    ~Iterator()
    {
        cout << "IDestructor:\t" << this << endl;
    }
    Iterator& operator++()
    {
        Temp = Temp->pNext;
        return *this;
    }
    Iterator operator++(int)
    {
        Iterator old = *this;
        Temp = Temp->pNext;
        return old;
    }
    bool operator==(const Iterator& other)const
    {
        return this->Temp == other.Temp;
    }
    bool operator!=(const Iterator& other)const
    {
        return this->Temp != other.Temp;
    }
    int operator*()const
    {
        return Temp->Data;
    }
    int& operator*()
    {
        return Temp->Data;
    }
};


class ForwardList
{
    Element* Head;
    int size;
public:
    Iterator begin()
    {
        return Head;
    }
    Iterator end()
    {
        return nullptr;
    }
    int get_size()const
    {
        return size;
    }
    ForwardList()
    {
        size = 0;
        Head = nullptr;
        cout << "LConstructor" << this << endl;
    }
    explicit ForwardList(int size) :ForwardList()
    {
        while (size--)push_front(0);
    }
    ForwardList(const ForwardList& other) :ForwardList()
    {
        cout << "CopyConstructor\t" << this << endl;
        *this = other;
    }
    ForwardList(ForwardList&& other) :ForwardList()
    {
        *this = std::move(other);
        cout << "MoveConstructor:\t" << this << endl;
    }
    ForwardList(const initializer_list<int>& il):ForwardList()
    {
        for (const int* it = il.begin(); it != il.end(); it++)
        {
            push_back(*it);
        }

    }
    ~ForwardList()
    {
        while (Head)pop_front();
        cout << "DLConstructor" << this << endl;
    }
    //          Operators
    ForwardList& operator=(const ForwardList& other)
    {
        if (this == &other)return *this;
        this->~ForwardList();
        for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
            push_back(Temp->Data);
        cout << "CopyAssignment\t" << this << endl;
        return *this;
    }
    ForwardList& operator=(ForwardList&& other)
    {
        if (this == &other)return *this;
        this->~ForwardList();
        this->Head = other.Head;
        this->size = other.size;
        other.Head = nullptr;
        other.size = 0;
        cout << "MoveAssignment:\t" << this << endl;
    }
    
    const  int& operator[](int index)const
    {
        Element* Temp = Head;
        for (int i = 0; i < index; i++)Temp = Temp->pNext;
        return Temp->Data;
    }
    int& operator[](int index)
    {
        Element* Temp = Head;
        for (int i = 0; i < index; i++)Temp = Temp->pNext;
        return Temp->Data;
    }
    //      Adding elements
    void push_front(int Data)
    {
       Head = new Element(Data, Head);
        size++;
    }

    void push_back(int Data)
    {
        if (Head == nullptr)return push_front(Data);
       // Element* New = new Element(Data);
        Element* Temp = Head;
        while (Temp->pNext) Temp = Temp->pNext;
        Temp == nullptr;
        Temp->pNext = new Element(Data);
        size++;
    }
    //      Removing elements
    void pop_front()
    {
        if (Head == nullptr)return;
        Element* Erased = Head;
        Head = Head->pNext;
        delete Erased;
        size--;
    }
    void pop_back()
    {
        
        if (Head == nullptr)return pop_front();
        Element* Temp = Head;
        while (Temp->pNext->pNext)Temp = Temp->pNext;
        delete Temp->pNext;
        Temp->pNext = nullptr;
        size--;
    }

    void insert(int index,int Data)
    {
        if (index > size)
        {
            cout << "Error:out of range" << endl;
            return;
        }
        if (index == 0)return push_front(Data);
 
        Element* Temp = Head;
        for (int i = 0; i < index - 1; i++)
        {
            if (Temp->pNext == nullptr)break;
            Temp = Temp->pNext;
        }
        /*New->pNext = Temp->pNext;
        Temp->pNext = New;*/
        Temp->pNext = new Element(Data, Temp->pNext);
        size++;  
    }
  
    //      Methods
    void print()const
    {  
        //Element* Temp = Head; //Temp - итератор
        //while (Temp)
        //{
        //    cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
        //    Temp = Temp->pNext;      //переход на следующий элемент
        //    cout << "Количество элементов списка" << size << endl;
        //    cout << "Общее количество элементов" << Element::count<<endl;
        //}
        for (Element* Temp = Head; Temp; Temp->pNext)
        {
            cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
        }
        cout << "Количество элементов списка" << size << endl;
        cout << "Общее количество элементов" << Element::count<<endl;
    }
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
    ForwardList buffer = left;
    //for (int i = 0; i < left.get_size(); i++)buffer.push_back(left[i]);
    for (int i = 0; i < right.get_size(); i++)buffer.push_back(right[i]);
    return buffer;
}

void print(int arr[])
{
    cout << typeid(arr).name() << endl;
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        cout << arr[i] << tab;
    }
    cout << endl;
}
//#define BASE_CHECK
//#define COUNT_CHECK
//#define SIZE_CONSTRUCTOR_CHECK
//#define OPERATOR_PLUS_CHECK
//#define INITIALIZER_LIST_CONSTRUCTOR_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST
void main()
{
    setlocale(LC_ALL, "Russian");
#ifdef BASE_CHECK
    int n;
    cout << "Введите количество элементов списка"; cin >> n;
    ForwardList List;
    for (int i = 0; i < n; i++)
    {
        List.push_front(rand() % 100);
    }
    List.print();
    List.push_back(123);
    int index, int value;
    cout << "Напишите интекс добавляемого эелемента"; cin >> index;
    cout << "Напишите  значение добавляемого элемента"; cin >> value;
    List.insert(index, value);
    List.print();
#endif // BASE_CHECK
#ifdef COUNT_CHECK
    ForwardList list1;
    list1.push_back(3);
    list1.push_back(5);
    list1.push_back(8);
    list1.push_back(13);
    list1.push_back(21);
    list1.print();

    ForwardList list2;
    list2.push_back(34);
    list2.push_back(55);
    list2.push_back(89);
    list2.print();
#endif // COUNT_CHECK
#ifdef SIZE_CONSTRUCTOR_CHECK
    ForwardList list(5);
    for (int i = 0; i < list.get_size(); i++)
    {
        list[i] = rand() % 100;
    }
    for (int i = 0; i < list.get_size(); i++)
    {
        cout << list[i] << tab;
    }
#endif // SIZE_CONSTRUCTOR_CHECK
#ifdef OPERATOR_PLUS_CHECK
    ForwardList list1;
    list1.push_back(3);
    list1.push_back(5);
    list1.push_back(8);
    list1.push_back(13);
    list1.push_back(21);
    list1.print();

    ForwardList list2;
    list2.push_back(34);
    list2.push_back(55);
    list2.push_back(89);
    list2.print();

    cout << delimeter << endl;
    //ForwardList list3 = list1 + list2;	//CopyConstructor
    cout << delimeter << endl;
    ForwardList list3;
    cout << delimeter << endl;
    list3 = list1 + list2;	//CopyAssignment
    cout << delimeter << endl;
    list3.print();
#endif // OPERATOR_PLUS_CHECK
#ifdef INITIALIZER_LIST_CONSTRUCTOR_CHECK
    ForwardList list1 = { 3,5,8,13,21 };
    list1.print();

#endif // INITIALIZER_LIST_CONSTRUCTOR_CHECK
#ifdef RANGE_BASED_FOR_ARRAY
    int arr[] = { 3, 5, 8, 13, 21 };
    //int* arr = new int[5] {3, 5, 8, 13, 21};
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        cout << arr[i] << tab;
    }
    cout << endl;

    //Range-based for:
    for (int i : arr)
    {
        cout << i << tab;
    }
    cout << endl;

    cout << typeid(arr).name() << endl;
    print(arr);
    //delete[] arr;  
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
    ForwardList list = { 3, 5, 8, 13, 21 };
    //list.print();
    for (int i : list)
    {
        cout << i << tab;
    }
    cout << endl;
    for (Iterator it = list.begin(); it != list.end(); ++it)
    {
        cout << *it << tab;
    }
    cout << endl;
#endif // RANGE_BASED_FOR_LIST

    
}