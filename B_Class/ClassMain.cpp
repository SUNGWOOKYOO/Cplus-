// [Chap3]

// RacingMain.cpp ; Carline class
/* Class에서 가독성을 위해 namespace와 enum 사용 
	Class 는 class specifier : public, private, protected 에 의해 member 들이 관리된다. 
	기본적으로 변수들은 private member이므로 member 함수에 의해 접근이 가능하다!
	※ class가 구조체 와 다른점 
	- 접근제어 지시자 class specifier에 의해 접근 유무 지정
	- class에서는 접근 제어 지시자를 선언 하지 않으면, 모든 변수와 함수는 private 으로 선언됨
	- sturture에서는 별도의 접근 제어를 선언하지 않으면, 모든 변수 와 함수는 public으로 선언된다.  */
/* Class에서 Inline 함수 사용 
	- 인라인 함수 사용시 헤더안에 inline 함수 정의를 넣어야한다 
	why? 인라인 함수는 
	컴파일 과정에서 함수의 호출 문이 있는곳에 함수의 몸체부분이 삽입 되어야하므로
	클래스 선언과 동일한 파일에 저장되어 컴파일러가 동시에 참조할 수 있게 해야한다.*/
#if 0
#include "CarInline.h"

int main(void)
{
	Car run99;
	run99.InitMembers("run99", 100);
	run99.Accel();
	run99.Accel();
	run99.Accel();
	run99.ShowCarState();
	run99.Break();
	run99.ShowCarState();
	return 0;
}
#endif

// [Chap4]

// RectangleFaultFind.cpp ; Rectangle, Point class
/*	Point정보가 은닉된 Rectangle class
	Point class ⊂ Rectangle class
	Information Hiding(정보은닉) : private member 에 대해서 제한된 방법으로만 접근을 허용해서 잘못된 값이 저장되지 않도록 한다. 
	※ private member는 access function을 통해 다뤄진다. 
		- access function 은 기본적으로 member 변수를 변경할 수 있는 능력이 있으므로,  
		  사용자가 private member 변경을 원치 않는 경우, const 함수로서 access function을 선언 해야 한다
		  ; 즉, const 참조자를 이용 한 class 객체를 argument로 하는 함수 내부에서 호출되는 객체의 access function은 const access function이어야한다.  */
#if 0
#include<iostream>
#include "Point.h"
#include "Rectangle.h"
using namespace std;

int main(void)
{
	Point pos1;
	if (!pos1.InitMembers(-2, 4))		// access function을 통해 private member를 초기화 하므로 안정적으로 Information Hiding 을 구현 할 수있다. 
		cout << "초기화 실패" << endl;
	if (!pos1.InitMembers(2, 4))
		cout << "초기화 실패" << endl;

	Point pos2;
	if (!pos2.InitMembers(5, 9))
		cout << "초기화 실패" << endl;

	Rectangle rec;
	if (rec.InitMembers(pos2, pos1))
		cout << "직사각형 초기화 실패" << endl;

	if (rec.InitMembers(pos1, pos2))
		cout << "직사각형 초기화 실패" << endl;

	rec.ShowRecInfo();
	return 0;
}

#endif
 
/*	Encapsulation(캡슐화) : 관련있는 함수와 변수를 하나의 클래스 안에 묶는것 ; 여러 클래스들을 하나의 클래스로 필요에 의해 묶어 여러 기능들을 효율적으로 사용하도록 한다.
	※ encapsulation 과정에서 access specifier 선언과 const의 사용을 하면 안정적인 Information Hiding을 동반한 encapsulation 을 구현 할 수 있다 */
#if 0
#include <iostream>
using namespace std; 

class SinivelCap    // 콧물 처치용 캡슐
{
public:
	void Take() const { cout << "콧물이 싹~ 납니다." << endl; }
};

class SneezeCap    // 재채기 처치용 캡슐
{
public:
	void Take() const { cout << "재채기가 멎습니다." << endl; }
};

class SnuffleCap   // 코막힘 처치용 캡슐
{
public:
	void Take() const { cout << "코가 뻥 뚫립니다." << endl; }
};

class CONTAC600
{
private:
	SinivelCap sin;
	SneezeCap sne;
	SnuffleCap snu;

public:
	void Take() const
	{
		sin.Take();
		sne.Take();
		snu.Take();
	}
};

class ColdPatient
{
public:
	void TakeCONTAC600(const CONTAC600 &cap) const { cap.Take(); }		// const CONTAC600 &cap 가 인자로 쓰였으므로 cap.Take()가 쓰였으므로 Take는 const 함수 여야한다.
};

int main(void)
{
	CONTAC600 cap;
	ColdPatient sufferer;
	sufferer.TakeCONTAC600(cap);
	return 0;
}
#endif

// Constructor2.cpp
/*	Constructor(생성자) :  객체 생성과 동시 호출되며 객체를 초기화 할 수 있다. 
	※ overloading, default 값 setting 가능 	
	※ 객체 생성시 함수의 원형 선언처럼 쓰면 안된다; C++에서는 함수 원형 선언으로만 사용하기로 약속했다. - [classtype] obj ();  function prototype declaration
	※ 생성자는 반드시 호출 된다(생성자 정의 하지 않으면 디폴트 생성자 호출됨)
	※ Member Initializer 를 사용하면 private member 변수 및 객체 맴버 변수를 초기화 할수 있으며, 이때, 선언과 동시에 초기화가 이뤄지는 효율적인 코드로 동작한다.
	※ Const 맴버 변수(= const  맴버 상수)와 참조자는 선언과 동시에 초기화 해야하는데 Member Initializer를 이용하면 초기화가 가능하다 .      
	※ 동적할당을 통해 class object를 선언할 경우, 반드시 new 를 이용하여 선언 해야한다. malloc을 이용할 경우, 생성자 호출이 되지 않는다. - 클래스의 크기 정보로만 바이트 단위로 동적 할당이 이루어짐
	※ access function을 통해(동적할당한 객체를 참조값으로 반환가능) 클래스 내부에서 동적할당을 통해 객체를 생성할 경우, 생성자를 private으로 두기도 한다! ; 힙영역에 할당도니 메모리 공간은 변수 = 참조자가 참조가능 기억*/
#if 0

//Encaps2.cpp ;
#include <iostream>
using namespace std;

class SimpleClass
{
	int num1;
	int num2;

public:
	SimpleClass(int n1 = 0, int n2 = 0)	// default 값 setting 가능 
	{
		num1 = n1;
		num2 = n2;
	}

	void ShowData() const
	{
		cout << num1 << ' ' << num2 << endl;
	}
};

int main(void)
{
	SimpleClass sc1();    // 함수의 선언!

	SimpleClass *ptr = new SImpleclass; // 동적할당을 통해 선언!  SimpleClass *ptr = new SImpleclass();, SimpleClass *ptr = new SImpleclass(100,200); 가능 

	SimpleClass mysc = sc1();
	mysc.ShowData();
	return 0;
}

SimpleClass sc1()				// 함수의 정의
{
	SimpleClass sc(20, 30);
	return sc;
}

#elif 0
/*	RectangleConstructor.cpp ; Point, Rectangle class의 Constructor 추가 버전 
	Member initializer 를 이용한 생성자 호출 ; 생성자를 호출함과 동시에 맴버 객체의 초기화를 위해 맴버 객체의 생성자도 호출 한다.	 */
#include<iostream>
#include "Point.h"
#include "Rectangle.h"
using namespace std;

int main(void)
{

	Rectangle rec(1, 1, 5, 5);
	rec.ShowRecInfo();
	return 0;
}

#elif 0
/*※ Const 맴버 변수(= const  맴버 상수)와 참조자는 선언과 동시에 초기화 해야하는데 Member Initializer를 이용하면 초기화가 가능하다 .  */
#include <iostream>
using namespace std;

class AAA
{
public:
	AAA()
	{
		cout << "empty object" << endl;
	}
	void ShowYourName()
	{
		cout << "I'm class AAA" << endl;
	}
};

class BBB
{
private:
	AAA &ref;
	//AAA ref;	
	const int &num;

public:
	BBB(AAA &r, const int &n)
		: ref(r), num(n)		// Member initializer를 통해 BBB 객체의 member class reference &ref와 member const reference &num 을 초기화 할 수 있다.
	{
	}
	void ShowYourName()
	{
		ref.ShowYourName();
		cout << "and" << endl;
		cout << "I ref num " << num << endl;
	}
};

int main(void)
{
	AAA obj1;
	BBB obj2(obj1, 20);
	obj2.ShowYourName();
	return 0;
}

#elif 0	
// ※ 동적할당을 통해 class object를 선언할 경우, 반드시 new 를 이용하여 선언 해야한다.malloc을 이용할 경우, 생성자 호출이 되지 않는다
#include <iostream>
using namespace std;
class AAA
{	
	int num; 
public: 
	AAA() { cout << "I'm constructor!" << endl; } // 디폴트 생성자
	int GetNum(){ return num;}	//access function 
};
int main()
{
	AAA *ptr1 = new AAA; 
	AAA *ptr2 = (AAA*)malloc(sizeof(AAA));	// 생성자가 호출되지 않는다! -> 맴버를 초기화 시킬 수 없다. 문제가 될 수 있다. 
	return 0;
}

#elif 0			// PrivateConstructor.cpp
// ※ access function을 통해(동적할당한 객체를 참조값으로 반환가능) 클래스 내부에서 동적할당을 통해 객체를 생성할 경우, 생성자를 private으로 두기도 한다!
#include <iostream>
using namespace std;

class AAA
{
private:
	int num;

public:
	AAA() : num(0) {}						// 디폴트 생성자 num = 0 으로 member initializer를 통해 초기화
	AAA& CreateInitObj(int n) const			// Heap 영역에 할당된 공간 = 변수 이므로 reference이용 에 참조 가능 
	{
		AAA * ptr = new AAA(n);
		return *ptr;
	}
	void ShowNum() const { cout << num << endl; }

private:
	AAA(int n) : num(n) {}
};

int main(void)
{
	AAA base;
	base.ShowNum();

	AAA &obj1 = base.CreateInitObj(3);		//  Heap 영역에 할당된 공간 = 변수 이므로 reference이용 에 참조 받은 값을 참조한다. 
	obj1.ShowNum();

	AAA &obj2 = base.CreateInitObj(12);
	obj2.ShowNum();

	delete &obj1;
	delete &obj2;
	return 0;
}
#endif 

// 문제 04-3
#if 0
#include <iostream>

#include <cstring>



using namespace std;



namespace COMP_POS

{

	enum { CLERK, SENIOR, ASSIST, MANAGER };



	void ShowPositionInfo(int pos)

	{

		switch (pos)

		{

		case CLERK:

			cout << "사원" << endl;

			break;

		case SENIOR:

			cout << "주임" << endl;

			break;

		case ASSIST:

			cout << "대리" << endl;

			break;

		case MANAGER:

			cout << "과장" << endl;

		}

	}

}



class NameCard

{

private:

	char *name;

	char *cname;

	char *num;

	int pos;



public:

	NameCard(char *fname, char *fcname, char *fnum, int fpos)		// constructor

	{

		int len = strlen(fname) + 1;

		name = new char[len];

		strcpy_s(name, len, fname);

		len = strlen(fcname) + 1;

		cname = new char[len];

		strcpy_s(cname, len, fcname);

		len = strlen(fnum) + 1;

		num = new char[len];

		strcpy_s(num, len, fnum);

		pos = fpos;

	}

	void ShowNameCardInfo()

	{

		cout << "이름: " << name << endl;			//*(name) 을 출력하면 name[0] 이 가리키는 값이 출력된다 

		cout << "회사: " << cname << endl;

		cout << "전화번호: " << num << endl;

		cout << "직급: ";

		COMP_POS::ShowPositionInfo(pos);

		cout << endl;

	}



};



int main()

{

	NameCard manClerk("Lee", "ABCEng", "010-1111-2222", COMP_POS::CLERK);

	NameCard manSENIOR("Hong", "OrangeEng", "010-3333-4444", COMP_POS::SENIOR);

	NameCard manAssist("Kim", "SoGoodComp", "010-5555-6666", COMP_POS::ASSIST);

	manClerk.ShowNameCardInfo();

	manSENIOR.ShowNameCardInfo();

	manAssist.ShowNameCardInfo();



	system("pause");



}



//출처: http://luv4ever.tistory.com/113?category=493441 [잡동사니 블로그]
#endif 


// ObjArr 
/*	객체 배열은 한번에 여러개의 object를 선언하므로 이때, member 변수의 초기화를 따로 해주어야한다. 이때 2가지 방법
	1. object array를 선언하는경우: 
		default 생성자만 호출 될수 밖에 없다. 따라서 access function을 통해 초기화 한다
		
	2. object array pointer를 선언하는경우: 
		Heap 영역에 동적할당을 하도록 생성자를 정의하여 생성자를 통해 초기화를 한다.  
*/
#if 0
#include <iostream>
#include <cstring>
using namespace std;

class Person
{
private:
	char * name;
	int age;
public:
	Person(char * myname, int myage)
	{
		int len = strlen(myname) + 1;
		name = new char[len];
		strcpy_s(name, len, myname);
		age = myage;
	}
	Person()
	{
		name = NULL;
		age = 0;
		cout << "called Person()" << endl;
	}
	void SetPersonInfo(char * myname, int myage)
	{
		name = myname;
		age = myage;
	}
	void ShowPersonInfo() const
	{
		cout << "이름: " << name << ", ";
		cout << "나이: " << age << endl;
	}
	~Person()
	{
		delete[]name;
		cout << "called destructor!" << endl;
	}
};

#if 0
int main(void)
{
	Person parr[3];					// object array 를 사용할 경우 defalut 생성자만 호출됨

	char namestr[100];
	char * strptr;
	int age;
	int len;

	for (int i = 0; i<3; i++)
	{
		cout << "이름: ";
		cin >> namestr;
		cout << "나이: ";
		cin >> age;

		len = strlen(namestr) + 1;
		strptr = new char[len];
		strcpy_s(strptr, len, namestr);
		parr[i].SetPersonInfo(strptr, age);		// aceess function을 통해 초기화 했다.
	}

	parr[0].ShowPersonInfo();
	parr[1].ShowPersonInfo();
	parr[2].ShowPersonInfo();
	return 0;
}
#elif 1
int main(void)
{
	Person * parr[3];						// object array pointer를 이용하여 

	char namestr[100];
	char * strptr;
	int age;
	int len;

	for (int i = 0; i<3; i++)
	{
		cout << "이름: ";
		cin >> namestr;
		cout << "나이: ";
		cin >> age;

		parr[i] = new Person(namestr, age);		// Constructor 을 통해 초기화 했다.
	}

	parr[0]->ShowPersonInfo();
	parr[1]->ShowPersonInfo();
	parr[2]->ShowPersonInfo();

	delete parr[0];
	delete parr[1];
	delete parr[2];
	return 0;
}
#endif
#endif

// UsefulThisPtr.cpp
/*	This pointer 사용 
	this pointer는  맴버함수 내에서 this 라는 포인터를 사용하여 객체 자신을 가리키는 용도로 쓰인다.
	주소값과 자료형이 정해져 있지 않은 포인터다.
	※ member initializer에서는 this 포인터를 사용할 수 없다. 
	주로, member 변수와 argument(매개변수)의 이름이 동일할 경우, this 포인터를 이용하여 이를 구분짓는데 쓰인다.
*/
#if 0
#include <iostream>
using namespace std;

class TwoNumber
{
private:
	int num1;
	int num2;
public:
	TwoNumber(int num1, int num2)
	{
		this->num1 = num1;
		this->num2 = num2;
	}

	/*
	TwoNumber(int num1, int num2)
	: num1(num1), num2(num2)			// num1(this->num1) 하면 error ! 
	{
	// empty
	}
	*/

	void ShowTwoNumber()
	{
		cout << this->num1 << endl;
		cout << this->num2 << endl;
	}
};

int main(void)
{
	TwoNumber two(2, 4);
	two.ShowTwoNumber();
	return 0;
}
#endif

//SelfRef.cpp
/*	어떤 class의 맴버 함수의 반환형이 자기 class형의 참조값을 반환할 경우, 이때, this 포인터를 사용하여 객체 자신을 참조할 수 있는 참조자(Self-Reference)를 반환하게된다.
	※ 참조를 할때, 참조의 정보(참조값) 이 전달된다고 생각하자
*/
#if 0
#include <iostream>
using namespace std;

class SelfRef
{
private:
	int num;
public:
	SelfRef(int n) : num(n)
	{
		cout << "객체생성" << endl;
	}
	SelfRef& Adder(int n)
	{
		num += n;
		return *this;
	}
	SelfRef& ShowTwoNumber()
	{
		cout << num << endl;
		return *this;
	}
};

int main(void)
{
	SelfRef obj(3);
	SelfRef &ref = obj.Adder(2);	//obj의 또다른 이름이 ref가 된다. 

	obj.ShowTwoNumber();
	ref.ShowTwoNumber();

	ref.Adder(1).ShowTwoNumber().Adder(2).ShowTwoNumber();	// 임시적인 참조 객체가 recursive한 호출을 이끌고 있다.
	return 0;
}
#endif

