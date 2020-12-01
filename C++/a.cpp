#include <iostream>
#include <string>
using namespace std;

template<class T> class Node
{
public:
    T Value;
    Node* Next;
    Node(T v): Value(v), Next(0){}
};

template<class T> class List
{
    Node<T> *head, *tail;
    int count;
public:
    List():count(0){}
    ~List();

    void RemoveAll()
    {
        while (count)
        {
            --count;

            Node<T> *p = head;
            head = p->Next;
            delete p;
        }
    }

    void Add(T v)
    {
        Node<T> *p = new Node<T>(v);
        if (count++ == 0)
            head = p;
        else
            tail->Next = p;
        tail = p;
    }

    Node<T> *First() const {return head;}
    int Count() const {return count;}

    T* ToArray()
    {
        T* arr = new T[count];
        Node<T> *p = head;
        for (int i = 0; i < count; ++i, p = p->Next)
            arr[i] = p->Value;
        return arr;
    }
};

class Date
{
public:
    int Day, Month, Year;
    Date(){Day = Month = Year = 0;}
    Date(int, int, int);
    friend ostream& operator << (ostream&, const Date&);
};

class ThiSinh
{
public:
    Date NgaySinh;
    string HoTen;
    double Toan, Ly, Anh;
public:
    ThiSinh(){}
    ThiSinh(const char* hoTen, const Date ns, double toan, double ly, double anh);
    double Tong() const;
    double TB() const;
    friend ostream& operator << (ostream&, const ThiSinh&);
};

class ListThiSinh : public List<ThiSinh*>
{
public:
    ListThiSinh(ThiSinh **arr)
    {
        int i = 0;
        while (arr[i])
            this->Add(arr[i++]);
    }
};

// List
template<class T>
List<T>::~List()
{
    // List<T>::RemoveAll();
}

// Date
Date::Date(int year, int month, int day): Year(year), Month(month), Day(day){}
ostream& operator << (ostream& output, const Date& date)
{
    output << date.Day << "." << date.Month << "." << date.Year;
    return output;
}

// ThiSinh
ThiSinh::ThiSinh(const char* hoTen, const Date ns, double toan, double ly, double anh):
                                                                        HoTen(hoTen), NgaySinh(ns), Toan(toan), Ly(ly), Anh(anh) {}
double ThiSinh::Tong() const
{
    return Toan*2 + Ly + Anh;
}

double ThiSinh::TB() const
{
    return Tong() / 4;
}

ostream& operator << (ostream& output, const ThiSinh& thisinh)
{
    output << thisinh.HoTen << "\t" << thisinh.NgaySinh << "\t";
    output << thisinh.Toan << "\t" << thisinh.Ly << "\t" << thisinh.Anh << "\t";
    output << thisinh.Tong() << "\t" << thisinh.TB();
    return output;
}

void func3(ListThiSinh cacThiSinh)
{
    auto p = cacThiSinh.First();
    int soLuong = cacThiSinh.Count();

    int count = 0;
    for (int i = 0; i < soLuong; ++i, p = p->Next)
        if ((*p->Value).TB() >= 8)
            count++;
    cout << "Phan tram kha gioi: " << (double)count / soLuong <<endl;
}

void func2(ListThiSinh cacThiSinh)
{
    auto p = cacThiSinh.First();
    auto q = cacThiSinh.First();
    int soLuong = cacThiSinh.Count();

    for (int i = 0; i < soLuong-1; ++i, p = p->Next)
    {
        q = cacThiSinh.First();
        for (int j = 0; j <= i; ++j)
            q = q->Next;
        for (int j = i+1; j < soLuong; ++j, q = q->Next)
            if ((*p->Value).Tong() < (*q->Value).Tong())
            {
                auto temp = *p->Value;
                *p->Value = *q->Value;
                *q->Value = temp;
            }
    }

    p = cacThiSinh.First();
    for (int i = 0; i < soLuong; ++i, p = p->Next)
        cout << *p->Value <<endl;
}

int main()
{
    ThiSinh *arr[] = {
        new ThiSinh("Nguyen Thanh Son", Date(2020, 1, 15), 8, 7, 8),
        new ThiSinh("Tran Hai Nan", Date(2020, 10, 6), 9, 8, 6),
        new ThiSinh("Vu Duy Anh", Date(2020, 7, 31), 7, 10, 9),
        new ThiSinh("Hoang Anh Tuan", Date(2020, 12, 22), 3, 5, 7),
        new ThiSinh("Phung Ngoc Linh", Date(2020, 4, 5), 9, 9, 9),
        0
    };
    ListThiSinh cacThiSinh(arr);
    auto p = cacThiSinh.First();
    int soLuong = cacThiSinh.Count();
    cout <<soLuong;
    for (int i = 0; i < soLuong; ++i, p = p->Next)
        cout << *p->Value << endl;
    cout <<endl; func2(cacThiSinh); cout <<endl; func3(cacThiSinh);
    return 0;
}