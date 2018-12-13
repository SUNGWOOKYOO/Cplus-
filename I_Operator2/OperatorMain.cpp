//	Chap[11]
/*	���� �������� Ư��
1. �������� ������ default ���� ������ ����
2. default ���� �����ڴ� shallow copy
3. ������ ������ ���� �Ҵ��� �Ѵٸ�, deep copy�� ���� define �ؾ��Ѵ�.

�� ������  ������ �� ��ü���� ���� ������ ���� �����ڰ� ȣ���. (copy constructor���� ���� )
pos2 = pos1;	��, pos2.operator=(pos1)					*/

/* default ���Կ����� */
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

	// ����Ʈ ���� �����ڴ� �̷��� �����. 
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

/*	default ���Կ������� ������ -  Deep copy �ʿ� 
	��ü�� 2���ε� �Ҹ��ڰ� 1�� �ٲ� ȣ�� ���� �ʴ´�. - memory�� Leak �߻�!
	��, 2���� ��ü�� ������ Heap ������ ����Ű�� �ִ�.							*/
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

#if 0	// Deep ���� ������ 
	Person& operator=(const Person& ref)
	{
		delete[]name;	//���� ������ �ִ� name ����! 

		int len = strlen(ref.name) + 1;
		name = new char[len];		// Deep copy�� ���� Heap ������ ���ο� �Ҵ� 
		strcpy_s(name, strlen(ref.name) + 1 , ref.name);
		age = ref.age;
		return *this;
	}
#else	// shallow ���� ������(default ���Կ���)
	Person& operator=(const Person& ref)
	{
		age = ref.age;
		name = ref.name;

		return *this;
	}
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
	//Person man2 = man1;					// Default ���� �����ڸ� �̿��Ͽ� �Ҵ� ����(Copy)�� �ϰ� �Ǵµ� �̶�, ���� ������ ����Ű�� ���� �߻�
	Person man2("Yoon Ji yul", 22);
	man2 = man1;							// ���ǵ� Deep ���� �����ڰ� ���ٸ�, default ���� �����ڸ� ���� ���� �ȴ�.

	man1.ShowPersonInfo();
	man2.ShowPersonInfo();
	return 0;							// ��ü�� 2���ε�, Deep copy�� �̷�� ���� ������, �Ҹ��ڴ� 1�� �ۿ� Call ���� �ʴ´�. : ������ ���� �߻�! �ϳ��� ��ü�� �Ҹ� �� ������ ��ü�� ����Ű�� ���� ������
}

#endif 

/*	Copy constructor�� ���� �������� �ٸ��� 
	��Ӱ��� �� �ִ� Ŭ�������� 
	derived Ŭ������ ���� �����ڿ� �ƹ� ��ø� ���� ������ base Ŭ������ ���Կ����ڴ� ȣ����� �ʴ´�. 
	��	����Ʈ derived Ŭ������ ���� �����ڴ� base �����ڸ� ȣ�� �Ѵ�. 
		������, derived Ŭ������ ���� �����ڸ� ����ڰ� ������ ���, ��������� base class ���� ������ ȣ�� �ؾ��� */
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

	// derived class �� ���� �����ڿ��� ��������� ȣ���� ����� �� �κ��� ȣ�� �� �� �ִ�. 
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
	// derived class�� ���� ������ ���ǿ� base ���� �����ڸ� ��������� ȣ�� �ؾ� �Ѵ�. 
	Second& operator=(const Second &ref)
	{
	cout<<"Second& operator=()"<<endl;
#if 1
	/* ��	Remember!!
			ref�� Second �� ������ ������, 
			const First &ref = ref ���� �ϴ�! 
			(Chap8 ... virtual ������ ���� reference�� tpye�� ���� �����Ǵ°��� �ƴ�,
			reference�� �����ϴ� ��ü�� �Լ��� ������ �� �� �ִ�)	*/
	First::operator=(ref);		// base Ŭ������ ���� ������ ȣ���� ���! 
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

/*	 initializer�� ���� ��� ������ �Ǵ� ����
	initializer�� ����ϸ�, ����� ���ÿ� �ʱ�ȭ�� �̷����� ���� 
	��, AAA mem = ref; 
	��������ڸ� ȣ�� 
	
	�Ҵ�(���Կ���)�� ���� �ʱ�ȭ�ϸ�, ����� �ʱ�ȭ�� ���� ������ ���忡�� ����
	��, AAA mem;
		mem = ref;
	��������ڿ� ���Կ����ڰ� �Ѵ� ȣ�� �ȴ�.  */
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

// initializer�� ���� �ʱ�ȭ 
class BBB
{
private:
	AAA mem;
public:
	BBB(const AAA & ref)
		: mem(ref)
	{  }
};

// ���� ������ ���� �ʱ�ȭ 
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
	AAA obj1(12);	// ������ ȣ��
	cout << "*********************" << endl;
	BBB obj2(obj1);	// ���� ������ ȣ��
	cout << "*********************" << endl;
	CCC obj3(obj1);	// ���� ������, ���� ������ ȣ��
	return 0;
}
#endif 

// 11-2		; �迭�� �ε��� ������ overloading 

// �⺻ �ڷ��� ����� �迭 Ŭ���� 
/*	object�� ������� �����ؾ� �ϹǷ�, member function���θ� overloading�� �����ϴ�.
	��	��ȯ���� ���������� �Ͽ� �迭��ҿ� ������ �� �ִ�. 
	��	�����ڸ� ȣ�� �ҽ� array�� �����Ҵ� �ϰ�, �̸� private member �� pointer�� ����Ű�� �Ǵµ� 
		operator[](�ε�����)�� ���� �����ϰ��� �� �������� overloading �ϰ� �ȴ�.	
	��	���翬���ڿ� ���Կ����ڸ� private �ɹ��� �����ν� ����� ������ ��õ������ ���°��� ���� �� �ִ�.
		BoundCheckIntArray arr(5);
		BoundCheckIntArray cpy1(5);
		cpy1 = arr;		// �������� �ʱ� ������ ���´�.			
		
	However, 
		��ȯ���� ���������� �ϱ� ������, operator[]() �� 
		access function�� ����� ���,  
		����, access function�� �Ű������� const ��ü�� �̿��Ͽ� �������� �������� ��쵵, 
		������ ������ �ʷ��Ѵ�! 
		-> const ���� ������ �̿��Ͽ� operator[]()�Լ��� �����ε� �Ѵ�!  
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

	// ���� �����ڿ� ���� �����ڸ� private���� �����ν�, �迭���� ����Ǵ°��� ��õ������ ����
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
		arr[i] = (i + 1) * 11;		//arr.operator[](i)�� �ǹ� 

	for (int i = 0; i < 6; i++)
		cout << arr[i] << endl;

	BoundCheckIntArray copy1(5);
	// copy1=arr;						//���� �����ڿ�, ���Կ����ڸ� private���� �ξ��� ������ �Ұ��� 
	// BoundCheckIntArray copy=arr;
	return 0;
}

#endif

/*	const �Լ��� overloading! 
	access function�� �̿��Ͽ� operator[] �Լ��� ����ʹ�! 
	const ���� ������ �̿��Ͽ� operator[]()�Լ��� �����ε� �Ѵ�! 
	��	operator[]() const �� ���, ��ȯ���� int�� �Ͽ� �ܼ��� �迭 ���� ��ȯ�ϰ� �ؾ��Ѵ�. 
		operator[]() �� ���, ��ȯ�� ������(int &)���� �Ͽ� �迭 ��ҿ� ���� ���� �ϰ� �Ѵ�. */
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
		cout << ref[idx] << endl;	// const ������ �ִ� operator[] ȣ��
}

int main(void)
{
	BoundCheckIntArray arr(5);

	for (int i = 0; i<5; i++)
		arr[i] = (i + 1) * 11;	// const ������ ���� operator[] ȣ��

	ShowAllData(arr);
	return 0;
}

#endif 

/*	��ü ����� �迭 Ŭ���� 
	1. ��ü�� �ּҰ��� �����ϴ� �迭 ����� Ŭ���� 
	2. ��ü�� �����ϴ� �迭 ����� Ŭ���� 
		1�� ��찡 ���� ���̹Ƿ�, 1�� ��츸 ������ �ϰڴ�.	
		�ּ� ���� ���� �ϵ��� �ϸ� ���� �����, ���� ������� ������ �Ű澲�� �ʾƵ� �Ǳ� ������ �� ��� ��ȣ*/
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

// << ������ ���� �ٷ� private member�� �����ֱ����� global operator<< �� ������.
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

	// operator[] const �Լ��� overloading; access function�� ������ �Լ��� ����ϵ��� �ϱ� ���� 
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
	arr[0] = new Point(3, 4);	// �ּҰ��� �����ϰԵ�
	arr[1] = new Point(5, 6);
	arr[2] = new Point(7, 8);

	for (int i = 0; i<arr.GetArrLen(); i++)
		cout << *(arr[i]);	// �ּҰ��� ���������Ƿ� *(arr[i])�� �ؾ��Ѵ�. 

	delete arr[0];
	delete arr[1];
	delete arr[2];
	return 0;
}

#endif


// 11-3 ���ķδ� ������ �ϰڴ�.
/*	new, delete, *, 
	smart *, 
	();functor
	conversion operator
	���� �ִ�.		*/