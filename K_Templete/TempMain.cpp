//	Chap 13
/*	templete <typename T>
	T add(T int, int); 
	or 
	templete <class T>
	T add(T int, int);	
	
	when call,
	add<int>(15,20);
	add(15,20); �ڵ����� ���� int������ �ް�, ��ȯ
	
	��	�ѹ� �Լ��� ���������, ������� �Լ��� ȣ���Ѵ�!
		(��, �������Ҷ�, �ڷ��� �ϳ��� �ϳ����� ���������, �Ź� ���� �������� ����)	*/
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

// 2�� �̻��� type�� ���� templete
#if 0
#include <iostream>
using namespace std;

template <class T1, class T2>	
void ShowData(double num)
{
	cout << (T1)num << ", " << (T2)num << endl;		// ����ȯ T1(num) = (T1)num ���� 
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

/*	�Լ� ���ø��� Ư��ȭ 
	- �������� ����� ó��	
	templete <>
	{�Լ� ���Ǻ� }		*/
#if 0 
#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
T Max(T a, T b)
{
	return a > b ? a : b;
}

template <>	// ���ڿ��� ��� ���ܸ� �ξ� ó���Ѵ�.
char* Max(char* a, char* b)		// ���� ���� 
{
	cout << "char* Max<char*>(char* a, char* b)" << endl;
	return strlen(a) > strlen(b) ? a : b;
}

template <>
const char* Max(const char* a, const char* b)		// ���� ��� ; ���ڿ� ��ü 
{
	cout << "const char* Max<const char*>(const char* a, const char* b)" << endl;
	return strcmp(a, b) > 0 ? a : b;
}


int main(void)
{
	cout << Max(11, 15) << endl;
	cout << Max('T', 'Q') << endl;
	cout << Max(3.5, 7.5) << endl;
	cout << Max("Simple", "Best") << endl;		//	�������� ��  why? "Simple" �� const char * type

	char str1[] = "Simple";
	char str2[] = "Best";
	cout << Max(str1, str2) << endl;			// ���� ��		why? str�� char * type 
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

	��	when call,
	Point<int> pos1(3,4);
	Point<char> pos2('p','f');
	
	��	����Լ� ����� ���� �и��� template <typename T>������Ѵ�
		Ŭ���� �ۺ� ���ǿ� �Լ��� ���ǰ� �����̱� ������...		
	��	review 
		default ���� ����ο���, initializer�� ���Ǻο��� */
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

	Point<char> pos3('P', 'F');    // ��ǥ������ ���ڷ� ǥ���ϴ� ��Ȳ�� ǥ��
	pos3.ShowPosition();
	return 0;
}
#endif 

/*	���ø��� �̿��Ͽ� Ŭ������ ���� �Ǿ��� ���,
	������ ���ҿ� �־ �����ؾ� �� ���� �ִ�! 
	 -	application ��(main�� )�� ������ �Ҷ�, Ŭ������ ����� ���� 
		���(���ø� Ŭ���� �����) + implementation��(���ø� Ŭ���� ���Ǻ�)�� ���ÿ� �ʿ��ϴ�. 
		sol1. ������Ͽ� ���Ǻε� ���� �����Ѵ�.  
		sol2. application�ο� #include "[implemenation��].cpp" �����Ѵ�.*/
#if 0
// Template Header file �ȿ� �ִ� �͵� 
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

/*	�迭 Ŭ������ ���ø�ȭ 
	chap11 �� ������ �Բ�, ������ �غ��ڴ�.*/
#if 0
// BoundArrayMain.cpp
#include <iostream>
#include "ArrayTemplate.h"
#include "Point.h"
using namespace std;

int main(void)
{
	/*** int�� ���� ���� ***/
	BoundCheckArray<int> iarr(5);

	for (int i = 0; i<5; i++)
		iarr[i] = (i + 1) * 11;

	for (int i = 0; i<5; i++)
		cout << iarr[i] << endl;


	/*** Point ��ü ���� ***/
	BoundCheckArray<Point> oarr(3);
	oarr[0] = Point(3, 4);
	oarr[1] = Point(5, 6);
	oarr[2] = Point(7, 8);

	BoundCheckArray<Point> oarr2(3);

	//	oarr2= oarr;  ��ü�� �Ҵ� ������ private
	oarr[2] = oarr[1];//���:  Point ��ü�� �ɹ��� =�����̹Ƿ� ����� ����.  ���� ����Ʈ Point �Ҵ翬���� ���Ȱ��� privateȭ ��Ű�� �Ұ����������̴�.


	for (int i = 0; i<oarr.GetArrLen(); i++)
		cout << oarr[i];

	/*** Point ��ü�� �ּ� �� ���� ***/
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

/* Point<> �ڷ����� Ŭ���� ���ø��� �ڷ������� �ε��� �ϴ°��� chap 14 ���� �ϴµ� �����ϰڴ�. */