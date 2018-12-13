	// [Chap9]

// 09-1
/*	����Լ��� ��ü 
	C	sytle coding 
	C++	sytle coding
	�� ���� �˼� �ִ���:	��������� ��ü ���� ����������, 
							����Լ��� �޸� �� ������ ������ ��ġ�ϰ�, �� �Լ������ǵ� Ŭ������ ��� ��ü�� �̸� �����ϴ� ���¸� ����		*/
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

// Ŭ���� Data�� �䳻�� ����
typedef struct Data
{
	int data;
	void(*ShowData)(Data*);		// �Լ� ������ ���� 
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


// ������ ����� main �Լ�
int main(void)
{
	Data obj1 = { 15, ShowData, Add };	// �Լ� �����͸� ���ڷ� �ޱ� ������ �Լ� �̸��� �־ �Լ��� ����Ű�� �Ͽ���. 
	Data obj2 = { 7, ShowData, Add };

	obj1.Add(&obj1, 17);
	obj2.Add(&obj2, 9);
	obj1.ShowData(&obj1);
	obj2.ShowData(&obj2);
	return 0;
};

#endif

/*	�����Լ� ���ۿ���
	C++ style�� �ڵ�����
	��	�Ѱ� �̻��� �����Լ��� �����ϴ� Ŭ������ ���ؼ� �����Ϸ��� �����Լ� ���̺�(V-Table)�� �����. 
		main �Լ��� ȣ�� �Ǳ� ������ V-Table�� �޸� ������ �Ҵ�ȴ�. ��ü ������ ����� ����.
		overriding�� �����Լ��� �ּ������� derived class�� V-Table�� ���Ե��� �ʴ´�. 
		��, ������ �������� overriding �� derived class�� member function�� ȣ��Ǵ� ���̴�.	*/
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
/*	���߻���� ��ȣ��	*/
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

/*	virtual ����� ���� �ذ�	
	������ 1���� ȣ��ǵ����� 
	:: ������ ���� V-table�� �̿��Ͽ� ������ �Լ� ����*/
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
		SimpleFunc();		// vitual ������ �ֱ⿡ ������. ���ٸ� MiddleDrivedOne::SimpleFuncOne();
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
		SimpleFunc();		// vitual ������ �ֱ⿡ ������ 
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
		SimpleFunc();	// vitual ������ �ֱ⿡ ������ 
	}
};

int main(void)
{
	cout << "��ü���� �� ..... " << endl;
	LastDerived ldr;						// virtual �������� ���� Base ������ 1���� ȣ���
	cout << "��ü���� �� ..... " << endl;
	ldr.ComplexFunc();
	return 0;
}
#endif
