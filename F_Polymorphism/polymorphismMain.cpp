// [chap 8]
/*	상속은 Is - a 관계에서 쓰인다.
	상속을 통해 공통규약을 정의할 수 있다.
	오렌지 미디어 급여 확장성 문제에 주목할 것	*/

// 08-1 ; ObjectPointer
/*	base class 형 포인터는 derived class 를 가리킬 수 있다.  	
	AAA - BBB - CCC 관계에 있다면
	AAA * p = new BBB; 
	AAA * p = new CCC;
	BBB * p = new CCC; 
	가능하다			*/
#if 0
#include <iostream>
using namespace std;

class Person
{
public:
	void Sleep() { cout << "Sleep" << endl; }
};

class Student : public Person
{
public:
	void Study() { cout << "Study" << endl; }
};

class PartTimeStudent : public Student
{
public:
	void Work() { cout << "Work" << endl; }
};

int main(void)
{
	Person * ptr1 = new Student();
	Person * ptr2 = new PartTimeStudent();
	Student * ptr3 = new PartTimeStudent();
	ptr1->Sleep();
	ptr2->Sleep();
	ptr3->Study();
	delete ptr1; delete ptr2; delete ptr3;
	return 0;
}
#endif 

/*	class 형 포인터를 이용하여 상속되는 클래스를 가리키게 할 수 있다. 
	오렌지 미디어 급여 관리 확장성 문제의 1차적 해결
	※	상속관계에서 함수가 오버라이딩 되면 derived class의 함수가 우선된다.
		주석처리된 부분은 compile error가 발생하는데, 가상 함수의 개념을 알아야 이해가 가능하다.
		(간단히 말하면, C++ 컴파일러는 포인터 연산의 가능성 여부를 판단할때, 포인터의 자료형을 기준으로 판단하지, 실제 가리키는
		객체의 자료형을 기준으로 판단하지 않는다. 따라서, Employ pointer는 ShowSalaryInfo() 함수와 GetPay() 함수를 찾지 못한다.)*/
// EmployeeManager2.cpp
#if 0
#include <iostream>
#include <cstring>
using namespace std;

class Employee
{
private:
	char name[100];
public:
	Employee(char * name)
	{
		strcpy_s(this->name, strlen(name)+1, name);
	}
	void ShowYourName() const
	{
		cout << "name: " << name << endl;
	}
};

class PermanentWorker : public Employee
{
private:
	int salary;
public:
	PermanentWorker(char* name, int money)
		: Employee(name), salary(money)
	{  }
	int GetPay() const
	{
		return salary;
	}
	void ShowSalaryInfo() const
	{
		ShowYourName();
		cout << "salary: " << GetPay() << endl << endl;
	}
};

class EmployeeHandler
{
private:
	Employee* empList[50];
	int empNum;
public:
	EmployeeHandler() : empNum(0)
	{ }
	void AddEmployee(Employee* emp)
	{
		empList[empNum++] = emp;
	}
	void ShowAllSalaryInfo() const
	{
		/*
		for(int i=0; i<empNum; i++)
		empList[i]->ShowSalaryInfo();
		*/
	}
	void ShowTotalSalary() const
	{
		int sum = 0;
		/*
		for(int i=0; i<empNum; i++)
		sum+=empList[i]->GetPay();
		*/
		cout << "salary sum: " << sum << endl;
	}
	~EmployeeHandler()
	{
		for (int i = 0; i<empNum; i++)
			delete empList[i];
	}
};

int main(void)
{
	// 직원관리를 목적으로 설계된 컨트롤 클래스의 객체생성
	EmployeeHandler handler;

	// 직원 등록
	handler.AddEmployee(new PermanentWorker("KIM", 1000));
	handler.AddEmployee(new PermanentWorker("LEE", 1500));
	handler.AddEmployee(new PermanentWorker("JUN", 2000));

	// 이번 달에 지불해야 할 급여의 정보
	handler.ShowAllSalaryInfo();

	// 이번 달에 지불해야 할 급여의 총합
	handler.ShowTotalSalary();
	return 0;
}
#endif

// 08-2 ;	virtual Fucntion 
/*	C++ 컴파일러는 포인터 연산의 가능성 여부를 판단할때, 포인터의 자료형을 기준으로 판단하지, 실제 가리키는
	객체의 자료형을 기준으로 판단하지 않는다. 
	※	Base pointer는 Base형을 가리킬 수 도 있고, Derived형을 가리킬 수 도 있으므로 
		Base형 pointer로 Derived형 class의 멤버 호출을 하면 에러 발생	
		즉, pointer 형에 해당하는 클래스에 정의된 멤버에만 접근이 가능하다.*/
#if 0
#if 0
#include <iostream>
using namespace std;
class Base { public: void BaseFunc(){} };
class Derived :public Base { public: void DerivedFunc(){} };
int main()
{
	Base *p = new Derived();	// poineter는 상속 class인 할당된 Derived를 가리키는 것은 가능하지만 data type은 Base형 포인터이다. 
	//p->DerivedFunc();		// pointer는 Base 형 포인터이므로 DerivedFunc을 찾지 못한다.
	//Derived * dp = p;		// poineter는 Base 형 포인터이므로 Derived의 멤버를 대입연산하지 못한다. 
}
#elif 0
/*	pointer 형에 해당하는 클래스에 정의된 멤버에만 접근이 가능하다	*/
#include <iostream>
using namespace std;
class First { public: void ffunc() {} };
class Second :public First { public: void sfunc() {} };
class Third :public Second { public: void tfunc() {} };
int main()
{
	Third * tp = new Third();
	Second * sp = tp;
	First * fp = sp;
	
	tp->ffunc();
	tp->sfunc();
	tp->tfunc();
	
	sp->ffunc();
	sp->sfunc();
	//sp->tfunc();

	fp->ffunc();
	//fp->sfunc();
	//fp->tfunc();

}
#elif 0
/*	가상 함수의 필요성 :
	가상함수가 없으면, 실제 가리키는 자료형을 기준으로 판단하여 overriding 하게 하지 않는다. */
#include <iostream>
using namespace std;

class First
{
public:
	void MyFunc()
	{
		cout << "FirstFunc" << endl;
	}
};

class Second : public First
{
public:
	void MyFunc()
	{
		cout << "SecondFunc" << endl;
	}
};

class Third : public Second
{
public:
	void MyFunc()
	{
		cout << "ThirdFunc" << endl;
	}
};

int main(void)
{
	Third * tptr = new Third();		// 실제 가리키는 자료형 Third class
	Second * sptr = tptr;
	First * fptr = sptr;

	fptr->MyFunc();
	sptr->MyFunc();
	tptr->MyFunc();
	delete tptr;
	return 0;
}

#endif
#endif

/*	가상함수의 필요성과 적용! ; 오렌지 미디어 확장성 문제 해결! 
	pointer 형에 해당하는 클래스에 정의된 멤버에만 접근이 가능하다 
	-> 가상함수가 있어야 실제 가리키는 자료형을 기준으로 판단하여 overriding 하게 할 수 있다.
	※ Virtual Function 은 객체 지향의 개념이다. ; C++, JAVA, C# ... 에도 적용	
		virtual [함수 선언문]				
		가상함수를 사용하면, 포인터의 자료형을 기반으로 호출 대상을 결정하지 않고, 
		포인터 변수가 실제로 가리키는 객체를 참조하여 호출의 대상을 결정한다. */
#if 0
#if 0
/* virtual function을 통한 overriding */
#include <iostream>
using namespace std;

class First
{
public:
	virtual void MyFunc()
	{
		cout << "FirstFunc" << endl;
	}
};

class Second : public First
{
public:
	virtual void MyFunc()
	{
		cout << "SecondFunc" << endl;
	}
};

class Third : public Second
{
public:
	virtual void MyFunc()
	{
		cout << "ThirdFunc" << endl;
	}
};

int main(void)
{
	Third * tptr = new Third();
	Second * sptr = tptr;
	First * fptr = sptr;

	fptr->MyFunc();
	sptr->MyFunc();
	tptr->MyFunc();
	delete tptr;
	return 0;
}
#elif 0
/*	EmployeeManager4.cpp
	오렌지 미디어 확장성 문제 해결! 
	virtual 선언을 통해 만약 Employee 포인터가 하위 class를 가리키고 있다면, 그 함수를 overiding 해서 사용하도록 한다! 
	Employee 클래스에 GetPay함수와 ShowSalaryInfo 함수를 추가로 정의하고, 이를 가상함수로 선언한다. */
#include <iostream>
#include <cstring>
using namespace std;

class Employee
{
private:
	char name[100];
public:
	Employee(char * name)
	{
		strcpy_s(this->name, strlen(name)+1, name);
	}
	void ShowYourName() const
	{
		cout << "name: " << name << endl;
	}
	virtual int GetPay() const
	{
		return 0;
	}
	virtual void ShowSalaryInfo() const		// 만약 Employee 포인터가 하위 class를 가리키고 있다면 그 함수를 overiding 해서 사용하도록 한다!  
	{  }
};

class PermanentWorker : public Employee
{
private:
	int salary;
public:
	PermanentWorker(char * name, int money)
		: Employee(name), salary(money)
	{  }
	int GetPay() const
	{
		return salary;
	}
	void ShowSalaryInfo() const
	{
		ShowYourName();
		cout << "salary: " << GetPay() << endl << endl;
	}
};

class TemporaryWorker : public Employee
{
private:
	int workTime;
	int payPerHour;
public:
	TemporaryWorker(char * name, int pay)
		: Employee(name), workTime(0), payPerHour(pay)
	{  }
	void AddWorkTime(int time)
	{
		workTime += time;
	}
	int GetPay() const
	{
		return workTime*payPerHour;
	}
	void ShowSalaryInfo() const
	{
		ShowYourName();
		cout << "salary: " << GetPay() << endl << endl;
	}
};

class SalesWorker : public PermanentWorker
{
private:
	int salesResult;    // 월 판매실적
	double bonusRatio;    // 상여금 비율 
public:
	SalesWorker(char * name, int money, double ratio)
		: PermanentWorker(name, money), salesResult(0), bonusRatio(ratio)
	{  }
	void AddSalesResult(int value)
	{
		salesResult += value;
	}
	int GetPay() const
	{
		return PermanentWorker::GetPay()
			+ (int)(salesResult*bonusRatio);
	}
	void ShowSalaryInfo() const
	{
		ShowYourName();
		cout << "salary: " << GetPay() << endl << endl;
	}
};

class EmployeeHandler
{
private:
	Employee* empList[50];
	int empNum;
public:
	EmployeeHandler() : empNum(0)
	{ }
	void AddEmployee(Employee* emp)
	{
		empList[empNum++] = emp;
	}
	void ShowAllSalaryInfo() const
	{

		for (int i = 0; i<empNum; i++)
			empList[i]->ShowSalaryInfo();

	}
	void ShowTotalSalary() const
	{
		int sum = 0;

		for (int i = 0; i<empNum; i++)
			sum += empList[i]->GetPay();

		cout << "salary sum: " << sum << endl;
	}
	~EmployeeHandler()
	{
		for (int i = 0; i<empNum; i++)
			delete empList[i];
	}
};

int main(void)
{
	// 직원관리를 목적으로 설계된 컨트롤 클래스의 객체생성
	EmployeeHandler handler;

	// 정규직 등록
	handler.AddEmployee(new PermanentWorker("KIM", 1000));
	handler.AddEmployee(new PermanentWorker("LEE", 1500));

	// 임시직 등록
	TemporaryWorker * alba = new TemporaryWorker("Jung", 700);
	alba->AddWorkTime(5);	// 5시간 일한결과 등록
	handler.AddEmployee(alba);

	// 영업직 등록
	SalesWorker * seller = new SalesWorker("Hong", 1000, 0.1);
	seller->AddSalesResult(7000);	// 영업실적 7000
	handler.AddEmployee(seller);

	// 이번 달에 지불해야 할 급여의 정보
	handler.ShowAllSalaryInfo();

	// 이번 달에 지불해야 할 급여의 총합
	handler.ShowTotalSalary();
	return 0;
}
#endif
#endif 

/*	Pure Virtual Function and Abstract Class

	EmployeeManager4.cpp를 한번더 개선할 수 있다.

	※ Employee class는 일종의 공통 규약을 의미하며, 객체 생성을 목적으로 정의되지 않는 class이다. 
		-> Employee class 의 생성은 불필요한 행동이다. 
		따라서, 이를 막기 위한 Pure virtual Function 필요 
		virtual [함수 선언] = 0; 
	순수 가상함수란, 함수의 몸체가 정의되지 않는 함수 ; 명시적으로 몸체를 정의하지 않았음을 컴파일러에게 알림
		-> 순수 가상함수가 선언된 class 의 object 생성 불가능	
	
	하나이상 pure virtual function을 갖는  class = Abstract Class (객체생성이 불가능한 class)라한다. 	*/
#if 0
#include <iostream>
#include <cstring>
using namespace std;

class Employee
{
private:
	char name[100];
public:
	Employee(char * name)
	{
		strcpy_s(this->name, strlen(name)+1, name);
	}
	void ShowYourName() const
	{
		cout << "name: " << name << endl;
	}
	virtual int GetPay() const = 0;
	virtual void ShowSalaryInfo() const = 0;
};

class PermanentWorker : public Employee
{
private:
	int salary;
public:
	PermanentWorker(char * name, int money)
		: Employee(name), salary(money)
	{  }
	int GetPay() const
	{
		return salary;
	}
	void ShowSalaryInfo() const
	{
		ShowYourName();
		cout << "salary: " << GetPay() << endl << endl;
	}
};

class TemporaryWorker : public Employee
{
private:
	int workTime;
	int payPerHour;
public:
	TemporaryWorker(char * name, int pay)
		: Employee(name), workTime(0), payPerHour(pay)
	{  }
	void AddWorkTime(int time)
	{
		workTime += time;
	}
	int GetPay() const
	{
		return workTime*payPerHour;
	}
	void ShowSalaryInfo() const
	{
		ShowYourName();
		cout << "salary: " << GetPay() << endl << endl;
	}
};

class SalesWorker : public PermanentWorker
{
private:
	int salesResult;    // 월 판매실적
	double bonusRatio;    // 상여금 비율 
public:
	SalesWorker(char * name, int money, double ratio)
		: PermanentWorker(name, money), salesResult(0), bonusRatio(ratio)
	{  }
	void AddSalesResult(int value)
	{
		salesResult += value;
	}
	int GetPay() const
	{
		return PermanentWorker::GetPay()
			+ (int)(salesResult*bonusRatio);
	}
	void ShowSalaryInfo() const
	{
		ShowYourName();
		cout << "salary: " << GetPay() << endl << endl;
	}
};

class EmployeeHandler
{
private:
	Employee* empList[50];
	int empNum;
public:
	EmployeeHandler() : empNum(0)
	{ }
	void AddEmployee(Employee* emp)
	{
		empList[empNum++] = emp;
	}
	void ShowAllSalaryInfo() const
	{

		for (int i = 0; i<empNum; i++)
			empList[i]->ShowSalaryInfo();

	}
	void ShowTotalSalary() const
	{
		int sum = 0;

		for (int i = 0; i<empNum; i++)
			sum += empList[i]->GetPay();

		cout << "salary sum: " << sum << endl;
	}
	~EmployeeHandler()
	{
		for (int i = 0; i<empNum; i++)
			delete empList[i];
	}
};

int main(void)
{
	// 직원관리를 목적으로 설계된 컨트롤 클래스의 객체생성
	EmployeeHandler handler;

	// 정규직 등록
	handler.AddEmployee(new PermanentWorker("KIM", 1000));
	handler.AddEmployee(new PermanentWorker("LEE", 1500));

	// 임시직 등록
	TemporaryWorker * alba = new TemporaryWorker("Jung", 700);
	alba->AddWorkTime(5);	// 5시간 일한결과 등록
	handler.AddEmployee(alba);

	// 영업직 등록
	SalesWorker * seller = new SalesWorker("Hong", 1000, 0.1);
	seller->AddSalesResult(7000);	// 영업실적 7000
	handler.AddEmployee(seller);

	// 이번 달에 지불해야 할 급여의 정보
	handler.ShowAllSalaryInfo();

	// 이번 달에 지불해야 할 급여의 총합
	handler.ShowTotalSalary();
	return 0;
}
#endif

/*	다형성(Polymorphism)
	가상함수의 호출 특성; 문장은 같은데 결과는 다르다! */
#if 0
/*	fptr은 First 형 포인터지만, MyFunc을 virtual function으로 정의되어있어, 가리키는 자료형에 따른 overiding이 가능하다
	따라서, MyFunc의 결과는 다형성을 가지게 된다.*/
#include <iostream>
using namespace std;

class First
{
public:
	virtual void MyFunc()
	{
		cout << "FirstFunc" << endl;
	}
};

class Second : public First
{
public:
	virtual void MyFunc()
	{
		cout << "SecondFunc" << endl;
	}
};

class Third : public Second
{
public:
	virtual void MyFunc()
	{
		cout << "ThirdFunc" << endl;
	}
};

int main(void)
{
	First * fptr = new First();
	fptr->MyFunc();
	delete fptr;

	fptr = new Second();
	fptr->MyFunc();
	delete fptr;
	return 0;
}
#endif

// 08-3
/*	Virtual Destructor(가상 소멸자)
		각 상속 관계에 놓인 class의 생성자에서 동적 할당이 이뤄질 경우, 
			pointer를 통해 상속관계 에 놓인 class를 가리키게 한다면, 소멸자에게 문제가 생길 수 있다(Memory Leak발생).
			따라서, pointer의 변수형에 상관없이 모든 소멸자가 호출(소멸자의 연속적 호출) 되도록, 가상 소멸자 필요! 	*/
#if 0
#include <iostream>
using namespace std;

class First
{
private:
	char * strOne;
public:
	First(char * str)
	{
		strOne = new char[strlen(str) + 1];
	}
	virtual ~First()
	{
		cout << "~First()" << endl;
		delete[]strOne;
	}
};

class Second : public First
{
private:
	char * strTwo;
public:
	Second(char * str1, char * str2) : First(str1)
	{
		strTwo = new char[strlen(str2) + 1];
	}
	virtual ~Second()
	{
		cout << "~Second()" << endl;
		delete[]strTwo;
	}
};

int main(void)
{
	First * ptr = new Second("simple", "complex");
	delete ptr;
	return 0;
}
#endif

/*	참조자의 참조 가능성
	pointer와 마찬가지의 결과가 reference에도 적용된다. 
	virtual 선언을 통해, 
	reference의 tpye에 따라 결정되는것이 아닌, reference가 참조하는 객체의 함수를 쓰도록 할 수 있다.
	※	void GoodFunction(const First &ref){...} 에서
		First 객체 or First객체를 상속하는 객체 가 인자로 들어갈 수 있다. 
		ref를 사용하여 함수내에서 member 를 call할때, class에 virtual 선언이 있다면, 
		실제 참조하는 객체에 해당하는 member를 call 할 수 있다.
	*/
//  
#if 0
// ReferenceAttribute.cpp
#include <iostream>
using namespace std;

class First
{
public:
	void FirstFunc()
	{
		cout << "FirstFunc()" << endl;
	}
	virtual void SimpleFunc()
	{
		cout << "First's SimpleFunc()" << endl;
	}
};

class Second : public First
{
public:
	void SecondFunc()
	{
		cout << "SecondFunc()" << endl;
	}
	virtual void SimpleFunc()
	{
		cout << "Second's SimpleFunc()" << endl;
	}
};

class Third : public Second
{
public:
	void ThirdFunc()
	{
		cout << "ThirdFunc()" << endl;
	}
	virtual void SimpleFunc()
	{
		cout << "Third's SimpleFunc()" << endl;
	}
};

int main(void)
{
	Third obj;
	obj.FirstFunc();
	obj.SecondFunc();
	obj.ThirdFunc();
	obj.SimpleFunc();

	Second & sref = obj;
	sref.FirstFunc();
	sref.SecondFunc();
	sref.SimpleFunc();

	First & fref = obj;
	fref.FirstFunc();
	fref.SimpleFunc();
	return 0;
}
#endif 