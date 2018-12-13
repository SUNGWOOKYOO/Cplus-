// http://luv4ever.tistory.com/113?category=493441 윤성우 C++ 문제 풀이 
// [Chap1]
/*
The following two lines set up things so that the libraries with console input and output facilities are available to the program
#include<iostream>
using namespace std

where
include, using ... are called directive 지시자
<iostream>, <cmath>, <cstdlib> ... are called library

[memory 영역]
Compiler decision
	-	CODE	:함수, 제어문
	-	DATA	:전역변수
	-	BSS		:전역변수
Running time시 크기 결정
	-	HEAP	:동적할당
	-	STACK	:지역변수
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

	// 배열기반 문자열 
	char name[100];
	cout << "what is your name? : " << endl;
	cin >> name;
	cout << "My name is " << name << endl;

	return 0;
}
#endif

// 01-2; Function overloading  
//※ 함수의 반환형이 다르면 overloading안된다.
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
//※ Default 값은 function prototype declaration 부분에만 표현하면된다. - 미리 알려줘야 컴파일이 가능하니까
//※ 반드시 오른쪽 매개변수의 디폴트 값부터 채우는 형태로 정의해야한다. - 전달되는 인자는 왼쪽부터 채워져가고, 부족 부분은 디폴트 값으로 call 되므로
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


// 01-4; Inline function  (매크로 함수의 장점을 살린 C++ 에서의 함수) 
//※ 매크로 함수는 전처리기에 의해 처리, but Inline function은 컴파일러에 의해 처리  
//※ 매크로 함수는 자료형에 의존하지 않는다는 장점, Inline함수는 templete을 사용하여 매크로 함수와 같이 동작하게 할 수 있다.
#if 0
#include <iostream>

#define SQUARE1(x) ((x)*(x))	// 자료형에 의존적이지 않은 큰 장점을 갖고 있다!

inline int SQUARE2 (int x)	// x가 int 형이 아닌경우, Data의 손실이 발생할 수 있다는 단점
{
	return x*x;
}

template <typename T>		// 위의 단점을 극복 
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

// 01-5; Name space 와 ::(scope resolution operator)
//※ 지역변수와 전역변수가 같은 이름이면 지역변수를 쓴다. 전역변수를 쓰려면 :: 를 사용하자
//※ using을 사용하여 :: 의 사용을 없앨 수 있다. 
//※ namespace ABC = AAA::BBB::CCC 를 통해 별칭 지정가능
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
	val += 3;		// 지역변수 val 
	::val += 7;		// 전역변수 val

	cout << val << '\n' << ::val << endl;

	return 0;
}
#endif

// [Chap2]

// 02-1 Review of C foundation 
#if 0
/* 1. Const 
	- ※ 변수에서 const (초기값을 지정해야한다; pointer 변수면 고정할 값지정, 그냥 변수면 값지정 ) 
		const int *a = &v;			pointer a를 이용하여 v접근은 가능하지만, v변경x, but v자체 증가가능.
		int * const a = &v;			poineter a의 상수화. a를 이용하여 v값 변경가능, but &val 값 변경 불가 and v자체 증가가능.
		const int *const a = &v;	pointer a를 이용하여 v접근은 가능하지만, v변경x, &val 변경불가, but v자체 증가가능
		const int a = 초기값;		a의 변경 불가, 접근만 가능

	- 함수에서 const ; 나중에 detail 하게 하겠다.
*/
#if 0
#include <iostream>
using namespace std;

int main(void)
{
	int val1 = 10, val2 = 20, val3 = 30;

	switch (1)	// case1~4 선택할 수 있다.
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

/* 2. 상식
	memory 공간 할당 방식 
	데이터 영역		전역변수 저장
	스택 영역		지역변수 및 매개변수 저장 
	힙 영역			동적 할당 영역 
*/

/* 3. Call by value  VS  Call by referenece 
	※ pointer ;		int * a = b;  가리킬수 있는 변수(화살표)
	※ reference ;		int & a = b;  자신이 참조하는 변수를 대신할 수 있는 또 하나의 이름(별칭)
	call by reference 의 2가지 방법 
	 - 주소값을 이용한 call by ref ; * 이용
	 - 참조자를 이용한 call by ref ; & 이용
*/
#if 1
#include <iostream>
using namespace std;

void get(int&, int&); //정수 입력받음 = void getN(int& x, int& y);
void SwapByValue(int, int);
void SwapByRef(int *, int *);

void swap(int&, int&); //call by reference parameter를 통해 argument를 variable 로 직접 참조하여 변경함, so 결과는 variable 직접 변경가능
void show(int, int);

int main()
{
	int first, second;
	get(first, second);
	SwapByValue(first,second);
	show(first, second);

	//SwapByRef(first, second);
	SwapByRef(&first, &second);		// point를 사용하여 call by reference 함수를 정의하면 argument를 '주소값' 으로 받는다.
	//swap(first, second);			// 참조형 연산자를 사용하여 call by reference 함수를 정의하면 argument를 '값' 으로 받는다.
	show(first, second);


	return 0;
}

void get(int& x, int& y)
{
	cout << "Enter 2 number continuously: ";
	cin >> x
		>> y;
	// return 0; 선택사항 
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

// 02-3; Reference 이해 
//※ reference는 선언과 동시에 누군가를 참조해야한다! 즉, 미리 참조자 선언했다가 후에 누군가를 참조하는 것은 불가능하며, 참조의 대상을 바꾸는 것도 불가능
//※ reference는 변수를 참조해야한다; 즉, 상수를 참조하는것을 불가능하며, pointer 나 배열도 참조가능
//※ 단점1: 함수의 argument(인자로서) 참조자가 사용될때, 함수 call 에 의해 변수가 변경될 수 있다. 
//		   따라서, C에서와 같도록 const 를 이용하여 함수 원형만 봐도 값의 변경이 이루어 지지 않음을 알수 있게 이를 극복한다!
//	 단점2: 함수에서 반환형을 & 로 하는 경우, 문제가 될 수 있다.  - 함수의 반환형을 참조형으로 반환할경우, 그 값을 받는 변수를 참조형으로 하면 의도치 않은 결과 발생할 수 있다.(조심해서 사용해야 한다)
//			왜냐면 함수의 인자로 들어가는 변수가 참조형식으로 반환되어 참조 되고, 그것을 참조자가 받으면, input과 output을 받는 변수가 연결됨. 
//			※ 이때, 중요한점 참조자는 변수가 아니므로 함수가 종료될때, 참조자가 참조하는 변수는 소멸되지 않는다! 
#if 1
// 1st는 기본적 이해, 2nd는 const reference 이해, 3rd 이면 함수에서의 referecne, 4th 는 기본적 이해에 대해 주의해야할 사항 
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
void func1(int);			// C style 에서는 & 변수가 없으므로 main문에서 func1(); call이 변수를 항상 바꾸지 않는다는것을 알 수 있다.
void func2(int &);			// However, C++ style 에서는 & 변수의 이용으로 func2(); call이 변수를 바꿀 수 있다. 따라서 protopyte declaration을 봐야한다. 
void func3(const int &);	// 따라서, C style 처럼 바로 main 문만 보고 함수가 변수를 바꾸지 않는 다는 것을 편하게 알 수 있게 하기 위해 const reference이용한다. 

int main(void)
{
	// 가정상황: programmer는 func함수를 통해 num을 접근만 하고, 변경은 하지않을 예정이다. 
	int num = 10; 
	func1(num);
	cout << "함수 외부에서의 값: " << num << endl;

	func2(num);	//func2의 사용으로 num이 변경될 수 있다. (C++ 에서 reference를 사용하면 유용하기도 하면서 위험한 발상)
	cout << "함수 외부에서의 값: " << num << endl;

	func3(num);	//func2의 단점을 개선시킨 func3 
	cout << "함수 외부에서의 값: " << num << endl;

	return 0;
}

void func1(int n) 
{
	n++;	// argument가 int n이므로, 함수내에서 n을 변화시키도 local variable이므로 함수 외부의 값을 변경 할 수 없다.
	cout << "함수 내부에서의 값: " << n << endl;
}

void func2(int & n)
{
	n++;	// argument가 int n이므로, 함수내에서 n을 변화시키도 local variable이므로 함수 외부의 값을 변경 할 수 없다.(유용하지만, 위험하다)
	cout << "함수 내부에서의 값: " << n << endl;
}

void func3(const int & n)
{
	//n++	// 값의 변경을 하려고 하면, 이 함수의 인자가 const int & 형이기 때문에 error가 발생한다. 
	cout << "함수 내부에서의 값: " << n << endl;
}
#elif 0		//3rd
#include <iostream>
using namespace std;

int & RefRetFuncOne(int &ref)	//함수의 반환형을 참조형으로 반환할경우, 
{
	ref++;
	return ref;
}

int main(void)
{
	int num1 = 1;
	int &num2 = RefRetFuncOne(num1);	// num1이 RefRetfuncOne을 통해 변경되고, 그 값이 반환되며 num2 값으로 참조되는데, 그 과정에서 num2의 또다른 이름이 num1이된다.

	num1+= 2;	// num2 의 또다른 이름이 num1이 되어 num1을 증가시키면 num2도 증가한다
	num2++; // num1 의 또다른 이름이 num2이 되어 num2을 증가시키면 num1도 증가한다
	cout << "num1: " << num1 << endl;
	cout << "num2: " << num2 << endl;

	// 위의 문제 해결 : num1 과 num2를 분리시킨다.   
	int num3 = RefRetFuncOne(num1);		//변형된 num1값을 참조형으로 반환하는데 그 값을 num3가 복사하여 저장한다.
	num1 += 2;	
	num3++; 
	cout << "num1: " << num1 << endl;
	cout << "num3: " << num3 << endl;

	return 0;
}
#elif 0		//4th
#include <iostream>
using namespace std;

int & RefRetFuncOne(int &ref)	//함수의 반환형을 참조형으로 반환할경우, 
{
	ref++;
	return ref;
}

int RefRetFuncTwo(int &ref)	//함수의 반환형을 int으로 반환할경우, 
{
	ref++;
	return ref;
}

int & RefRetFunc(int n)	//함수의 반환형을 & int으로 반환하는데 지역변수를 참조형으로 반환할 경우, 정작 지역변수 num은 소멸된다.  
{
	int num = 20;
	num += n;
	return num;
}

int Adder(const int &, const int &);

int main(void)
{
	// reference는 변수를 참조해야함을 기억!! 
	int num1 = 1;
	int num2 = RefRetFuncOne(num1);
	int &num3 = RefRetFuncOne(num1);	// int 자료형 num1 변수를 증가시켜 그 참조값을 반환하므로 변수를 참조하는 것이라 할 수 있다. 
	int num4 = RefRetFuncTwo(num1);
	//int &num5 = RefRetFuncTwo(num1);	// int 자료형 num1 변수를 증가시켜 그 int 값에 해당하는 숫자을 반환하므로 변수를를 참조하는 것이라 할 수 없다 ; error!. 
	//RefRetFuncOne(1);
	//RefRetFuncTwo(1);					// 마찬가지로 변수를 인수로 해야하는데 integer 값인 1을 인자로 받으면 error! 

	cout << num1 << '\n' << num2 << '\n' << num3 << '\n' << num4 << endl;

	// 지역변수를 참조형으로 반환하면, 지역변수는 소멸되게 되므로 소멸된 값을 참조하게 된다. 
	int num6 = RefRetFunc(10); 
	int &num7 = RefRetFunc(10);		// 매우 위험한 짓; 하지만 정상 출력된다..
	cout << num6 << '\n' << num7 << endl;

	// const 변수를 참조하는 법! 
	const int num = 20;
	const int &ref = num; 
	//int &ref = num;	// error!! num은 const변수이므로 
	

	// ※가능!! ; 참조자는 변수만 참조 가능한것 아니었는가???? literal constant ; 다음행으로 넘어가면 존재하지 않는 상수, 임시 존재하는 값(임시변수)
	const int &ref2 = 50; // 50은 (임시변수) 를 의미한다. 따라서 참조가능 why? 이런 것을 허용한 것일까? -> 함수에 이용하기 위해서 
	int R = Adder(20, 30);		// 함수에 직접 값을 대입하므로서 사용 할 수 있게 하였다. 
	cout << R << endl;


	return 0;
}

int Adder(const int &num1, const int &num2)
{
	return num1 + num2;
}
#endif
#endif

// 문제 02-2 ; const 변수를 가리키는 const pointer 를 참조
#if 0
#include <iostream>
using namespace std; 

int main()
{
	const int num = 12;
	const int *ptr = &num;
	const int *(&ref) = ptr;	// 포인터 변수를 참조하는 참조자

	cout << *ptr << endl;		// 포인터를 이용한 const int 변수에 접근
	cout << *ref << endl;		// (포인터를 참조하는) 참조자를 이용한 const int 변수에 접근

	return 0;
}
#endif

// 02-5
/* 동적할당 in C 
	malloc, free를 통해 Heap 영역에서 수행된다. 
	Byte 크기 단위로 정보 전달해야한다. 
	반환형이 pointer이므로 적절한 형변환을 거쳐야한다.  */
/* 동적할당 in C++
	new, delete를 통해 Heap 영역에서 수행된다.
		- [data type pointer] = new [data type]
		- delete [주소값]
	new 뒤에 자료형 type을 적으면 알아서 그에 맞게 할당된다.
	반환형이 pointer
	※ C++ 에서 malloc, free 함수의 사용이 문제를 발생 시킬 수 있다.	*/
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

#elif 0						// malloc과 new의 차이 
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
	Simple * sp1 = new Simple;								// new를 통해 Simple class 동적할당을 하면 constructor 호출O
	cout << "case 2: ";
	Simple * sp2 = (Simple*)malloc(sizeof(Simple) * 1);		// malloc를 통해 Simple class 동적할당을 하면 constructor 호출X

	cout << endl << "end of main" << endl;
	delete sp1;
	free(sp2);
	return 0;
}

#elif 0					// reference 의 선언은 변수를 대상으로 가능 = 동적 할당된 영역도 참조가 가능하다! 
#include <iostream>
using namespace std;

int main()
{
	int *ptr = new int; 
	int &ref = *ptr;	// important ! why? reference는 변수를 참조해야하므로 포인터가 가리키는 변수 *ptr을 참조해야함.
	ref = 20;
	cout << *ptr << endl;
	return 0;
}
#elif 0			// 문제 02-3
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
	cout << "[" << pref.xpos << "," << pref.ypos << "]" << endl;		// 동적 할당 된 공간을 참조하여 출력한다 메모리의 효율적 사용 [73,37] 

	Point p = PntAdder(*pptr1, *pptr2);
	cout << "[" << pref.xpos << "," << pref.ypos << "]" << endl;		// 동적할당 된 공간에 대한 PntAdder값을 다른 메모리로 복사하여 그 값을 출력으로 쓰고 있다. 

	delete pptr1;
	delete pptr2;
	delete &pref;
	return 0;
}
#endif

//	02-6
// C++ 소스 파일에서 C언어 코딩하기 
#if 0
#include <cmath>		//'math.h' 대신에 <cmath>
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

#elif 0			// 문제 02-4 문자열에 대해 다뤄보자 

#include <iostream>
#include <cstring>
using namespace std; 

int main()
{
	char *str1 = "ABC 123 ";  // 'A','B','C',' ','1','2','3','\0' : 길이 8
	char *str2 = "ABC 123 ";
	//char *str2 = "DEF 456 ";

	char str3[50];
	strcpy_s(str3, strlen(str1)+1, str1);		// strcpy 할때 '\n' 때문에 +1 해줘야 한다. 
	strcat_s(str3, str2);						// str1 + str2  문자열 합침 ; C++ 에서는 이렇게 해야한다.
	cout << str3 << endl;

	if (strcmp(str1, str2) == 0)
		cout << "문자열이 같다." << endl;
	else
		cout << "문자열이 같지 않다" << '\n'<< strlen(str1)<< '\n' << strlen(str2)<< '\n' << strlen(str3) <<endl;

	return 0;
}
#endif