// Chap14
/*	클래스 템플릿 특수화
	- 특정 자료형 기반으로 생성된 객체에 대해 예외 처리 
		templete <>
		class SoSimple<int>
		{};			
	- 부분 특수화도 가능하다 
		원래 templete <typename T1, typename T2> 인데
		templete <typename T1>
		class Mysimple<T1, double>			// T2에 대해서 double 예외처리 
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

//	14-3	; 템플릿인자
/*	<typename T1, typename T2>  ... 에서
	T1, T2 등을 템플릿 매개변수로 하고, 
	매개변수에 대입되는 자료형 정보를 '템플릿 인자' 라 한다. 이는 상수처림 쓰일 수 있다. 
	※ 템플릿 인자를 통해 전달되는 상수를 통해서 서로 다른 형의 클래스가 생성되게 할 수 있고, 
		서로 다른 형의 클래스끼리의 대입및 복사 연산을 막을 수 있다
		ex) 5iarr1 = i7arr1; 불가능 왜냐면, 서로 다른형 클래스에 대한 할당 연산자 정의하지 않았다. */
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

/*	함수 템플릿과 static 변수	
	한번 초기화된 상태에서 그값을 계속 유지하는 static 변수의 특성이 
	각각 다른 templete 에 대해서 적용이 된다. */
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

/*	클래스 템플릿과 static 변수		
	각각 다른 클래스 마다 하나씩 static 변수를 공유하게 된다.*/
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
// 예외처리 (특수화)
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