// [chap 8]
/*	����� Is - a ���迡�� ���δ�.
	����� ���� ����Ծ��� ������ �� �ִ�.
	������ �̵�� �޿� Ȯ�强 ������ �ָ��� ��	*/

// 08-1 ; ObjectPointer
/*	base class �� �����ʹ� derived class �� ����ų �� �ִ�.  	
	AAA - BBB - CCC ���迡 �ִٸ�
	AAA * p = new BBB; 
	AAA * p = new CCC;
	BBB * p = new CCC; 
	�����ϴ�			*/
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

/*	class �� �����͸� �̿��Ͽ� ��ӵǴ� Ŭ������ ����Ű�� �� �� �ִ�. 
	������ �̵�� �޿� ���� Ȯ�强 ������ 1���� �ذ�
	��	��Ӱ��迡�� �Լ��� �������̵� �Ǹ� derived class�� �Լ��� �켱�ȴ�.
		�ּ�ó���� �κ��� compile error�� �߻��ϴµ�, ���� �Լ��� ������ �˾ƾ� ���ذ� �����ϴ�.
		(������ ���ϸ�, C++ �����Ϸ��� ������ ������ ���ɼ� ���θ� �Ǵ��Ҷ�, �������� �ڷ����� �������� �Ǵ�����, ���� ����Ű��
		��ü�� �ڷ����� �������� �Ǵ����� �ʴ´�. ����, Employ pointer�� ShowSalaryInfo() �Լ��� GetPay() �Լ��� ã�� ���Ѵ�.)*/
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
	// ���������� �������� ����� ��Ʈ�� Ŭ������ ��ü����
	EmployeeHandler handler;

	// ���� ���
	handler.AddEmployee(new PermanentWorker("KIM", 1000));
	handler.AddEmployee(new PermanentWorker("LEE", 1500));
	handler.AddEmployee(new PermanentWorker("JUN", 2000));

	// �̹� �޿� �����ؾ� �� �޿��� ����
	handler.ShowAllSalaryInfo();

	// �̹� �޿� �����ؾ� �� �޿��� ����
	handler.ShowTotalSalary();
	return 0;
}
#endif

// 08-2 ;	virtual Fucntion 
/*	C++ �����Ϸ��� ������ ������ ���ɼ� ���θ� �Ǵ��Ҷ�, �������� �ڷ����� �������� �Ǵ�����, ���� ����Ű��
	��ü�� �ڷ����� �������� �Ǵ����� �ʴ´�. 
	��	Base pointer�� Base���� ����ų �� �� �ְ�, Derived���� ����ų �� �� �����Ƿ� 
		Base�� pointer�� Derived�� class�� ��� ȣ���� �ϸ� ���� �߻�	
		��, pointer ���� �ش��ϴ� Ŭ������ ���ǵ� ������� ������ �����ϴ�.*/
#if 0
#if 0
#include <iostream>
using namespace std;
class Base { public: void BaseFunc(){} };
class Derived :public Base { public: void DerivedFunc(){} };
int main()
{
	Base *p = new Derived();	// poineter�� ��� class�� �Ҵ�� Derived�� ����Ű�� ���� ���������� data type�� Base�� �������̴�. 
	//p->DerivedFunc();		// pointer�� Base �� �������̹Ƿ� DerivedFunc�� ã�� ���Ѵ�.
	//Derived * dp = p;		// poineter�� Base �� �������̹Ƿ� Derived�� ����� ���Կ������� ���Ѵ�. 
}
#elif 0
/*	pointer ���� �ش��ϴ� Ŭ������ ���ǵ� ������� ������ �����ϴ�	*/
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
/*	���� �Լ��� �ʿ伺 :
	�����Լ��� ������, ���� ����Ű�� �ڷ����� �������� �Ǵ��Ͽ� overriding �ϰ� ���� �ʴ´�. */
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
	Third * tptr = new Third();		// ���� ����Ű�� �ڷ��� Third class
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

/*	�����Լ��� �ʿ伺�� ����! ; ������ �̵�� Ȯ�强 ���� �ذ�! 
	pointer ���� �ش��ϴ� Ŭ������ ���ǵ� ������� ������ �����ϴ� 
	-> �����Լ��� �־�� ���� ����Ű�� �ڷ����� �������� �Ǵ��Ͽ� overriding �ϰ� �� �� �ִ�.
	�� Virtual Function �� ��ü ������ �����̴�. ; C++, JAVA, C# ... ���� ����	
		virtual [�Լ� ����]				
		�����Լ��� ����ϸ�, �������� �ڷ����� ������� ȣ�� ����� �������� �ʰ�, 
		������ ������ ������ ����Ű�� ��ü�� �����Ͽ� ȣ���� ����� �����Ѵ�. */
#if 0
#if 0
/* virtual function�� ���� overriding */
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
	������ �̵�� Ȯ�强 ���� �ذ�! 
	virtual ������ ���� ���� Employee �����Ͱ� ���� class�� ����Ű�� �ִٸ�, �� �Լ��� overiding �ؼ� ����ϵ��� �Ѵ�! 
	Employee Ŭ������ GetPay�Լ��� ShowSalaryInfo �Լ��� �߰��� �����ϰ�, �̸� �����Լ��� �����Ѵ�. */
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
	virtual void ShowSalaryInfo() const		// ���� Employee �����Ͱ� ���� class�� ����Ű�� �ִٸ� �� �Լ��� overiding �ؼ� ����ϵ��� �Ѵ�!  
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
	int salesResult;    // �� �ǸŽ���
	double bonusRatio;    // �󿩱� ���� 
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
	// ���������� �������� ����� ��Ʈ�� Ŭ������ ��ü����
	EmployeeHandler handler;

	// ������ ���
	handler.AddEmployee(new PermanentWorker("KIM", 1000));
	handler.AddEmployee(new PermanentWorker("LEE", 1500));

	// �ӽ��� ���
	TemporaryWorker * alba = new TemporaryWorker("Jung", 700);
	alba->AddWorkTime(5);	// 5�ð� ���Ѱ�� ���
	handler.AddEmployee(alba);

	// ������ ���
	SalesWorker * seller = new SalesWorker("Hong", 1000, 0.1);
	seller->AddSalesResult(7000);	// �������� 7000
	handler.AddEmployee(seller);

	// �̹� �޿� �����ؾ� �� �޿��� ����
	handler.ShowAllSalaryInfo();

	// �̹� �޿� �����ؾ� �� �޿��� ����
	handler.ShowTotalSalary();
	return 0;
}
#endif
#endif 

/*	Pure Virtual Function and Abstract Class

	EmployeeManager4.cpp�� �ѹ��� ������ �� �ִ�.

	�� Employee class�� ������ ���� �Ծ��� �ǹ��ϸ�, ��ü ������ �������� ���ǵ��� �ʴ� class�̴�. 
		-> Employee class �� ������ ���ʿ��� �ൿ�̴�. 
		����, �̸� ���� ���� Pure virtual Function �ʿ� 
		virtual [�Լ� ����] = 0; 
	���� �����Լ���, �Լ��� ��ü�� ���ǵ��� �ʴ� �Լ� ; ��������� ��ü�� �������� �ʾ����� �����Ϸ����� �˸�
		-> ���� �����Լ��� ����� class �� object ���� �Ұ���	
	
	�ϳ��̻� pure virtual function�� ����  class = Abstract Class (��ü������ �Ұ����� class)���Ѵ�. 	*/
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
	int salesResult;    // �� �ǸŽ���
	double bonusRatio;    // �󿩱� ���� 
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
	// ���������� �������� ����� ��Ʈ�� Ŭ������ ��ü����
	EmployeeHandler handler;

	// ������ ���
	handler.AddEmployee(new PermanentWorker("KIM", 1000));
	handler.AddEmployee(new PermanentWorker("LEE", 1500));

	// �ӽ��� ���
	TemporaryWorker * alba = new TemporaryWorker("Jung", 700);
	alba->AddWorkTime(5);	// 5�ð� ���Ѱ�� ���
	handler.AddEmployee(alba);

	// ������ ���
	SalesWorker * seller = new SalesWorker("Hong", 1000, 0.1);
	seller->AddSalesResult(7000);	// �������� 7000
	handler.AddEmployee(seller);

	// �̹� �޿� �����ؾ� �� �޿��� ����
	handler.ShowAllSalaryInfo();

	// �̹� �޿� �����ؾ� �� �޿��� ����
	handler.ShowTotalSalary();
	return 0;
}
#endif

/*	������(Polymorphism)
	�����Լ��� ȣ�� Ư��; ������ ������ ����� �ٸ���! */
#if 0
/*	fptr�� First �� ����������, MyFunc�� virtual function���� ���ǵǾ��־�, ����Ű�� �ڷ����� ���� overiding�� �����ϴ�
	����, MyFunc�� ����� �������� ������ �ȴ�.*/
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
/*	Virtual Destructor(���� �Ҹ���)
		�� ��� ���迡 ���� class�� �����ڿ��� ���� �Ҵ��� �̷��� ���, 
			pointer�� ���� ��Ӱ��� �� ���� class�� ����Ű�� �Ѵٸ�, �Ҹ��ڿ��� ������ ���� �� �ִ�(Memory Leak�߻�).
			����, pointer�� �������� ������� ��� �Ҹ��ڰ� ȣ��(�Ҹ����� ������ ȣ��) �ǵ���, ���� �Ҹ��� �ʿ�! 	*/
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

/*	�������� ���� ���ɼ�
	pointer�� ���������� ����� reference���� ����ȴ�. 
	virtual ������ ����, 
	reference�� tpye�� ���� �����Ǵ°��� �ƴ�, reference�� �����ϴ� ��ü�� �Լ��� ������ �� �� �ִ�.
	��	void GoodFunction(const First &ref){...} ����
		First ��ü or First��ü�� ����ϴ� ��ü �� ���ڷ� �� �� �ִ�. 
		ref�� ����Ͽ� �Լ������� member �� call�Ҷ�, class�� virtual ������ �ִٸ�, 
		���� �����ϴ� ��ü�� �ش��ϴ� member�� call �� �� �ִ�.
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