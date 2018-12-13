// Chap14
/*	Ŭ���� ���ø� Ư��ȭ
	- Ư�� �ڷ��� ������� ������ ��ü�� ���� ���� ó�� 
		templete <>
		class SoSimple<int>
		{};			
	- �κ� Ư��ȭ�� �����ϴ� 
		���� templete <typename T1, typename T2> �ε�
		templete <typename T1>
		class Mysimple<T1, double>			// T2�� ���ؼ� double ����ó�� 
		{};							*/
#if 0
#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
class Point
{
private:
	T xpos, ypos;
public:
	Point(T x = 0, T y = 0) : xpos(x), ypos(y)
	{  }
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}
};

template <typename T>
class SimpleDataWrapper
{
private:
	T mdata;
public:
	SimpleDataWrapper(T data) : mdata(data)
	{ }
	void ShowDataInfo(void)
	{
		cout << "Data: " << mdata << endl;
	}
};

template<>
class SimpleDataWrapper <char*>
{
private:
	char* mdata;
public:
	SimpleDataWrapper(char* data)
	{
		mdata = new char[strlen(data) + 1];
		strcpy_s(mdata, strlen(data) + 1, data);
	}
	void ShowDataInfo(void)
	{
		cout << "String: " << mdata << endl;
		cout << "Length: " << strlen(mdata) << endl;
	}
	~SimpleDataWrapper()
	{
		delete[]mdata;
	}
};

template<>
class SimpleDataWrapper <Point<int>>
{
private:
	Point<int> mdata;
public:
	SimpleDataWrapper(int x, int y) : mdata(x, y)
	{ }
	void ShowDataInfo(void)
	{
		mdata.ShowPosition();
	}
};

int main(void)
{
	SimpleDataWrapper<int> iwrap(170);
	iwrap.ShowDataInfo();

	SimpleDataWrapper<char*> swrap("Class Template Specialization");
	swrap.ShowDataInfo();

	SimpleDataWrapper<Point<int>> poswrap(3, 7);
	poswrap.ShowDataInfo();
	return 0;
}

#elif 0
#include <iostream>
using namespace std;

template <typename T1, typename T2>
class MySimple
{
public:
	void WhoAreYou()
	{
		cout << "size of T1: " << sizeof(T1) << endl;
		cout << "size of T2: " << sizeof(T2) << endl;
		cout << "<typename T1, typename T2>" << endl;
	}
};

template<>
class MySimple<int, double>
{
public:
	void WhoAreYou()
	{
		cout << "size of int: " << sizeof(int) << endl;
		cout << "size of double: " << sizeof(double) << endl;
		cout << "<int, double>" << endl;
	}
};


template<typename T1>
class MySimple<T1, double>
{
public:
	void WhoAreYou()
	{
		cout << "size of T1: " << sizeof(T1) << endl;
		cout << "size of double: " << sizeof(double) << endl;
		cout << "<T1, double>" << endl;
	}
};


int main(void)
{
	MySimple<char, double> obj1;
	obj1.WhoAreYou();
	MySimple<int, long> obj2;
	obj2.WhoAreYou();
	MySimple<int, double> obj3;
	obj3.WhoAreYou();
	return 0;
}
#endif

//	14-3	; ���ø�����
/*	<typename T1, typename T2>  ... ����
	T1, T2 ���� ���ø� �Ű������� �ϰ�, 
	�Ű������� ���ԵǴ� �ڷ��� ������ '���ø� ����' �� �Ѵ�. �̴� ���ó�� ���� �� �ִ�. 
	�� ���ø� ���ڸ� ���� ���޵Ǵ� ����� ���ؼ� ���� �ٸ� ���� Ŭ������ �����ǰ� �� �� �ְ�, 
		���� �ٸ� ���� Ŭ���������� ���Թ� ���� ������ ���� �� �ִ�
		ex) 5iarr1 = i7arr1; �Ұ��� �ֳĸ�, ���� �ٸ��� Ŭ������ ���� �Ҵ� ������ �������� �ʾҴ�. */
#if 0
#include <iostream>
using namespace std;

template <typename T, int len>
class SimpleArray
{
private:
	T arr[len];
public:

	T& operator[] (int idx)
	{
		return arr[idx];
	}
	T& operator=(const T&ref)
	{
		for (int i = 0; i<len; i++)
			arr[i] = ref.arr[i];
	}
};

int main(void)
{
	SimpleArray<int, 5> i5arr1;
	for (int i = 0; i<5; i++)
		i5arr1[i] = i * 10;

	SimpleArray<int, 5> i5arr2;
	i5arr2 = i5arr1;
	for (int i = 0; i<5; i++)
		cout << i5arr2[i] << ", ";
	cout << endl;

	SimpleArray<int, 7> i7arr1;
	for (int i = 0; i<7; i++)
		i7arr1[i] = i * 10;

	SimpleArray<int, 7> i7arr2;
	i7arr2 = i7arr1;
	for (int i = 0; i<7; i++)
		cout << i7arr2[i] << ", ";
	cout << endl;
	return 0;
}

#endif 

/*	�Լ� ���ø��� static ����	
	�ѹ� �ʱ�ȭ�� ���¿��� �װ��� ��� �����ϴ� static ������ Ư���� 
	���� �ٸ� templete �� ���ؼ� ������ �ȴ�. */
#if 0
#include <iostream>
using namespace std;

template <typename T>
void ShowStaticValue(void)
{
	static T num = 0;
	num += 1;
	cout << num << " ";
}

int main(void)
{
	ShowStaticValue<int>();
	ShowStaticValue<int>();
	ShowStaticValue<int>();
	cout << endl;

	ShowStaticValue<long>();
	ShowStaticValue<long>();
	ShowStaticValue<long>();
	cout << endl;

	ShowStaticValue<double>();
	ShowStaticValue<double>();
	ShowStaticValue<double>();
	return 0;
}
#endif

/*	Ŭ���� ���ø��� static ����		
	���� �ٸ� Ŭ���� ���� �ϳ��� static ������ �����ϰ� �ȴ�.*/
#if 0
#include <iostream>
using namespace std;

template <typename T>
class SimpleStaticMem
{
private:
	static T mem;

public:
	void AddMem(int num) { mem += num; }
	void ShowMem() { cout << mem << endl; }
};

template <typename T>
T SimpleStaticMem<T>::mem = 0;

/*
// ����ó�� (Ư��ȭ)
template<>
long SimpleStaticMem<long>::mem=5;
*/

int main(void)
{
	SimpleStaticMem<int> obj1;
	SimpleStaticMem<int> obj2;
	obj1.AddMem(2);
	obj2.AddMem(3);
	obj1.ShowMem();

	SimpleStaticMem<long> obj3;
	SimpleStaticMem<long> obj4;
	obj3.AddMem(100);
	obj4.ShowMem();
	return 0;
}


#endif 