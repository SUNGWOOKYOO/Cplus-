// [Chap3]

// RacingMain.cpp ; Carline class
/* Class���� �������� ���� namespace�� enum ��� 
	Class �� class specifier : public, private, protected �� ���� member ���� �����ȴ�. 
	�⺻������ �������� private member�̹Ƿ� member �Լ��� ���� ������ �����ϴ�!
	�� class�� ����ü �� �ٸ��� 
	- �������� ������ class specifier�� ���� ���� ���� ����
	- class������ ���� ���� �����ڸ� ���� ���� ������, ��� ������ �Լ��� private ���� �����
	- sturture������ ������ ���� ��� �������� ������, ��� ���� �� �Լ��� public���� ����ȴ�.  */
/* Class���� Inline �Լ� ��� 
	- �ζ��� �Լ� ���� ����ȿ� inline �Լ� ���Ǹ� �־���Ѵ� 
	why? �ζ��� �Լ��� 
	������ �������� �Լ��� ȣ�� ���� �ִ°��� �Լ��� ��ü�κ��� ���� �Ǿ���ϹǷ�
	Ŭ���� ����� ������ ���Ͽ� ����Ǿ� �����Ϸ��� ���ÿ� ������ �� �ְ� �ؾ��Ѵ�.*/
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
/*	Point������ ���е� Rectangle class
	Point class �� Rectangle class
	Information Hiding(��������) : private member �� ���ؼ� ���ѵ� ������θ� ������ ����ؼ� �߸��� ���� ������� �ʵ��� �Ѵ�. 
	�� private member�� access function�� ���� �ٷ�����. 
		- access function �� �⺻������ member ������ ������ �� �ִ� �ɷ��� �����Ƿ�,  
		  ����ڰ� private member ������ ��ġ �ʴ� ���, const �Լ��μ� access function�� ���� �ؾ� �Ѵ�
		  ; ��, const �����ڸ� �̿� �� class ��ü�� argument�� �ϴ� �Լ� ���ο��� ȣ��Ǵ� ��ü�� access function�� const access function�̾���Ѵ�.  */
#if 0
#include<iostream>
#include "Point.h"
#include "Rectangle.h"
using namespace std;

int main(void)
{
	Point pos1;
	if (!pos1.InitMembers(-2, 4))		// access function�� ���� private member�� �ʱ�ȭ �ϹǷ� ���������� Information Hiding �� ���� �� ���ִ�. 
		cout << "�ʱ�ȭ ����" << endl;
	if (!pos1.InitMembers(2, 4))
		cout << "�ʱ�ȭ ����" << endl;

	Point pos2;
	if (!pos2.InitMembers(5, 9))
		cout << "�ʱ�ȭ ����" << endl;

	Rectangle rec;
	if (rec.InitMembers(pos2, pos1))
		cout << "���簢�� �ʱ�ȭ ����" << endl;

	if (rec.InitMembers(pos1, pos2))
		cout << "���簢�� �ʱ�ȭ ����" << endl;

	rec.ShowRecInfo();
	return 0;
}

#endif
 
/*	Encapsulation(ĸ��ȭ) : �����ִ� �Լ��� ������ �ϳ��� Ŭ���� �ȿ� ���°� ; ���� Ŭ�������� �ϳ��� Ŭ������ �ʿ信 ���� ���� ���� ��ɵ��� ȿ�������� ����ϵ��� �Ѵ�.
	�� encapsulation �������� access specifier ����� const�� ����� �ϸ� �������� Information Hiding�� ������ encapsulation �� ���� �� �� �ִ� */
#if 0
#include <iostream>
using namespace std; 

class SinivelCap    // �๰ óġ�� ĸ��
{
public:
	void Take() const { cout << "�๰�� ��~ ���ϴ�." << endl; }
};

class SneezeCap    // ��ä�� óġ�� ĸ��
{
public:
	void Take() const { cout << "��ä�Ⱑ �ܽ��ϴ�." << endl; }
};

class SnuffleCap   // �ڸ��� óġ�� ĸ��
{
public:
	void Take() const { cout << "�ڰ� �� �ո��ϴ�." << endl; }
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
	void TakeCONTAC600(const CONTAC600 &cap) const { cap.Take(); }		// const CONTAC600 &cap �� ���ڷ� �������Ƿ� cap.Take()�� �������Ƿ� Take�� const �Լ� �����Ѵ�.
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
/*	Constructor(������) :  ��ü ������ ���� ȣ��Ǹ� ��ü�� �ʱ�ȭ �� �� �ִ�. 
	�� overloading, default �� setting ���� 	
	�� ��ü ������ �Լ��� ���� ����ó�� ���� �ȵȴ�; C++������ �Լ� ���� �������θ� ����ϱ�� ����ߴ�. - [classtype] obj ();  function prototype declaration
	�� �����ڴ� �ݵ�� ȣ�� �ȴ�(������ ���� ���� ������ ����Ʈ ������ ȣ���)
	�� Member Initializer �� ����ϸ� private member ���� �� ��ü �ɹ� ������ �ʱ�ȭ �Ҽ� ������, �̶�, ����� ���ÿ� �ʱ�ȭ�� �̷����� ȿ������ �ڵ�� �����Ѵ�.
	�� Const �ɹ� ����(= const  �ɹ� ���)�� �����ڴ� ����� ���ÿ� �ʱ�ȭ �ؾ��ϴµ� Member Initializer�� �̿��ϸ� �ʱ�ȭ�� �����ϴ� .      
	�� �����Ҵ��� ���� class object�� ������ ���, �ݵ�� new �� �̿��Ͽ� ���� �ؾ��Ѵ�. malloc�� �̿��� ���, ������ ȣ���� ���� �ʴ´�. - Ŭ������ ũ�� �����θ� ����Ʈ ������ ���� �Ҵ��� �̷����
	�� access function�� ����(�����Ҵ��� ��ü�� ���������� ��ȯ����) Ŭ���� ���ο��� �����Ҵ��� ���� ��ü�� ������ ���, �����ڸ� private���� �α⵵ �Ѵ�! ; �������� �Ҵ絵�� �޸� ������ ���� = �����ڰ� �������� ���*/
#if 0

//Encaps2.cpp ;
#include <iostream>
using namespace std;

class SimpleClass
{
	int num1;
	int num2;

public:
	SimpleClass(int n1 = 0, int n2 = 0)	// default �� setting ���� 
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
	SimpleClass sc1();    // �Լ��� ����!

	SimpleClass *ptr = new SImpleclass; // �����Ҵ��� ���� ����!  SimpleClass *ptr = new SImpleclass();, SimpleClass *ptr = new SImpleclass(100,200); ���� 

	SimpleClass mysc = sc1();
	mysc.ShowData();
	return 0;
}

SimpleClass sc1()				// �Լ��� ����
{
	SimpleClass sc(20, 30);
	return sc;
}

#elif 0
/*	RectangleConstructor.cpp ; Point, Rectangle class�� Constructor �߰� ���� 
	Member initializer �� �̿��� ������ ȣ�� ; �����ڸ� ȣ���԰� ���ÿ� �ɹ� ��ü�� �ʱ�ȭ�� ���� �ɹ� ��ü�� �����ڵ� ȣ�� �Ѵ�.	 */
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
/*�� Const �ɹ� ����(= const  �ɹ� ���)�� �����ڴ� ����� ���ÿ� �ʱ�ȭ �ؾ��ϴµ� Member Initializer�� �̿��ϸ� �ʱ�ȭ�� �����ϴ� .  */
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
		: ref(r), num(n)		// Member initializer�� ���� BBB ��ü�� member class reference &ref�� member const reference &num �� �ʱ�ȭ �� �� �ִ�.
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
// �� �����Ҵ��� ���� class object�� ������ ���, �ݵ�� new �� �̿��Ͽ� ���� �ؾ��Ѵ�.malloc�� �̿��� ���, ������ ȣ���� ���� �ʴ´�
#include <iostream>
using namespace std;
class AAA
{	
	int num; 
public: 
	AAA() { cout << "I'm constructor!" << endl; } // ����Ʈ ������
	int GetNum(){ return num;}	//access function 
};
int main()
{
	AAA *ptr1 = new AAA; 
	AAA *ptr2 = (AAA*)malloc(sizeof(AAA));	// �����ڰ� ȣ����� �ʴ´�! -> �ɹ��� �ʱ�ȭ ��ų �� ����. ������ �� �� �ִ�. 
	return 0;
}

#elif 0			// PrivateConstructor.cpp
// �� access function�� ����(�����Ҵ��� ��ü�� ���������� ��ȯ����) Ŭ���� ���ο��� �����Ҵ��� ���� ��ü�� ������ ���, �����ڸ� private���� �α⵵ �Ѵ�!
#include <iostream>
using namespace std;

class AAA
{
private:
	int num;

public:
	AAA() : num(0) {}						// ����Ʈ ������ num = 0 ���� member initializer�� ���� �ʱ�ȭ
	AAA& CreateInitObj(int n) const			// Heap ������ �Ҵ�� ���� = ���� �̹Ƿ� reference�̿� �� ���� ���� 
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

	AAA &obj1 = base.CreateInitObj(3);		//  Heap ������ �Ҵ�� ���� = ���� �̹Ƿ� reference�̿� �� ���� ���� ���� �����Ѵ�. 
	obj1.ShowNum();

	AAA &obj2 = base.CreateInitObj(12);
	obj2.ShowNum();

	delete &obj1;
	delete &obj2;
	return 0;
}
#endif 

// ���� 04-3
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

			cout << "���" << endl;

			break;

		case SENIOR:

			cout << "����" << endl;

			break;

		case ASSIST:

			cout << "�븮" << endl;

			break;

		case MANAGER:

			cout << "����" << endl;

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

		cout << "�̸�: " << name << endl;			//*(name) �� ����ϸ� name[0] �� ����Ű�� ���� ��µȴ� 

		cout << "ȸ��: " << cname << endl;

		cout << "��ȭ��ȣ: " << num << endl;

		cout << "����: ";

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



//��ó: http://luv4ever.tistory.com/113?category=493441 [�⵿��� ��α�]
#endif 


// ObjArr 
/*	��ü �迭�� �ѹ��� �������� object�� �����ϹǷ� �̶�, member ������ �ʱ�ȭ�� ���� ���־���Ѵ�. �̶� 2���� ���
	1. object array�� �����ϴ°��: 
		default �����ڸ� ȣ�� �ɼ� �ۿ� ����. ���� access function�� ���� �ʱ�ȭ �Ѵ�
		
	2. object array pointer�� �����ϴ°��: 
		Heap ������ �����Ҵ��� �ϵ��� �����ڸ� �����Ͽ� �����ڸ� ���� �ʱ�ȭ�� �Ѵ�.  
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
		cout << "�̸�: " << name << ", ";
		cout << "����: " << age << endl;
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
	Person parr[3];					// object array �� ����� ��� defalut �����ڸ� ȣ���

	char namestr[100];
	char * strptr;
	int age;
	int len;

	for (int i = 0; i<3; i++)
	{
		cout << "�̸�: ";
		cin >> namestr;
		cout << "����: ";
		cin >> age;

		len = strlen(namestr) + 1;
		strptr = new char[len];
		strcpy_s(strptr, len, namestr);
		parr[i].SetPersonInfo(strptr, age);		// aceess function�� ���� �ʱ�ȭ �ߴ�.
	}

	parr[0].ShowPersonInfo();
	parr[1].ShowPersonInfo();
	parr[2].ShowPersonInfo();
	return 0;
}
#elif 1
int main(void)
{
	Person * parr[3];						// object array pointer�� �̿��Ͽ� 

	char namestr[100];
	char * strptr;
	int age;
	int len;

	for (int i = 0; i<3; i++)
	{
		cout << "�̸�: ";
		cin >> namestr;
		cout << "����: ";
		cin >> age;

		parr[i] = new Person(namestr, age);		// Constructor �� ���� �ʱ�ȭ �ߴ�.
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
/*	This pointer ��� 
	this pointer��  �ɹ��Լ� ������ this ��� �����͸� ����Ͽ� ��ü �ڽ��� ����Ű�� �뵵�� ���δ�.
	�ּҰ��� �ڷ����� ������ ���� ���� �����ʹ�.
	�� member initializer������ this �����͸� ����� �� ����. 
	�ַ�, member ������ argument(�Ű�����)�� �̸��� ������ ���, this �����͸� �̿��Ͽ� �̸� �������µ� ���δ�.
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
	: num1(num1), num2(num2)			// num1(this->num1) �ϸ� error ! 
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
/*	� class�� �ɹ� �Լ��� ��ȯ���� �ڱ� class���� �������� ��ȯ�� ���, �̶�, this �����͸� ����Ͽ� ��ü �ڽ��� ������ �� �ִ� ������(Self-Reference)�� ��ȯ�ϰԵȴ�.
	�� ������ �Ҷ�, ������ ����(������) �� ���޵ȴٰ� ��������
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
		cout << "��ü����" << endl;
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
	SelfRef &ref = obj.Adder(2);	//obj�� �Ǵٸ� �̸��� ref�� �ȴ�. 

	obj.ShowTwoNumber();
	ref.ShowTwoNumber();

	ref.Adder(1).ShowTwoNumber().Adder(2).ShowTwoNumber();	// �ӽ����� ���� ��ü�� recursive�� ȣ���� �̲��� �ִ�.
	return 0;
}
#endif

