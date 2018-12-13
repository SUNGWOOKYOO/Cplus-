// [Chap5]

/*	Foundation of Copying in terms of Object
	※ 디폴트 복사 생성자는 정의하지 않아도 존재하며, 자동으로 호출 된다. 
		복사생성자를 정의할때는, 복사의 개념을 구현(변경은 하지 않되, 맴버 변수에 접근하여 복사)하기 위해 const 키워드를 인자에 삽입하여 이를 방지한다.
		하지만, 이러한 복사는 문제를 유발시킬 수있다.(나중에 자세히)
		explicit 선언을 통해 묵시적으로 대입연산자를 이용한 객체 생성, 초기화를 불가능 하게 할 수 있다.
		※  복사생성자는 대입연산을 할때 항상 호출 된다. 정의가 안되어 있으면 디폴트 복사생성자 호출 
			복사생성자의 인자에 &는 반드시 있어야한다; 없다면, 컴파일에러 발생 ;복사생성자의 호출은 무한 루프에 빠진다; 자세한 사항은 나중에...*/
#if 0 
#include<iostream>
using namespace std;

class AAA
{
	int num1; 
	int num2;
public:
	AAA() {}
	AAA(int n1, int n2) : num1(n1), num2(n2) {}
	//AAA(const AAA &copy) : num1(copy.num1), num2(copy.num2) { cout<<"I'm called! "<<endl;}		// default Copy constructor 를 그대로 구현해 놓은것 
	//explicit AAA(const AAA &copy) : num1(copy.num1), num2(copy.num2) { cout << "I'm called! " << endl; }		// 묵시적으로 대입 연산자 를 통한 객체 생성 허용 x 
	void ShowData() { cout << num1 << endl;	cout << num2 << endl; }
};
void main()
{
	// 다음과 같이 변수에 값을 입력하는 것 역시 copy의 일종이다.
//	int num = 20; 
//	int &ref = num;
//	const int num = 20; 
//	const int &ref2 = 20;		

	AAA sim1(15, 20); 
	AAA sim2 = sim1; 		// same with ; AAA sim2(sim1);	// AAA(AAA &copy) 정의 없이도 Copy 가능? OK! why? default Copy constructor존재한다 in C++

	sim1.ShowData();
	sim2.ShowData();

//	int num(20);		 // same with ; int num = 20;

}
#endif

// 05-2 ; Deep Copy vs Shallow Copy 
/* Shallow Copy ; Default Copy 
	※문제점 : 멤머 변수(포인터 변수)가 동적할당을 통한 Heap영역에 할당되었을 때, 문제가 된다.
	= 연산자를 통해 Copy 될때, 포인터 변수가 복사 되는데 복사된 포인터는 같은 Heap 영역 공간을 가리키고 있다. 
	따라서, 2개의 서로다른 객체의 맴버 변수가 같은 공간을 가리키게 된다.
VS
	Deep Copy : 멤버변수가 동적할당되었을때, 대입 연산 문제 해결 
	Copy Constructor 를 통해 대입 연산이 이루어질때, 복사되는 맴버 변수가 가리키는 Heap 영역 을 또하나 만들어서 각각 다른 메모리를 가리키도록 한다. */
#if 0
#include <iostream>
#include <cstring>
using namespace std;

class Person
{
	char * name;	// Pointer 맴버변수  
	int age;
public:
	// 생성자 정의 ; 동적할당을 통해 member 변수 할당 ; 
	Person(char * myname, int myage)
	{
		int len = strlen(myname) + 1;	// 생성자를 통해 포인터 멤버 변수가 동적 할당을 통해 Heap 영역을 가리키게 정의하였다. 
		name = new char[len];
		strcpy_s(name, len, myname);
		age = myage;
	}

	// 복사 생성자 정의 ; 대입 연산을 할때 자동으로 호출 
#if 0	// Deep Copy 
	Person(const Person& copy) :age(copy.age)				// 대입연산시 자동으로 call 
	{
		name = new char[strlen(copy.name) + 1];				// 또다른 Heap 공간 할당
		strcpy_s(name, strlen(copy.name) + 1, copy.name);
	}
#else	// Shaloow Copy
	Person(const Person& copy) : age(copy.age), name(copy.name) { }
#endif

	void ShowPersonInfo() const
	{
		cout << "이름: " << name << endl;
		cout << "나이: " << age << endl;
	}
	~Person()
	{
		delete[]name;
		cout << "called destructor!" << endl;
	}
};

int main(void)
{
	Person man1("Lee dong woo", 29);
	Person man2 = man1;					// Default 복사 생성자를 이용하여 할당 연산(Copy)를 하게 되는데 이때, 같은 공간을 가리키는 문제 발생
	man1.ShowPersonInfo();
	man2.ShowPersonInfo();
	return 0;							// 객체는 2개인데, Deep copy가 이루어 지지 않으면, 소멸자는 1번 밖에 Call 되지 않는다. : 심한한 문제 발생! 하나의 객체가 소멸 후 나머지 객체가 가리키는 공간 없어짐
}
#endif 


// 05-3 ; 복사 생성자의 호출 시점
/*	Case1: 기존에 생성된 객체를 이용하여 새로운 객체 초기화 
	Case2: call by value 방식의 함수 호출 과정에서 객체를 인자로 전달하는 경우
	Case3: 객체를 반환하되, 참조형으로 반환하지 않는경우 ; 임시객체의 개념
공통점 : 객체를 생성해야한다. 단, 생성과 동시에 동일한 자료형의 객체로 초기화 해야한다! 	
위의 3가지 Case와 비슷한 상황 3가지 example(메모리 공간의 할당과 초기화가 동시에 일어나는 상황). 
1.	int num = num2; 
2.	int SimpleFunc(int n){ ... } ...
	Simple Func(num); 호출되는 순간 매개변수 n이 할당과 동시에 초기화! 
3.  int SimpleFunc(int n){ ...  return n;} ...
	int num = 10; 
	cout << SimpleFuc(num) << endl;	출력을 할때 값을 반환하면 반환된 값은 별도의 메로리 공간이 할당되어 저장이 되고, cout을 통해 출력이 가능한것! 임시변수(상수)의 개념 (이전에도 말했듯이 상수가아닌 변수개념이므로, 이 값을 참조가 가능하다 )  */
#if 0
#include <iostream>
#include <cstring>
using namespace std;

class Person
{
	char * name;	// Pointer 맴버변수  
	int age;
public:
	// 생성자 정의 ; 동적할당을 통해 member 변수 할당 ; 
	Person(char * myname, int myage)
	{
		int len = strlen(myname) + 1;	// 생성자를 통해 포인터 멤버 변수가 동적 할당을 통해 Heap 영역을 가리키게 정의하였다. 
		name = new char[len];
		strcpy_s(name, len, myname);
		age = myage;
	}

	// 복사 생성자 정의 ; 대입 연산을 할때 자동으로 호출 
#if 1	// Deep Copy 
	Person(const Person& copy) :age(copy.age)				// 대입연산시 자동으로 call 
	{
		cout << "I'm Deep copy constructor!!" << endl;
		name = new char[strlen(copy.name) + 1];				// 또다른 Heap 공간 할당
		strcpy_s(name, strlen(copy.name) + 1, copy.name);
	}
#else	// Shaloow Copy
	Person(const Person& copy) : age(copy.age), name(copy.name) { }
#endif

	void ShowPersonInfo() const
	{
		cout << "이름: " << name << endl;
		cout << "나이: " << age << endl;
	}
	~Person()
	{
		delete[]name;
		cout << "called destructor!" << endl;
	}
};

void FuncCaseTwoObj(Person ob)
{
	ob.ShowPersonInfo();
}
Person FuncCaseTreeObj(Person ob)
{
	return ob;
}

int main(void)
{
	Person man1("Lee dong woo", 29);
	Person man2 = man1;							// Case 1 : Copy constructor call!  

	FuncCaseTwoObj(man2);						// Case 2: Copy constructor call!

	FuncCaseTreeObj(man2).ShowPersonInfo();		// Case2 and Case 3 : Copy constructor call! 

	return 0;
}
#endif

/* Temporary Object (임시객체) 의 개념 */
#if 0	// ReturnObjCopycon.cpp 
#include <iostream>
using namespace std;

class SoSimple
{
private:
	int num;
public:
	SoSimple(int n) : num(n)
	{ }
	SoSimple(const SoSimple& copy) : num(copy.num)
	{
		cout << "Called SoSimple(const SoSimple& copy)" << endl;
	}
	SoSimple& AddNum(int n)		// 참조값을 반환하기 때문에 반환하며 복사가 이루어지지않는다 (복사 생성자 호출 X)
	{
		num += n;
		return *this;
	}
	void ShowData()
	{
		cout << "num: " << num << endl;
	}
};

SoSimple SimpleFuncObj(SoSimple ob)
{
	cout << "return 이전" << endl;
	return ob;
}

int main(void)
{
	SoSimple obj(7);

	// SimeFuncObj함수가 반환하는 obj의 복사본이 만들어지며 반환, 그 (임시 객체)객체를 대상으로 AddNum 호출, 이어서 AddNum함수가 반환하는 참조값을 대상으로 ShowData함수 호출
	SimpleFuncObj(obj).AddNum(30).ShowData();	
	obj.ShowData();
	return 0;
}

#elif 0

#include <iostream>
using namespace std;

class Temporary
{
private:
	int num;
public:
	Temporary(int n) : num(n)
	{
		cout << "create obj: " << num << endl;
	}
	~Temporary()
	{
		cout << "destroy obj: " << num << endl;
	}
	void ShowTempInfo()
	{
		cout << "My num is " << num << endl;
	}
};

int main(void)
{
	Temporary(100);
	cout << "********** after make!" << endl << endl;

	Temporary(200).ShowTempInfo();
	cout << "********** after make!" << endl << endl;

	const Temporary &ref = Temporary(300);
	cout << "********** end of main!" << endl << endl;
	return 0;
}


#elif 0		
/*	- 임시객체는 다음행으로 넘어가면 바로 소멸되어 버린다. 
	- 참조자에 참조되는 임시객체는 바로 소멸되지 않는다.
	※ 생성자가 반환하는 값은 임시객체의 참조값을 의미한다. 따라서 Temparary(200).ShowTemInfo(); 는 (임시 객체의 참조값).ShowTempInfo();를 의미
*/
#include <iostream>
using namespace std;

class SoSimple
{
private:
	int num;
public:
	SoSimple(int n) : num(n)
	{
		cout << "New Object: " << this << endl;
	}
	SoSimple(const SoSimple& copy) : num(copy.num)
	{
		cout << "New Copy obj: " << this << endl;
	}
	~SoSimple()
	{
		cout << "Destroy obj: " << this << endl;
	}
};

SoSimple SimpleFuncObj(SoSimple ob)
{
	cout << "Parm ADR: " << &ob << endl;
	return ob;
}

int main(void)
{
	SoSimple obj(7);
	SimpleFuncObj(obj);

	cout << endl;
	SoSimple &tempRef = SimpleFuncObj(obj);			// 임시객체를 참조하면 다음줄에 없어지지 않는다! 
	cout << "Return Obj " << &tempRef << endl;
	return 0;
}

#endif 
