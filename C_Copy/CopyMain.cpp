// [Chap5]

/*	Foundation of Copying in terms of Object
	�� ����Ʈ ���� �����ڴ� �������� �ʾƵ� �����ϸ�, �ڵ����� ȣ�� �ȴ�. 
		��������ڸ� �����Ҷ���, ������ ������ ����(������ ���� �ʵ�, �ɹ� ������ �����Ͽ� ����)�ϱ� ���� const Ű���带 ���ڿ� �����Ͽ� �̸� �����Ѵ�.
		������, �̷��� ����� ������ ���߽�ų ���ִ�.(���߿� �ڼ���)
		explicit ������ ���� ���������� ���Կ����ڸ� �̿��� ��ü ����, �ʱ�ȭ�� �Ұ��� �ϰ� �� �� �ִ�.
		��  ��������ڴ� ���Կ����� �Ҷ� �׻� ȣ�� �ȴ�. ���ǰ� �ȵǾ� ������ ����Ʈ ��������� ȣ�� 
			����������� ���ڿ� &�� �ݵ�� �־���Ѵ�; ���ٸ�, �����Ͽ��� �߻� ;����������� ȣ���� ���� ������ ������; �ڼ��� ������ ���߿�...*/
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
	//AAA(const AAA &copy) : num1(copy.num1), num2(copy.num2) { cout<<"I'm called! "<<endl;}		// default Copy constructor �� �״�� ������ ������ 
	//explicit AAA(const AAA &copy) : num1(copy.num1), num2(copy.num2) { cout << "I'm called! " << endl; }		// ���������� ���� ������ �� ���� ��ü ���� ��� x 
	void ShowData() { cout << num1 << endl;	cout << num2 << endl; }
};
void main()
{
	// ������ ���� ������ ���� �Է��ϴ� �� ���� copy�� �����̴�.
//	int num = 20; 
//	int &ref = num;
//	const int num = 20; 
//	const int &ref2 = 20;		

	AAA sim1(15, 20); 
	AAA sim2 = sim1; 		// same with ; AAA sim2(sim1);	// AAA(AAA &copy) ���� ���̵� Copy ����? OK! why? default Copy constructor�����Ѵ� in C++

	sim1.ShowData();
	sim2.ShowData();

//	int num(20);		 // same with ; int num = 20;

}
#endif

// 05-2 ; Deep Copy vs Shallow Copy 
/* Shallow Copy ; Default Copy 
	�ع����� : ��� ����(������ ����)�� �����Ҵ��� ���� Heap������ �Ҵ�Ǿ��� ��, ������ �ȴ�.
	= �����ڸ� ���� Copy �ɶ�, ������ ������ ���� �Ǵµ� ����� �����ʹ� ���� Heap ���� ������ ����Ű�� �ִ�. 
	����, 2���� ���δٸ� ��ü�� �ɹ� ������ ���� ������ ����Ű�� �ȴ�.
VS
	Deep Copy : ��������� �����Ҵ�Ǿ�����, ���� ���� ���� �ذ� 
	Copy Constructor �� ���� ���� ������ �̷������, ����Ǵ� �ɹ� ������ ����Ű�� Heap ���� �� ���ϳ� ���� ���� �ٸ� �޸𸮸� ����Ű���� �Ѵ�. */
#if 0
#include <iostream>
#include <cstring>
using namespace std;

class Person
{
	char * name;	// Pointer �ɹ�����  
	int age;
public:
	// ������ ���� ; �����Ҵ��� ���� member ���� �Ҵ� ; 
	Person(char * myname, int myage)
	{
		int len = strlen(myname) + 1;	// �����ڸ� ���� ������ ��� ������ ���� �Ҵ��� ���� Heap ������ ����Ű�� �����Ͽ���. 
		name = new char[len];
		strcpy_s(name, len, myname);
		age = myage;
	}

	// ���� ������ ���� ; ���� ������ �Ҷ� �ڵ����� ȣ�� 
#if 0	// Deep Copy 
	Person(const Person& copy) :age(copy.age)				// ���Կ���� �ڵ����� call 
	{
		name = new char[strlen(copy.name) + 1];				// �Ǵٸ� Heap ���� �Ҵ�
		strcpy_s(name, strlen(copy.name) + 1, copy.name);
	}
#else	// Shaloow Copy
	Person(const Person& copy) : age(copy.age), name(copy.name) { }
#endif

	void ShowPersonInfo() const
	{
		cout << "�̸�: " << name << endl;
		cout << "����: " << age << endl;
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
	Person man2 = man1;					// Default ���� �����ڸ� �̿��Ͽ� �Ҵ� ����(Copy)�� �ϰ� �Ǵµ� �̶�, ���� ������ ����Ű�� ���� �߻�
	man1.ShowPersonInfo();
	man2.ShowPersonInfo();
	return 0;							// ��ü�� 2���ε�, Deep copy�� �̷�� ���� ������, �Ҹ��ڴ� 1�� �ۿ� Call ���� �ʴ´�. : ������ ���� �߻�! �ϳ��� ��ü�� �Ҹ� �� ������ ��ü�� ����Ű�� ���� ������
}
#endif 


// 05-3 ; ���� �������� ȣ�� ����
/*	Case1: ������ ������ ��ü�� �̿��Ͽ� ���ο� ��ü �ʱ�ȭ 
	Case2: call by value ����� �Լ� ȣ�� �������� ��ü�� ���ڷ� �����ϴ� ���
	Case3: ��ü�� ��ȯ�ϵ�, ���������� ��ȯ���� �ʴ°�� ; �ӽð�ü�� ����
������ : ��ü�� �����ؾ��Ѵ�. ��, ������ ���ÿ� ������ �ڷ����� ��ü�� �ʱ�ȭ �ؾ��Ѵ�! 	
���� 3���� Case�� ����� ��Ȳ 3���� example(�޸� ������ �Ҵ�� �ʱ�ȭ�� ���ÿ� �Ͼ�� ��Ȳ). 
1.	int num = num2; 
2.	int SimpleFunc(int n){ ... } ...
	Simple Func(num); ȣ��Ǵ� ���� �Ű����� n�� �Ҵ�� ���ÿ� �ʱ�ȭ! 
3.  int SimpleFunc(int n){ ...  return n;} ...
	int num = 10; 
	cout << SimpleFuc(num) << endl;	����� �Ҷ� ���� ��ȯ�ϸ� ��ȯ�� ���� ������ �޷θ� ������ �Ҵ�Ǿ� ������ �ǰ�, cout�� ���� ����� �����Ѱ�! �ӽú���(���)�� ���� (�������� ���ߵ��� ������ƴ� ���������̹Ƿ�, �� ���� ������ �����ϴ� )  */
#if 0
#include <iostream>
#include <cstring>
using namespace std;

class Person
{
	char * name;	// Pointer �ɹ�����  
	int age;
public:
	// ������ ���� ; �����Ҵ��� ���� member ���� �Ҵ� ; 
	Person(char * myname, int myage)
	{
		int len = strlen(myname) + 1;	// �����ڸ� ���� ������ ��� ������ ���� �Ҵ��� ���� Heap ������ ����Ű�� �����Ͽ���. 
		name = new char[len];
		strcpy_s(name, len, myname);
		age = myage;
	}

	// ���� ������ ���� ; ���� ������ �Ҷ� �ڵ����� ȣ�� 
#if 1	// Deep Copy 
	Person(const Person& copy) :age(copy.age)				// ���Կ���� �ڵ����� call 
	{
		cout << "I'm Deep copy constructor!!" << endl;
		name = new char[strlen(copy.name) + 1];				// �Ǵٸ� Heap ���� �Ҵ�
		strcpy_s(name, strlen(copy.name) + 1, copy.name);
	}
#else	// Shaloow Copy
	Person(const Person& copy) : age(copy.age), name(copy.name) { }
#endif

	void ShowPersonInfo() const
	{
		cout << "�̸�: " << name << endl;
		cout << "����: " << age << endl;
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

/* Temporary Object (�ӽð�ü) �� ���� */
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
	SoSimple& AddNum(int n)		// �������� ��ȯ�ϱ� ������ ��ȯ�ϸ� ���簡 �̷�������ʴ´� (���� ������ ȣ�� X)
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
	cout << "return ����" << endl;
	return ob;
}

int main(void)
{
	SoSimple obj(7);

	// SimeFuncObj�Լ��� ��ȯ�ϴ� obj�� ���纻�� ��������� ��ȯ, �� (�ӽ� ��ü)��ü�� ������� AddNum ȣ��, �̾ AddNum�Լ��� ��ȯ�ϴ� �������� ������� ShowData�Լ� ȣ��
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
/*	- �ӽð�ü�� ���������� �Ѿ�� �ٷ� �Ҹ�Ǿ� ������. 
	- �����ڿ� �����Ǵ� �ӽð�ü�� �ٷ� �Ҹ���� �ʴ´�.
	�� �����ڰ� ��ȯ�ϴ� ���� �ӽð�ü�� �������� �ǹ��Ѵ�. ���� Temparary(200).ShowTemInfo(); �� (�ӽ� ��ü�� ������).ShowTempInfo();�� �ǹ�
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
	SoSimple &tempRef = SimpleFuncObj(obj);			// �ӽð�ü�� �����ϸ� �����ٿ� �������� �ʴ´�! 
	cout << "Return Obj " << &tempRef << endl;
	return 0;
}

#endif 
