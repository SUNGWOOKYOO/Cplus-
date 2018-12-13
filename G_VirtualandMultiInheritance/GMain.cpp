	// [Chap9]

// 09-1
/*	멤버함수의 실체 
	C	sytle coding 
	C++	sytle coding
	을 통해 알수 있는점:	멤버변수는 객체 내에 존재하지만, 
							멤버함수는 메모리 한 공간에 별도로 위치하고, 이 함수가정의된 클래스의 모든 객체가 이를 공유하는 형태를 취함		*/
#if 0
/*	C++ style	*/
#include <iostream>
using namespace std;

class Data
{
private:
	int data;
public:
	Data(int num) : data(num)
	{  }
	void ShowData()
	{
		cout << "Data: " << data << endl;
	}
	void Add(int num)
	{
		data += num;
	}
};

int main(void)
{
	Data obj(15);
	obj.Add(17);
	obj.ShowData();
	return 0;
}
#elif 0
/*	C	style	*/
#include <iostream>
using namespace std;

// 클래스 Data를 흉내낸 영역
typedef struct Data
{
	int data;
	void(*ShowData)(Data*);		// 함수 포인터 형태 
	void(*Add)(Data*, int);
} Data;

void ShowData(Data* THIS)
{
	cout << "Data: " << THIS->data << endl;
}
void Add(Data* THIS, int num)
{
	THIS->data += num;
}


// 적절히 변경된 main 함수
int main(void)
{
	Data obj1 = { 15, ShowData, Add };	// 함수 포인터를 인자로 받기 때문에 함수 이름을 넣어서 함수를 가리키게 하였다. 
	Data obj2 = { 7, ShowData, Add };

	obj1.Add(&obj1, 17);
	obj2.Add(&obj2, 9);
	obj1.ShowData(&obj1);
	obj2.ShowData(&obj2);
	return 0;
};

#endif

/*	가상함수 동작원리
	C++ style의 코딩에서
	※	한개 이상의 가상함수를 포함하는 클래스에 대해서 컴파일러는 가상함수 테이블(V-Table)을 만든다. 
		main 함수가 호출 되기 이전에 V-Table이 메모리 공간에 할당된다. 객체 생성과 상관이 없다.
		overriding된 가상함수의 주소정보는 derived class의 V-Table에 포함되지 않는다. 
		즉, 무조건 마지막에 overriding 한 derived class의 member function이 호출되는 것이다.	*/
#if 0
#include <iostream>
using namespace std;

class AAA
{
private:
	int num1;
public:
	virtual void Func1() { cout << "Func1" << endl; }
	virtual void Func2() { cout << "Func2" << endl; }
};

class BBB : public AAA
{
private:
	int num2;
public:
	virtual void Func1() { cout << "BBB::Func1" << endl; }
	void Func3() { cout << "Func3" << endl; }
};

int main(void)
{
	AAA * aptr = new AAA();
	aptr->Func1();

	BBB * bptr = new BBB();
	bptr->Func1();
	return 0;
}
#endif

// 09-2 ; Multiple Inheritance
/*	다중상속의 모호성	*/
#if 0
#include <iostream>
using namespace std;

class BaseOne
{
public:
	void SimpleFunc() { cout << "BaseOne" << endl; }
};

class BaseTwo
{
public:
	void SimpleFunc() { cout << "BaseTwo" << endl; }
};

class MultiDrived : public BaseOne, protected BaseTwo
{
public:
	void ComplexFunc()
	{
		BaseOne::SimpleFunc();
		BaseTwo::SimpleFunc();
	}
};

int main(void)
{
	MultiDrived mdr;
	mdr.ComplexFunc();
	return 0;
}
#endif

/*	virtual 상속을 통해 해결	
	생성자 1번만 호출되도록함 
	:: 연산자 없이 V-table을 이용하여 적절한 함수 실행*/
#if 0
#include <iostream>
using namespace std;

class Base
{
public:
	Base() { cout << "Base Constructor" << endl; }
	void SimpleFunc() { cout << "BaseOne" << endl; }
};

class MiddleDrivedOne : virtual public Base
{
public:
	MiddleDrivedOne() : Base()
	{
		cout << "MiddleDrivedOne Constructor" << endl;
	}
	void MiddleFuncOne()
	{
		SimpleFunc();		// vitual 선언이 있기에 가능함. 없다면 MiddleDrivedOne::SimpleFuncOne();
		cout << "MiddleDrivedOne" << endl;
	}
};

class MiddleDrivedTwo : virtual public Base
{
public:
	MiddleDrivedTwo() : Base()
	{
		cout << "MiddleDrivedTwo Constructor" << endl;
	}
	void MiddleFuncTwo()
	{
		SimpleFunc();		// vitual 선언이 있기에 가능함 
		cout << "MiddleDrivedTwo" << endl;
	}
};

class LastDerived : public MiddleDrivedOne, public MiddleDrivedTwo
{
public:
	LastDerived() : MiddleDrivedOne(), MiddleDrivedTwo()
	{
		cout << "LastDerived Constructor" << endl;
	}
	void ComplexFunc()
	{
		MiddleFuncOne();
		MiddleFuncTwo();
		SimpleFunc();	// vitual 선언이 있기에 가능함 
	}
};

int main(void)
{
	cout << "객체생성 전 ..... " << endl;
	LastDerived ldr;						// virtual 선언으로 인해 Base 생성자 1번만 호출됨
	cout << "객체생성 후 ..... " << endl;
	ldr.ComplexFunc();
	return 0;
}
#endif
