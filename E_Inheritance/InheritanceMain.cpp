// [Chap7]
/*	Inheritance은 프로그램의 유연성과 확장성을 위함이다. 
	일반적으로 Class는 2가지 목적으로 나뉜다. 
	1. Data oriented class	; 데이터적 성격이 강하다(derived class, sub class)
	2. func oriendted class ; Control Class, or handler class */

//	07-2;
/*	상속을 받게되면, 멤버를 물려받음, 다음과 같이 선언 
	class [child class name] : [접근 제어 지시자(public, or private, or protected)] [parent class name]
	※	child 생성자에 parient 생성자 포함해야함
		private member 를 상속받을 경우, ::없이 간접적으로 접근 가능(직접접근 불가) 
		public member 를 상속받은 경우, ::없이 or access func 없이, 직접 접근 가능	*/
#if 0
/* 생성자와 소멸자는 임시객체 이므로 Stack영역에 할당된다. 그 과정을 보이고있다. */
#include <iostream>
using namespace std;

class SoBase
{
private:
	int baseNum;
public:
	SoBase(int n) : baseNum(n)
	{
		cout << "SoBase() : " << baseNum << endl;
	}
	~SoBase()
	{
		cout << "~SoBase() : " << baseNum << endl;
	}
};

class SoDerived : public SoBase
{
private:
	int derivNum;
public:
	SoDerived(int n) : SoBase(n), derivNum(n)
	{
		cout << "SoDerived() : " << derivNum << endl;
	}
	~SoDerived()
	{
		cout << "~SoDerived() : " << derivNum << endl;
	}
};

int main(void)
{
	SoDerived drv1(15);
	SoDerived drv2(27);
	return 0;
};
#endif

// 07-3
/*	접근 지시 제어자(access specifier)
	class 의 상속에 관해 생각해야할 접근 제어 지시 경우
	class Base;
	class Derived : [access specfier] Base
	{
	[access specfier] :
	member ...
	};
	※	member 에서 access specifier.. 
		private	: 클래스 외부에서 접근불가		; derived class 직접접근 불가, 간접적으로 접근가능
		protected : 클래스 외부에서 접근 불가	; derived class 직접접근 가능!
		public :	클래스 외부에서 접근 가능	; derived class 직접접근 가능!
												# 상속 Class 정의 내부에서는 부모 class의 private 멤버 빼고는 모두 직접 접근가능
	※	class 에서 access specifier 
		protected 상속의 경우 ; 부모의 멤버중 protected 이상의 접근 범위를 protected화 시키며 상속받는다. 
					private	: 클래스 외부에서 접근불가		; derived class 에선, 접근 불가; 간접적으로 접근가능
					protected : 클래스 외부에서 접근 불가	; derived class	에선, protected화; 클래스 외부에서 접근 불가 ;
					public :	클래스 외부에서 접근 가능	; derived class 에선, protected화; 클래스 외부에서 접근 불가 ;
		private 상속의 경우 ; 부모의 멤버중 protected 이상의 접근 범위를 private 화 시키며 상속받는다.
					private	: 클래스 외부에서 접근불가		; derived class 에선, 접근 불가; 간접적으로 접근가능
					protected : 클래스 외부에서 접근 불가	; derived class	에선, protected화; 클래스 외부에서 접근 불가 ;
					public :	클래스 외부에서 접근 가능	; derived class 에선, protected화; 클래스 외부에서 접근 불가 ;
		private 상속의 경우 ; 부모의 멤버중 private 멤버를 제외하고는 그대로 상속 받겠다. 
					# 대부분의 상속은 public 상속이다. 
	*/
#if 0
#if 0
/* member에있는 부모클래스의 access specifier역할 */
#include <iostream>
using namespace std;

class Base
{
private:
	int num1;
protected:
	int num2;
public:
	int num3;
	void ShowData() { cout << num1 << ", " << num2 << num3; }
};

class Derived : public Base
{
public:
	void ShowBaseMember()
	{
		//cout << num1;		//compile error!! direct access is impossible
		cout << num2;
		cout << num3;
	}
};

int main(void)
{
	return 0;
};
#elif 0
/*	class 에서 access specifier : protected 상속*/
#include <iostream>
using namespace std;

class Base
{
private:
	int num1;
protected:
	int num2;
public:
	int num3;

	Base() : num1(1), num2(2), num3(3)
	{  }
};

// num3가 protected화 되었으므로 class 정의 안에서는 직접 사용가능, but 클래스 외부에서 직접 사용 불가
class Derived : protected Base { };	

int main(void)
{
	Derived drv;
	//cout << drv.num3 << endl;			// compile error!
	return 0;
}
#elif 0
/*	class 에서 access specifier : private 상속*/
#include <iostream>
using namespace std;

class Base
{
private:
	int num1;
protected:
	int num2;
public:
	int num3;

	Base() : num1(1), num2(2), num3(3)
	{  }
};

// num2, num3가 private 화 되었으므로 class 정의 안에서는 직접접근 가능, 외부에서는 불가
class Derived : private Base { };

int main(void)
{
	Derived drv;
	//cout << drv.num2 << endl;
	//cout << drv.num3 << endl;			// compile error!
	return 0;
}
#endif

#endif

// 07-4 상속을 위한조건
/*	상속이 쓰이는 경우 
	1. Is - a 관계 일때 : [derived class] is a [base class] ; 가장 상속에 적합한 형태. 
	2. has - a 관계일때 :  [derived class] has a [base class] ; 사용 가능 하지만, 복잡해 질 수 있다. */
#if 0
#if 0
/* is a 관계 */
#include <iostream>
#include <cstring>
using namespace std;

class Computer
{
private:
	char owner[50];
public:
	Computer(char * name)
	{
		strcpy_s(owner, strlen(name)+1, name);
	}
	void Calculate()
	{
		cout << "요청 내용을 계산합니다." << endl;
	}
};

class NotebookComp : public Computer
{
private:
	int battary;
public:
	NotebookComp(char * name, int initChag)
		: Computer(name), battary(initChag)
	{  }
	void Charging() { battary += 5; }
	void UseBattary() { battary -= 1; }
	void MovingCal()
	{
		if (GetBattaryInfo()<1)
		{
			cout << "충전이 필요합니다." << endl;
			return;
		}

		cout << "이동하면서 ";
		Calculate();
		UseBattary();
	}
	int GetBattaryInfo() { return battary; }
};

class TabletNotebook : public NotebookComp
{
private:
	char regstPenModel[50];
public:
	TabletNotebook(char * name, int initChag, char * pen)
		: NotebookComp(name, initChag)
	{
		strcpy_s(regstPenModel, strlen(pen)+1, pen);
	}
	void Write(char * penInfo)
	{
		if (GetBattaryInfo()<1)
		{
			cout << "충전이 필요합니다." << endl;
			return;
		}
		if (strcmp(regstPenModel, penInfo) != 0)
		{
			cout << "등록된 펜이 아닙니다.";
			return;
		}
		cout << "필기 내용을 처리합니다." << endl;
		UseBattary();
	}
};

int main(void)
{
	NotebookComp nc("이수종", 5);
	TabletNotebook tn("정수영", 5, "ISE-241-242");
	nc.MovingCal();
	tn.Write("ISE-241-242");
	return 0;
}
#elif 0
/* has a 관계 : 권총소유하지 않은 경찰 표현 어렵다 */
#include <iostream>
#include <cstring>
using namespace std;

class Gun
{
private:
	int bullet;    	// 장전된 총알의 수
public:
	Gun(int bnum) : bullet(bnum)
	{ }
	void Shut()
	{
		cout << "BBANG!" << endl;
		bullet--;
	}
};

class Police : public Gun
{
private:
	int handcuffs;	    // 소유한 수갑의 수
public:
	Police(int bnum, int bcuff)
		: Gun(bnum), handcuffs(bcuff)
	{  }
	void PutHandcuff()
	{
		cout << "SNAP!" << endl;
		handcuffs--;
	}
};

int main(void)
{
	Police pman(5, 3);	// 총알 5, 수갑 3
	pman.Shut();
	pman.PutHandcuff();
	return 0;
}
#elif 0
/* has a 관계일때, 상속 없이 구현 */
#include <iostream>
#include <cstring>
using namespace std;

class Gun
{
private:
	int bullet;    	// 장전된 총알의 수
public:
	Gun(int bnum) : bullet(bnum)
	{ }
	void Shut()
	{
		cout << "BBANG!" << endl;
		bullet--;
	}
};

class Police
{
private:
	int handcuffs;    // 소유한 수갑의 수
	Gun * pistol;     // 소유하고 있는 권총
public:
	Police(int bnum, int bcuff)
		: handcuffs(bcuff)
	{
		if (bnum>0)
			pistol = new Gun(bnum);
		else
			pistol = NULL;
	}
	void PutHandcuff()
	{
		cout << "SNAP!" << endl;
		handcuffs--;
	}
	void Shut()
	{
		if (pistol == NULL)
			cout << "Hut BBANG!" << endl;
		else
			pistol->Shut();
	}
	~Police()
	{
		if (pistol != NULL)
			delete pistol;
	}
};

int main(void)
{
	Police pman1(5, 3);
	pman1.Shut();
	pman1.PutHandcuff();

	Police pman2(0, 3);     // 권총소유하지 않은 경찰
	pman2.Shut();
	pman2.PutHandcuff();
	return 0;
}
#endif
#endif 
