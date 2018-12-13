// http://luv4ever.tistory.com/113?category=493441 ������ C++ ���� Ǯ�� 
// [Chap1]
/*
The following two lines set up things so that the libraries with console input and output facilities are available to the program
#include<iostream>
using namespace std

where
include, using ... are called directive ������
<iostream>, <cmath>, <cstdlib> ... are called library

[memory ����]
Compiler decision
	-	CODE	:�Լ�, ���
	-	DATA	:��������
	-	BSS		:��������
Running time�� ũ�� ����
	-	HEAP	:�����Ҵ�
	-	STACK	:��������
*/

// 01-1
#if 0
# include <iostream>
using namespace std;

int main(void)
{
	// cout, endl;  
	std::cout << "Hello World! " << std::endl; 

	int num = 20;
	cout << num << ' ' << 'A' << endl; 
	
	// cin
	int val; 
	cout << "Input 2nd # : " << endl;
	std::cin >> val; 

	int result = val;
	cout << "result of output : " << result << endl;

	// for
	int val1, val2;
	int bet_sum = 0;
	cout << "Input 2 numbers sucessively, then I can show you sum between 2 numbers : " << endl;
	cin >> val1 >> val2;

	if (val1 < val2)
	{
		for (int i = val1 + 1; i < val2; i++)
			bet_sum += i; 
	}
	else
	{
		for (int i = val2 + 1; i < val1; i++)
			bet_sum += i;
	}

	cout << "sum between 2 numbers : " << bet_sum << endl;

	// �迭��� ���ڿ� 
	char name[100];
	cout << "what is your name? : " << endl;
	cin >> name;
	cout << "My name is " << name << endl;

	return 0;
}
#endif

// 01-2; Function overloading  
//�� �Լ��� ��ȯ���� �ٸ��� overloading�ȵȴ�.
#if 0
#include <iostream>

void MyFunc(void)
{
	std::cout << "MyFunc(void) called" << std::endl;
}

void MyFunc(char c)
{
	std::cout << "MyFunc(char c) called" << std::endl;
}

void MyFunc(int a, int b)
{
	std::cout << "MyFunc(int a, int b) called" << std::endl;
}

int main(void)
{
	MyFunc();
	MyFunc('A');
	MyFunc(12, 13);
	return 0;
}
#endif

// 01-3; Default value setting  
//�� Default ���� function prototype declaration �κп��� ǥ���ϸ�ȴ�. - �̸� �˷���� �������� �����ϴϱ�
//�� �ݵ�� ������ �Ű������� ����Ʈ ������ ä��� ���·� �����ؾ��Ѵ�. - ���޵Ǵ� ���ڴ� ���ʺ��� ä��������, ���� �κ��� ����Ʈ ������ call �ǹǷ�
#if 0
#include<iostream>

int BoxVolume(int length, int width = 1, int height = 1);

int main()
{
	std::cout << "[3, 3, 3] : " << BoxVolume(3, 3, 3) << std::endl;
	std::cout << "[5, 5, D] : " << BoxVolume(5, 5) << std::endl;
	std::cout << "[7, D, D] : " << BoxVolume(7) << std::endl;
	//	std::cout<<"[D, D, D] : "<<BoxVolume()<<std::endl;       // Error!   
	return 0;
}

int BoxVolume(int length, int width, int height)
{
	return length*width*height;
}

#endif


// 01-4; Inline function  (��ũ�� �Լ��� ������ �츰 C++ ������ �Լ�) 
//�� ��ũ�� �Լ��� ��ó���⿡ ���� ó��, but Inline function�� �����Ϸ��� ���� ó��  
//�� ��ũ�� �Լ��� �ڷ����� �������� �ʴ´ٴ� ����, Inline�Լ��� templete�� ����Ͽ� ��ũ�� �Լ��� ���� �����ϰ� �� �� �ִ�.
#if 0
#include <iostream>

#define SQUARE1(x) ((x)*(x))	// �ڷ����� ���������� ���� ū ������ ���� �ִ�!

inline int SQUARE2 (int x)	// x�� int ���� �ƴѰ��, Data�� �ս��� �߻��� �� �ִٴ� ����
{
	return x*x;
}

template <typename T>		// ���� ������ �غ� 
inline T SQUARE3(T x)
{
	return x*x;
}

int main(void)
{
	std::cout << SQUARE1(3.15) << std::endl;
	std::cout << SQUARE2(3.15) << std::endl;
	std::cout << SQUARE3(3.15) << std::endl;

	return 0;
}
#endif

// 01-5; Name space �� ::(scope resolution operator)
//�� ���������� ���������� ���� �̸��̸� ���������� ����. ���������� ������ :: �� �������
//�� using�� ����Ͽ� :: �� ����� ���� �� �ִ�. 
//�� namespace ABC = AAA::BBB::CCC �� ���� ��Ī ��������
#if 0
#include <iostream>
using namespace std;
int val = 100;

namespace Parent
{
	namespace children
	{
		namespace childsubone
		{
			int num1;
			int num2;
		}

		namespace childsubtwo
		{
			int num1;
			int num2;
		}
		void func(void)
		{	
			cout << "this is children's fucntion" << endl;
		}

	}
}

int main(void)
{
	Parent::children::childsubone::num1 = 20;
	Parent::children::childsubtwo::num1 = 30;

	namespace Tree1 = Parent::children::childsubone;
	namespace Tree2 = Parent::children::childsubtwo;

	cout << Tree1::num1 << endl;
	cout << Tree2::num1 << endl;
	
	using Parent::children::func; 
	func();

	int val = 20; 
	val += 3;		// �������� val 
	::val += 7;		// �������� val

	cout << val << '\n' << ::val << endl;

	return 0;
}
#endif

// [Chap2]

// 02-1 Review of C foundation 
#if 0
/* 1. Const 
	- �� �������� const (�ʱⰪ�� �����ؾ��Ѵ�; pointer ������ ������ ������, �׳� ������ ������ ) 
		const int *a = &v;			pointer a�� �̿��Ͽ� v������ ����������, v����x, but v��ü ��������.
		int * const a = &v;			poineter a�� ���ȭ. a�� �̿��Ͽ� v�� ���氡��, but &val �� ���� �Ұ� and v��ü ��������.
		const int *const a = &v;	pointer a�� �̿��Ͽ� v������ ����������, v����x, &val ����Ұ�, but v��ü ��������
		const int a = �ʱⰪ;		a�� ���� �Ұ�, ���ٸ� ����

	- �Լ����� const ; ���߿� detail �ϰ� �ϰڴ�.
*/
#if 0
#include <iostream>
using namespace std;

int main(void)
{
	int val1 = 10, val2 = 20, val3 = 30;

	switch (1)	// case1~4 ������ �� �ִ�.
	{
	case 1:
	{
		const int * ptr1 = &val1;
		//* ptr1 += 1;
		cout << *ptr1 << '\n' << ptr1 << endl;

		val1++;	
		cout << val1 << endl;
		break;
	}
	case 2:
	{
		int * const ptr2 = &val2;
		//ptr2 = &val1;

		*ptr2 += 1;
		cout << val2 << endl;
		
		val2++;
		cout << val2 << endl;
		break;
	}
	case 3:
	{
		const int * const ptr3 = &val3;
		//ptr3 = &val3;
		//*ptr3 += 1;

		val3++;
		cout << val3 << endl;
		break;
	}
	case 4:
	{
		const int num = 5;
		//num = 11;  //error! 
		//num++; 
		cout << num << endl;
		break;
	}
	}

	return 0;
}
#endif

/* 2. ���
	memory ���� �Ҵ� ��� 
	������ ����		�������� ����
	���� ����		�������� �� �Ű����� ���� 
	�� ����			���� �Ҵ� ���� 
*/

/* 3. Call by value  VS  Call by referenece 
	�� pointer ;		int * a = b;  ����ų�� �ִ� ����(ȭ��ǥ)
	�� reference ;		int & a = b;  �ڽ��� �����ϴ� ������ ����� �� �ִ� �� �ϳ��� �̸�(��Ī)
	call by reference �� 2���� ��� 
	 - �ּҰ��� �̿��� call by ref ; * �̿�
	 - �����ڸ� �̿��� call by ref ; & �̿�
*/
#if 1
#include <iostream>
using namespace std;

void get(int&, int&); //���� �Է¹��� = void getN(int& x, int& y);
void SwapByValue(int, int);
void SwapByRef(int *, int *);

void swap(int&, int&); //call by reference parameter�� ���� argument�� variable �� ���� �����Ͽ� ������, so ����� variable ���� ���氡��
void show(int, int);

int main()
{
	int first, second;
	get(first, second);
	SwapByValue(first,second);
	show(first, second);

	//SwapByRef(first, second);
	SwapByRef(&first, &second);		// point�� ����Ͽ� call by reference �Լ��� �����ϸ� argument�� '�ּҰ�' ���� �޴´�.
	//swap(first, second);			// ������ �����ڸ� ����Ͽ� call by reference �Լ��� �����ϸ� argument�� '��' ���� �޴´�.
	show(first, second);


	return 0;
}

void get(int& x, int& y)
{
	cout << "Enter 2 number continuously: ";
	cin >> x
		>> y;
	// return 0; ���û��� 
}

void SwapByValue(int num1, int num2)
{
	// Call by value
	int temp = num1;
	num1 = num2;
	num2 = temp;
}

void SwapByRef(int *ptr1, int *ptr2)
{
	// Call by reference
	int temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

void swap(int& x, int& y)
{
	int temp;
	temp = y;
	y = x;
	x = temp;
}

void show(int x, int y)
{
	cout << "swapped variable \n" << "first: " << x << endl
		<< "second: " << y << endl;
}

#endif 


#endif

// 02-3; Reference ���� 
//�� reference�� ����� ���ÿ� �������� �����ؾ��Ѵ�! ��, �̸� ������ �����ߴٰ� �Ŀ� �������� �����ϴ� ���� �Ұ����ϸ�, ������ ����� �ٲٴ� �͵� �Ұ���
//�� reference�� ������ �����ؾ��Ѵ�; ��, ����� �����ϴ°��� �Ұ����ϸ�, pointer �� �迭�� ��������
//�� ����1: �Լ��� argument(���ڷμ�) �����ڰ� ���ɶ�, �Լ� call �� ���� ������ ����� �� �ִ�. 
//		   ����, C������ ������ const �� �̿��Ͽ� �Լ� ������ ���� ���� ������ �̷�� ���� ������ �˼� �ְ� �̸� �غ��Ѵ�!
//	 ����2: �Լ����� ��ȯ���� & �� �ϴ� ���, ������ �� �� �ִ�.  - �Լ��� ��ȯ���� ���������� ��ȯ�Ұ��, �� ���� �޴� ������ ���������� �ϸ� �ǵ�ġ ���� ��� �߻��� �� �ִ�.(�����ؼ� ����ؾ� �Ѵ�)
//			�ֳĸ� �Լ��� ���ڷ� ���� ������ ������������ ��ȯ�Ǿ� ���� �ǰ�, �װ��� �����ڰ� ������, input�� output�� �޴� ������ �����. 
//			�� �̶�, �߿����� �����ڴ� ������ �ƴϹǷ� �Լ��� ����ɶ�, �����ڰ� �����ϴ� ������ �Ҹ���� �ʴ´�! 
#if 1
// 1st�� �⺻�� ����, 2nd�� const reference ����, 3rd �̸� �Լ������� referecne, 4th �� �⺻�� ���ؿ� ���� �����ؾ��� ���� 
#if 0		//1st
#include <iostream>
using namespace std;

int main(void)
{
	int num = 12;
	int *ptr = &num;
	int **dptr = &ptr;

	int &ref = num;
	int *(&pref) = ptr;
	int **(&dpref) = dptr;

	cout << ref << endl;
	cout << *pref << endl;
	cout << **dpref << endl;
	return 0;
}
#elif 0		//2nd
#include <iostream>
using namespace std;
void func1(int);			// C style ������ & ������ �����Ƿ� main������ func1(); call�� ������ �׻� �ٲ��� �ʴ´ٴ°��� �� �� �ִ�.
void func2(int &);			// However, C++ style ������ & ������ �̿����� func2(); call�� ������ �ٲ� �� �ִ�. ���� protopyte declaration�� �����Ѵ�. 
void func3(const int &);	// ����, C style ó�� �ٷ� main ���� ���� �Լ��� ������ �ٲ��� �ʴ� �ٴ� ���� ���ϰ� �� �� �ְ� �ϱ� ���� const reference�̿��Ѵ�. 

int main(void)
{
	// ������Ȳ: programmer�� func�Լ��� ���� num�� ���ٸ� �ϰ�, ������ �������� �����̴�. 
	int num = 10; 
	func1(num);
	cout << "�Լ� �ܺο����� ��: " << num << endl;

	func2(num);	//func2�� ������� num�� ����� �� �ִ�. (C++ ���� reference�� ����ϸ� �����ϱ⵵ �ϸ鼭 ������ �߻�)
	cout << "�Լ� �ܺο����� ��: " << num << endl;

	func3(num);	//func2�� ������ ������Ų func3 
	cout << "�Լ� �ܺο����� ��: " << num << endl;

	return 0;
}

void func1(int n) 
{
	n++;	// argument�� int n�̹Ƿ�, �Լ������� n�� ��ȭ��Ű�� local variable�̹Ƿ� �Լ� �ܺ��� ���� ���� �� �� ����.
	cout << "�Լ� ���ο����� ��: " << n << endl;
}

void func2(int & n)
{
	n++;	// argument�� int n�̹Ƿ�, �Լ������� n�� ��ȭ��Ű�� local variable�̹Ƿ� �Լ� �ܺ��� ���� ���� �� �� ����.(����������, �����ϴ�)
	cout << "�Լ� ���ο����� ��: " << n << endl;
}

void func3(const int & n)
{
	//n++	// ���� ������ �Ϸ��� �ϸ�, �� �Լ��� ���ڰ� const int & ���̱� ������ error�� �߻��Ѵ�. 
	cout << "�Լ� ���ο����� ��: " << n << endl;
}
#elif 0		//3rd
#include <iostream>
using namespace std;

int & RefRetFuncOne(int &ref)	//�Լ��� ��ȯ���� ���������� ��ȯ�Ұ��, 
{
	ref++;
	return ref;
}

int main(void)
{
	int num1 = 1;
	int &num2 = RefRetFuncOne(num1);	// num1�� RefRetfuncOne�� ���� ����ǰ�, �� ���� ��ȯ�Ǹ� num2 ������ �����Ǵµ�, �� �������� num2�� �Ǵٸ� �̸��� num1�̵ȴ�.

	num1+= 2;	// num2 �� �Ǵٸ� �̸��� num1�� �Ǿ� num1�� ������Ű�� num2�� �����Ѵ�
	num2++; // num1 �� �Ǵٸ� �̸��� num2�� �Ǿ� num2�� ������Ű�� num1�� �����Ѵ�
	cout << "num1: " << num1 << endl;
	cout << "num2: " << num2 << endl;

	// ���� ���� �ذ� : num1 �� num2�� �и���Ų��.   
	int num3 = RefRetFuncOne(num1);		//������ num1���� ���������� ��ȯ�ϴµ� �� ���� num3�� �����Ͽ� �����Ѵ�.
	num1 += 2;	
	num3++; 
	cout << "num1: " << num1 << endl;
	cout << "num3: " << num3 << endl;

	return 0;
}
#elif 0		//4th
#include <iostream>
using namespace std;

int & RefRetFuncOne(int &ref)	//�Լ��� ��ȯ���� ���������� ��ȯ�Ұ��, 
{
	ref++;
	return ref;
}

int RefRetFuncTwo(int &ref)	//�Լ��� ��ȯ���� int���� ��ȯ�Ұ��, 
{
	ref++;
	return ref;
}

int & RefRetFunc(int n)	//�Լ��� ��ȯ���� & int���� ��ȯ�ϴµ� ���������� ���������� ��ȯ�� ���, ���� �������� num�� �Ҹ�ȴ�.  
{
	int num = 20;
	num += n;
	return num;
}

int Adder(const int &, const int &);

int main(void)
{
	// reference�� ������ �����ؾ����� ���!! 
	int num1 = 1;
	int num2 = RefRetFuncOne(num1);
	int &num3 = RefRetFuncOne(num1);	// int �ڷ��� num1 ������ �������� �� �������� ��ȯ�ϹǷ� ������ �����ϴ� ���̶� �� �� �ִ�. 
	int num4 = RefRetFuncTwo(num1);
	//int &num5 = RefRetFuncTwo(num1);	// int �ڷ��� num1 ������ �������� �� int ���� �ش��ϴ� ������ ��ȯ�ϹǷ� �������� �����ϴ� ���̶� �� �� ���� ; error!. 
	//RefRetFuncOne(1);
	//RefRetFuncTwo(1);					// ���������� ������ �μ��� �ؾ��ϴµ� integer ���� 1�� ���ڷ� ������ error! 

	cout << num1 << '\n' << num2 << '\n' << num3 << '\n' << num4 << endl;

	// ���������� ���������� ��ȯ�ϸ�, ���������� �Ҹ�ǰ� �ǹǷ� �Ҹ�� ���� �����ϰ� �ȴ�. 
	int num6 = RefRetFunc(10); 
	int &num7 = RefRetFunc(10);		// �ſ� ������ ��; ������ ���� ��µȴ�..
	cout << num6 << '\n' << num7 << endl;

	// const ������ �����ϴ� ��! 
	const int num = 20;
	const int &ref = num; 
	//int &ref = num;	// error!! num�� const�����̹Ƿ� 
	

	// �ذ���!! ; �����ڴ� ������ ���� �����Ѱ� �ƴϾ��°�???? literal constant ; ���������� �Ѿ�� �������� �ʴ� ���, �ӽ� �����ϴ� ��(�ӽú���)
	const int &ref2 = 50; // 50�� (�ӽú���) �� �ǹ��Ѵ�. ���� �������� why? �̷� ���� ����� ���ϱ�? -> �Լ��� �̿��ϱ� ���ؼ� 
	int R = Adder(20, 30);		// �Լ��� ���� ���� �����ϹǷμ� ��� �� �� �ְ� �Ͽ���. 
	cout << R << endl;


	return 0;
}

int Adder(const int &num1, const int &num2)
{
	return num1 + num2;
}
#endif
#endif

// ���� 02-2 ; const ������ ����Ű�� const pointer �� ����
#if 0
#include <iostream>
using namespace std; 

int main()
{
	const int num = 12;
	const int *ptr = &num;
	const int *(&ref) = ptr;	// ������ ������ �����ϴ� ������

	cout << *ptr << endl;		// �����͸� �̿��� const int ������ ����
	cout << *ref << endl;		// (�����͸� �����ϴ�) �����ڸ� �̿��� const int ������ ����

	return 0;
}
#endif

// 02-5
/* �����Ҵ� in C 
	malloc, free�� ���� Heap �������� ����ȴ�. 
	Byte ũ�� ������ ���� �����ؾ��Ѵ�. 
	��ȯ���� pointer�̹Ƿ� ������ ����ȯ�� ���ľ��Ѵ�.  */
/* �����Ҵ� in C++
	new, delete�� ���� Heap �������� ����ȴ�.
		- [data type pointer] = new [data type]
		- delete [�ּҰ�]
	new �ڿ� �ڷ��� type�� ������ �˾Ƽ� �׿� �°� �Ҵ�ȴ�.
	��ȯ���� pointer
	�� C++ ���� malloc, free �Լ��� ����� ������ �߻� ��ų �� �ִ�.	*/
#if 0
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

char * MakeStrAdr(int len)
{
	char * str=(char*)malloc(sizeof(char)*len);
	return str;
}

int main(void)
{
	char * str=MakeStrAdr(20);
	strcpy_s(str, strlen(str)+1, "I am so happy~");
	cout<<str<<endl;
	free(str);
	return 0;
}
#elif 0
#include <iostream>
#include <string.h>
using namespace std;

char * MakeStrAdr(int len)
{
	// char * str=(char*)malloc(sizeof(char)*len);
	char * str = new char[len];
	return str;
}

int main(void)
{
	char * str = MakeStrAdr(20);
	strcpy_s(str, strlen(str)+ 1, "I am so happy~");
	cout << str << endl;
	// free(str);
	delete []str;
	return 0;
}

#elif 0						// malloc�� new�� ���� 
#include <iostream>
#include <stdlib.h>
using namespace std;

class Simple
{
public:
	Simple()
	{
		cout << "I'm simple constructor!" << endl;
	}
};

int main(void)
{
	cout << "case 1: ";
	Simple * sp1 = new Simple;								// new�� ���� Simple class �����Ҵ��� �ϸ� constructor ȣ��O
	cout << "case 2: ";
	Simple * sp2 = (Simple*)malloc(sizeof(Simple) * 1);		// malloc�� ���� Simple class �����Ҵ��� �ϸ� constructor ȣ��X

	cout << endl << "end of main" << endl;
	delete sp1;
	free(sp2);
	return 0;
}

#elif 0					// reference �� ������ ������ ������� ���� = ���� �Ҵ�� ������ ������ �����ϴ�! 
#include <iostream>
using namespace std;

int main()
{
	int *ptr = new int; 
	int &ref = *ptr;	// important ! why? reference�� ������ �����ؾ��ϹǷ� �����Ͱ� ����Ű�� ���� *ptr�� �����ؾ���.
	ref = 20;
	cout << *ptr << endl;
	return 0;
}
#elif 0			// ���� 02-3
#include <iostream>
using namespace std;

typedef struct __Point
{
	int xpos;
	int ypos;
} Point;

Point& PntAdder(const Point &p1, const Point &p2)
{
	Point * pptr = new Point;
	pptr->xpos = p1.xpos + p2.xpos;
	pptr->ypos = p1.ypos + p2.ypos;
	return *pptr;
}

int main()
{	
	Point *pptr1 = new Point; 
	pptr1->xpos = 3;
	pptr1->ypos = 30;

	Point *pptr2 = new Point;
	pptr2->xpos = 70;
	pptr2->ypos = 7;

	Point &pref = PntAdder(*pptr1, *pptr2);
	cout << "[" << pref.xpos << "," << pref.ypos << "]" << endl;		// ���� �Ҵ� �� ������ �����Ͽ� ����Ѵ� �޸��� ȿ���� ��� [73,37] 

	Point p = PntAdder(*pptr1, *pptr2);
	cout << "[" << pref.xpos << "," << pref.ypos << "]" << endl;		// �����Ҵ� �� ������ ���� PntAdder���� �ٸ� �޸𸮷� �����Ͽ� �� ���� ������� ���� �ִ�. 

	delete pptr1;
	delete pptr2;
	delete &pref;
	return 0;
}
#endif

//	02-6
// C++ �ҽ� ���Ͽ��� C��� �ڵ��ϱ� 
#if 0
#include <cmath>		//'math.h' ��ſ� <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

int main(void)
{
	char str1[] = "Result";
	char str2[30];

	strcpy_s(str2,strlen(str1)+1, str1);
	printf("%s: %f \n", str1, sin(0.14));
	printf("%s: %f \n", str2, abs(-1.25));
	return 0;
}

#elif 0			// ���� 02-4 ���ڿ��� ���� �ٷﺸ�� 

#include <iostream>
#include <cstring>
using namespace std; 

int main()
{
	char *str1 = "ABC 123 ";  // 'A','B','C',' ','1','2','3','\0' : ���� 8
	char *str2 = "ABC 123 ";
	//char *str2 = "DEF 456 ";

	char str3[50];
	strcpy_s(str3, strlen(str1)+1, str1);		// strcpy �Ҷ� '\n' ������ +1 ����� �Ѵ�. 
	strcat_s(str3, str2);						// str1 + str2  ���ڿ� ��ħ ; C++ ������ �̷��� �ؾ��Ѵ�.
	cout << str3 << endl;

	if (strcmp(str1, str2) == 0)
		cout << "���ڿ��� ����." << endl;
	else
		cout << "���ڿ��� ���� �ʴ�" << '\n'<< strlen(str1)<< '\n' << strlen(str2)<< '\n' << strlen(str3) <<endl;

	return 0;
}
#endif