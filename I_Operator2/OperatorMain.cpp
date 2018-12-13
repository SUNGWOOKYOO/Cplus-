//	Chap[11]
/*	대입 연산자의 특성
1. 정의하지 않으면 default 대입 연산자 삽입
2. default 대입 연산자는 shallow copy
3. 연산자 내에서 동적 할당을 한다면, deep copy를 직접 define 해야한다.

※ 기존에  생성된 두 객체간의 대입 연산은 대입 연산자가 호출됨. (copy constructor와의 차이 )
pos2 = pos1;	즉, pos2.operator=(pos1)					*/

/* default 대입연산자 */
#if 0
#include <iostream>
using namespace std;

class First
{
private:
	int num1, num2;
public:
	First(int n1 = 0, int n2 = 0) : num1(n1), num2(n2)
	{  }
	void ShowData() { cout << num1 << ", " << num2 << endl; }
};

class Second
{
private:
	int num3, num4;
public:
	Second(int n3 = 0, int n4 = 0) : num3(n3), num4(n4)
	{  }
	void ShowData() { cout << num3 << ", " << num4 << endl; }

	// 디폴트 대입 연산자는 이렇게 생겼다. 
	Second& operator=(const Second& ref)
	{
		cout << "Second& operator=()" << endl;
		num3 = ref.num3;
		num4 = ref.num4;
		return *this;
	}
};

int main(void)
{
	First fsrc(111, 222);
	First fcpy;
	Second ssrc(333, 444);
	Second scpy;
	fcpy = fsrc;
	scpy = ssrc;
	fcpy.ShowData();
	scpy.ShowData();

	First fob1, fob2;
	Second sob1, sob2;
	fob1 = fob2 = fsrc;
	sob1 = sob2 = ssrc;

	fob1.ShowData();
	fob2.ShowData();
	sob1.ShowData();
	sob2.ShowData();
	return 0;
}
#endif 

/*	default 대입연산자의 문제점 -  Deep copy 필요 
	객체는 2개인데 소멸자가 1번 바께 호출 되지 않는다. - memory의 Leak 발생!
	즉, 2개의 객체가 동일한 Heap 영역을 가리키고 있다.							*/
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

#if 0	// Deep 대입 연산자 
	Person& operator=(const Person& ref)
	{
		delete[]name;	//원래 가지고 있던 name 제거! 

		int len = strlen(ref.name) + 1;
		name = new char[len];		// Deep copy를 위한 Heap 영역에 새로운 할당 
		strcpy_s(name, strlen(ref.name) + 1 , ref.name);
		age = ref.age;
		return *this;
	}
#else	// shallow 대입 연산자(default 대입연산)
	Person& operator=(const Person& ref)
	{
		age = ref.age;
		name = ref.name;

		return *this;
	}
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
	//Person man2 = man1;					// Default 복사 생성자를 이용하여 할당 연산(Copy)를 하게 되는데 이때, 같은 공간을 가리키는 문제 발생
	Person man2("Yoon Ji yul", 22);
	man2 = man1;							// 정의된 Deep 대입 연산자가 없다면, default 대입 연산자를 통해 연산 된다.

	man1.ShowPersonInfo();
	man2.ShowPersonInfo();
	return 0;							// 객체는 2개인데, Deep copy가 이루어 지지 않으면, 소멸자는 1번 밖에 Call 되지 않는다. : 심한한 문제 발생! 하나의 객체가 소멸 후 나머지 객체가 가리키는 공간 없어짐
}

#endif 

/*	Copy constructor와 대입 연산자의 다른점 
	상속관계 에 있는 클래스에서 
	derived 클래스의 대입 연산자에 아무 명시를 하지 않으면 base 클래스의 대입연산자는 호출되지 않는다. 
	※	디폴트 derived 클래스의 대입 연산자는 base 연산자를 호출 한다. 
		하지만, derived 클래스의 대입 연산자를 사용자가 정의할 경우, 명시적으로 base class 대입 연산자 호출 해야함 */
#if 0
#include <iostream>
using namespace std;

class First
{
private:
	int num1, num2;
public:
	First(int n1 = 0, int n2 = 0) : num1(n1), num2(n2)
	{  }
	void ShowData() { cout << num1 << ", " << num2 << endl; }

	// derived class 의 대입 연산자에서 명시적으로 호출을 적어야 이 부분이 호출 될 수 있다. 
	First& operator=(const First&ref)
	{
		cout << "First& operator=()" << endl;
		num1 = ref.num1;
		num2 = ref.num2;
		return *this;
	}
};

class Second : public First
{
private:
	int num3, num4;
public:
	Second(int n1, int n2, int n3, int n4)
		: First(n1, n2), num3(n3), num4(n4)
	{  }
	void ShowData()
	{
		First::ShowData();
		cout << num3 << ", " << num4 << endl;
	}

	///*
	// derived class의 대입 연산자 정의에 base 대입 연산자를 명시적으로 호출 해야 한다. 
	Second& operator=(const Second &ref)
	{
	cout<<"Second& operator=()"<<endl;
#if 1
	/* ※	Remember!!
			ref는 Second 형 참조자 이지만, 
			const First &ref = ref 가능 하다! 
			(Chap8 ... virtual 선언을 통해 reference의 tpye에 따라 결정되는것이 아닌,
			reference가 참조하는 객체의 함수를 쓰도록 할 수 있다)	*/
	First::operator=(ref);		// base 클래스의 대입 연산자 호출을 명령! 
#endif
	num3=ref.num3;
	num4=ref.num4;
	return *this;
	}
	//*/

};


int main(void)
{
	Second ssrc(111, 222, 333, 444);
	Second scpy(0, 0, 0, 0);
	scpy = ssrc;
	scpy.ShowData();
	return 0;
}
#endif

/*	 initializer가 성능 향상에 도움이 되는 이유
	initializer를 사용하면, 선언과 동시에 초기화가 이뤄지는 형태 
	즉, AAA mem = ref; 
	복사생성자만 호출 
	
	할당(대입연산)을 통해 초기화하면, 선언과 초기화를 각각 별도의 분장에서 진행
	즉, AAA mem;
		mem = ref;
	복사생성자와 대입연산자가 둘다 호출 된다.  */
#if 0
#include <iostream>
using namespace std;

class AAA
{
private:
	int num;
public:
	AAA(int n = 0) : num(n)
	{
		cout << "AAA(int n=0)" << endl;
	}
	AAA(const AAA &ref) : num(ref.num)
	{
		cout << "AAA(const AAA & ref)" << endl;
	}
	AAA & operator=(const AAA &ref)
	{
		num = ref.num;
		cout << "operator=(const AAA &ref)" << endl;
		return *this;
	}
};

// initializer를 통해 초기화 
class BBB
{
private:
	AAA mem;
public:
	BBB(const AAA & ref)
		: mem(ref)
	{  }
};

// 대입 연산을 통해 초기화 
class CCC
{
private:
	AAA mem;
public:
	CCC(const AAA & ref)
	{
		mem = ref;
	}
};

int main(void)
{
	AAA obj1(12);	// 생성자 호출
	cout << "*********************" << endl;
	BBB obj2(obj1);	// 복사 생성자 호출
	cout << "*********************" << endl;
	CCC obj3(obj1);	// 복사 생성자, 대입 연산자 호출
	return 0;
}
#endif 

// 11-2		; 배열의 인덱스 연산자 overloading 

// 기본 자료형 대상의 배열 클래스 
/*	object를 대상으로 접근해야 하므로, member function으로만 overloading이 가능하다.
	※	반환형을 참조형으로 하여 배열요소에 접근할 수 있다. 
	※	생성자를 호출 할시 array를 동적할당 하고, 이를 private member 인 pointer가 가르키게 되는데 
		operator[](인덱스값)를 통해 접근하고자 할 목적으로 overloading 하게 된다.	
	※	복사연산자와 대입연산자를 private 맴버로 둠으로써 복사와 대입을 원천적으로 막는것이 좋을 수 있다.
		BoundCheckIntArray arr(5);
		BoundCheckIntArray cpy1(5);
		cpy1 = arr;		// 안전하지 않기 때문에 막는다.			
		
	However, 
		반환형을 참조형으로 하기 때문에, operator[]() 는 
		access function을 사용할 경우,  
		또한, access function의 매개변수를 const 객체를 이용하여 안정성을 높히려는 경우도, 
		컴파일 에러를 초래한다! 
		-> const 선언 유무를 이용하여 operator[]()함수를 오버로딩 한다!  
		*/
#if 0
#include <iostream>
#include <cstdlib>
using namespace std;

class BoundCheckIntArray
{
private:
	int * arr;
	int arrlen;

	// 복사 생성자와 대입 연산자를 private으로 둠으로써, 배열값이 복사되는것을 원천적으로 막음
	BoundCheckIntArray(const BoundCheckIntArray& arr) { }
	BoundCheckIntArray& operator=(const BoundCheckIntArray& arr) { }

public:
	BoundCheckIntArray(int len) :arrlen(len)
	{
		arr = new int[len];
	}
	int& operator[] (int idx)
	{
		if (idx<0 || idx >= arrlen)
		{
			cout << "Array index out of bound exception" << endl;
			exit(1);
		}

		return arr[idx];
	}
	~BoundCheckIntArray()
	{
		delete[]arr;
	}
};

int main(void)
{
	BoundCheckIntArray arr(5);

	for (int i = 0; i<5; i++)
		arr[i] = (i + 1) * 11;		//arr.operator[](i)를 의미 

	for (int i = 0; i < 6; i++)
		cout << arr[i] << endl;

	BoundCheckIntArray copy1(5);
	// copy1=arr;						//복사 생성자와, 대입연산자를 private으로 두었기 때문에 불가능 
	// BoundCheckIntArray copy=arr;
	return 0;
}

#endif

/*	const 함수의 overloading! 
	access function을 이용하여 operator[] 함수를 쓰고싶다! 
	const 선언 유무를 이용하여 operator[]()함수를 오버로딩 한다! 
	※	operator[]() const 의 경우, 반환형을 int로 하여 단순히 배열 값을 반환하게 해야한다. 
		operator[]() 의 경우, 반환을 참조형(int &)으로 하여 배열 요소에 접근 가능 하게 한다. */
#if 0
#include <iostream>
#include <cstdlib>
using namespace std;

class BoundCheckIntArray
{
private:
	int * arr;
	int arrlen;

	BoundCheckIntArray(const BoundCheckIntArray& arr) { }
	BoundCheckIntArray& operator=(const BoundCheckIntArray& arr) { }

public:
	BoundCheckIntArray(int len) :arrlen(len)
	{
		arr = new int[len];
	}
	int& operator[] (int idx)
	{
		if (idx<0 || idx >= arrlen)
		{
			cout << "Array index out of bound exception" << endl;
			exit(1);
		}

		return arr[idx];
	}
	int operator[] (int idx) const
	{
		if (idx<0 || idx >= arrlen)
		{
			cout << "Array index out of bound exception" << endl;
			exit(1);
		}

		return arr[idx];
	}
	int GetArrLen() const
	{
		return arrlen;
	}
	~BoundCheckIntArray()
	{
		delete[]arr;
	}
};

void ShowAllData(const BoundCheckIntArray& ref)
{
	int len = ref.GetArrLen();

	for (int idx = 0; idx<len; idx++)
		cout << ref[idx] << endl;	// const 선언이 있는 operator[] 호출
}

int main(void)
{
	BoundCheckIntArray arr(5);

	for (int i = 0; i<5; i++)
		arr[i] = (i + 1) * 11;	// const 선언이 없는 operator[] 호출

	ShowAllData(arr);
	return 0;
}

#endif 

/*	객체 대상의 배열 클래스 
	1. 객체의 주소값을 저장하는 배열 기반의 클래스 
	2. 객체를 저장하는 배열 기반의 클래스 
		1번 경우가 많이 쓰이므로, 1번 경우만 보도록 하겠다.	
		주소 값을 저장 하도록 하면 깊은 복사냐, 얕은 복사냐의 문제를 신경쓰지 않아도 되기 때문에 이 방법 선호*/
#if 0 
#include <iostream>
#include <cstdlib>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y) {  }
	friend ostream& operator<<(ostream& os, const Point& pos);
};

// << 연산을 통해 바로 private member를 보여주기위해 global operator<< 를 정의함.
ostream& operator<<(ostream& os, const Point& pos)
{
	os << '[' << pos.xpos << ", " << pos.ypos << ']' << endl;
	return os;
}

typedef Point * POINT_PTR;

class BoundCheckPointPtrArray
{
private:
	POINT_PTR * arr;
	int arrlen;

	BoundCheckPointPtrArray(const BoundCheckPointPtrArray& arr) { }
	BoundCheckPointPtrArray& operator=(const BoundCheckPointPtrArray& arr) { }

public:
	BoundCheckPointPtrArray(int len) :arrlen(len)
	{
		arr = new POINT_PTR[len];
	}
	POINT_PTR& operator[] (int idx)
	{
		if (idx<0 || idx >= arrlen)
		{
			cout << "Array index out of bound exception" << endl;
			exit(1);
		}

		return arr[idx];
	}

	// operator[] const 함수의 overloading; access function이 적절한 함수를 사용하도록 하기 위해 
	POINT_PTR operator[] (int idx) const
	{
		if (idx<0 || idx >= arrlen)
		{
			cout << "Array index out of bound exception" << endl;
			exit(1);
		}

		return arr[idx];
	}
	int GetArrLen() const
	{
		return arrlen;
	}
	~BoundCheckPointPtrArray()
	{
		delete[]arr;
	}
};

int main(void)
{
	BoundCheckPointPtrArray arr(3);
	arr[0] = new Point(3, 4);	// 주소값을 저장하게됨
	arr[1] = new Point(5, 6);
	arr[2] = new Point(7, 8);

	for (int i = 0; i<arr.GetArrLen(); i++)
		cout << *(arr[i]);	// 주소값을 저장했으므로 *(arr[i])를 해야한다. 

	delete arr[0];
	delete arr[1];
	delete arr[2];
	return 0;
}

#endif


// 11-3 이후로는 생략을 하겠다.
/*	new, delete, *, 
	smart *, 
	();functor
	conversion operator
	등이 있다.		*/