//	Chap 13
/*	templete <typename T>
	T add(T int, int); 
	or 
	templete <class T>
	T add(T int, int);	
	
	when call,
	add<int>(15,20);
	add(15,20); 자동으로 형을 int형으로 받고, 반환
	
	※	한번 함수가 만들어지면, 만들어진 함수를 호출한다!
		(즉, 컴파일할때, 자료형 하나당 하나씩만 만들어지고, 매번 새로 만들지는 않음)	*/
#if 0
#include <iostream>
using namespace std;

template <typename T>
T Add(T num1, T num2)
{
	cout << "T Add(T num1, T num2)" << endl;
	return num1 + num2;
}

int Add(int num1, int num2)
{
	cout << "Add(int num1, int num2)" << endl;
	return num1 + num2;
}

double Add(double num1, double num2)
{
	cout << "Add(double num1, double num2)" << endl;
	return num1 + num2;
}

int main(void)
{
	cout << Add(5, 7) << endl;
	cout << Add(3.7, 7.5) << endl;
	cout << Add<int>(5, 7) << endl;
	cout << Add<double>(3.7, 7.5) << endl;
	return 0;
}

#endif 

// 2개 이상의 type에 대한 templete
#if 0
#include <iostream>
using namespace std;

template <class T1, class T2>	
void ShowData(double num)
{
	cout << (T1)num << ", " << (T2)num << endl;		// 형변환 T1(num) = (T1)num 가능 
}

int main(void)
{
	ShowData<char, int>(65);
	ShowData<char, int>(67);
	ShowData<char, double>(68.9);
	ShowData<short, double>(69.2);
	ShowData<short, double>(70.4);
	return 0;
}

#endif

/*	함수 템플릿의 특수화 
	- 예외적인 경우의 처리	
	templete <>
	{함수 정의부 }		*/
#if 0 
#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
T Max(T a, T b)
{
	return a > b ? a : b;
}

template <>	// 문자열의 경우 예외를 두어 처리한다.
char* Max(char* a, char* b)		// 변수 문자 
{
	cout << "char* Max<char*>(char* a, char* b)" << endl;
	return strlen(a) > strlen(b) ? a : b;
}

template <>
const char* Max(const char* a, const char* b)		// 문자 상수 ; 문자열 자체 
{
	cout << "const char* Max<const char*>(const char* a, const char* b)" << endl;
	return strcmp(a, b) > 0 ? a : b;
}


int main(void)
{
	cout << Max(11, 15) << endl;
	cout << Max('T', 'Q') << endl;
	cout << Max(3.5, 7.5) << endl;
	cout << Max("Simple", "Best") << endl;		//	사전순서 비교  why? "Simple" 은 const char * type

	char str1[] = "Simple";
	char str2[] = "Best";
	cout << Max(str1, str2) << endl;			// 길이 비교		why? str은 char * type 
	return 0;
}

#endif 

// 13-2 ; Class Templete
/*	template <typename T>
	class Point
	{
	private:
		T xpos, ypos; 
	public: 
		Point(T x=0, T y=0) : xpos(x), ypos(y)
		{}
	};								

	※	when call,
	Point<int> pos1(3,4);
	Point<char> pos2('p','f');
	
	※	멤버함수 선언과 정의 분리시 template <typename T>적어야한다
		클래스 템블릿 정의와 함수의 정의가 별개이기 때문에...		
	※	review 
		default 값은 선언부에만, initializer는 정의부에만 */
#if 0
#include <iostream>
using namespace std;

template <typename T>
class Point
{
private:
	T xpos, ypos;
public:
	Point(T x = 0, T y = 0);
	void ShowPosition() const;
};

template <typename T>
Point<T>::Point(T x, T y) : xpos(x), ypos(y)
{  }

template <typename T>
void Point<T>::ShowPosition() const
{
	cout << '[' << xpos << ", " << ypos << ']' << endl;
}


int main(void)
{
	Point<int> pos1(3, 4);
	pos1.ShowPosition();

	Point<double> pos2(2.4, 3.6);
	pos2.ShowPosition();

	Point<char> pos3('P', 'F');    // 좌표정보를 문자로 표시하는 상황의 표현
	pos3.ShowPosition();
	return 0;
}
#endif 

/*	템플릿을 이용하여 클래스가 정의 되었을 경우,
	파일의 분할에 있어서 주의해야 할 점이 있다! 
	 -	application 부(main부 )를 컴파일 할때, 클래스를 만들기 위해 
		헤더(템플릿 클래스 선언부) + implementation부(템플릿 클래스 정의부)가 동시에 필요하다. 
		sol1. 헤더파일에 정의부도 같이 포함한다.  
		sol2. application부에 #include "[implemenation부].cpp" 포함한다.*/
#if 0
// Template Header file 안에 있는 것들 
#include <iostream>
#include "PointTemplate.h"
#include "PointTemplate.cpp"
using namespace std;

int main(void)
{
	Point<int> pos1(3, 4);
	pos1.ShowPosition();

	Point<double> pos2(2.4, 3.6);
	pos2.ShowPosition();

	Point<char> pos3('P', 'F');
	pos3.ShowPosition();
	return 0;
}
#endif 

/*	배열 클래스의 템플릿화 
	chap11 의 복습과 함께, 응용을 해보겠다.*/
#if 0
// BoundArrayMain.cpp
#include <iostream>
#include "ArrayTemplate.h"
#include "Point.h"
using namespace std;

int main(void)
{
	/*** int형 정수 저장 ***/
	BoundCheckArray<int> iarr(5);

	for (int i = 0; i<5; i++)
		iarr[i] = (i + 1) * 11;

	for (int i = 0; i<5; i++)
		cout << iarr[i] << endl;


	/*** Point 객체 저장 ***/
	BoundCheckArray<Point> oarr(3);
	oarr[0] = Point(3, 4);
	oarr[1] = Point(5, 6);
	oarr[2] = Point(7, 8);

	BoundCheckArray<Point> oarr2(3);

	//	oarr2= oarr;  객체간 할당 연산자 private
	oarr[2] = oarr[1];//기능:  Point 객체의 맴버간 =연산이므로 상관이 없다.  지금 디폴트 Point 할당연산자 사용된것임 private화 시키면 불가능했을것이다.


	for (int i = 0; i<oarr.GetArrLen(); i++)
		cout << oarr[i];

	/*** Point 객체의 주소 값 저장 ***/
	typedef Point * POINT_PTR;
	BoundCheckArray<POINT_PTR> parr(3);
	parr[0] = new Point(3, 4);
	parr[1] = new Point(5, 6);
	parr[2] = new Point(7, 8);



	for (int i = 0; i<parr.GetArrLen(); i++)
		cout << *(parr[i]);

	delete parr[0];
	delete parr[1];
	delete parr[2];



	return 0;
}

#endif 

/* Point<> 자료형을 클래스 템플릿의 자료형으로 두도록 하는것은 chap 14 에서 하는데 생략하겠다. */