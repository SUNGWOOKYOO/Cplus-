// Chap 10

// 10-1
/*	연산자 overloading하는 2가지 방법	(멤버 함수에 희한 overloading이 우선순위가 높다.)
	pos1 + pos 2 
	1. 멤버 함수에 의한 op overloading
		pos1.operator+(pos2);		
	2. 전역 함수에 의한 op overloading		
		operator+(pos1, pos2)			*/
#if 0
// member function 
#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y)
	{  }
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}
	Point operator+(const Point &ref)    //operator+라는 이름의 함수
	{
		Point pos(xpos + ref.xpos, ypos + ref.ypos);
		return pos;
	}
};

int main(void)
{
	Point pos1(3, 4);
	Point pos2(10, 20);
	//Point pos3 = pos1.operator+(pos2);
	Point pos3 = pos1 + pos2;

	pos1.ShowPosition();
	pos2.ShowPosition();
	pos3.ShowPosition();
	return 0;
}
#elif 0
// global function
#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y)
	{  }
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}

	// member function
	const Point& operator+=(const Point &ref)		// 반환형을 reference로 하면, copy constructor를 호출 하지 않기 때문에 메모리를 효율적으로 사용가능
													// 더 자세한 내용은 뒤에 설명 
	{
		xpos = xpos + ref.xpos;
		ypos = ypos + ref.ypos;
		return *this;								
	}

	// global function 인데 private member에 접근을 쉽게 하기 위해 friend 선언 
	friend Point operator+(const Point &pos1, const Point &pos2);
	friend Point operator-(const Point &pos1, const Point &pos2);
};

Point operator+(const Point &pos1, const Point &pos2)
{
	Point pos(pos1.xpos + pos2.xpos, pos1.ypos + pos2.ypos);
	return pos;
}

Point operator-(const Point &pos1, const Point &pos2)
{
	Point pos(pos1.xpos - pos2.xpos, pos1.ypos - pos2.ypos);
	return pos;

}

int main(void)
{
	Point pos1(3, 4);
	Point pos2(10, 20);
	Point pos3 = pos1 + pos2;
	Point pos4 = pos2 - pos1;

	pos1.ShowPosition();
	pos2.ShowPosition();
	pos3.ShowPosition();
	pos4.ShowPosition();
	return 0;
}

#endif

/*
	※ member function 으로만 가능한 operator
		객체를 대상으로 진행해야 의미가 통하기 때문에 
		= , (), [], ->
	※ operator의 우선순위는 그대로 보존된다. 
	※ 매개변수의 default 값 설정 불가능 
*/

// 10-2	; 단항 연산자 
/*	전위 연산자 	
		++pos 
		--pos		
	member 의 경우	; pos.operator++()
	global 의 경우	; operator++(pos)		
	※	참조형 반환을 할 경우, 
			연속 operator 연산이 가능하다. 
		참조형 반환을 하지 않는경우, 
			연속 operator 연산 불가능. 왜냐면, 반환시 증가 시킨 값 객체는 copy되어 임시 객체가 생성되고, 증가 된 객체는 사라지게 되므로 
		*/
#if 0
#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y)
	{  }
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}
	Point operator++()
	{
		xpos += 1;
		ypos += 1;
		return *this;
	}
	friend Point& operator--(Point &ref);
};

Point& operator--(Point &ref)
{
	ref.xpos -= 1;
	ref.ypos -= 1;
	return ref;
}

int main(void)
{
	Point pos(1, 2);
	++pos;
	pos.ShowPosition();
	--pos;
	pos.ShowPosition();

	++(++pos);			// 참조형 반환을 안할경우 연속 계산이 되지 않는다.	++한번만 된다.  
	pos.ShowPosition();
	--(--pos);			// 참조형 반환을 안할경우 연속 계산 가능! 
	pos.ShowPosition();
	return 0;
}
#endif

/*	후위 연산자	
	pos++
	pos--
	member 의 경우  ; pos.operator++(int)
	global의 경우	; operator++(pos, int)
	※	참조형 반환을 하면 안된다. ; copy constructor를 통해, 현재 줄에서 증가되기 전의 값의 임시객체를 const 임시객체 형태로 반환한다.  
		후위 연산자는 const 객체를 반환해야한다. ; 따라서, (pos++)++ 같은 연속 operator 연산이 불가능 하도록 하였다. 
	*/
#if 0
#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y)
	{  }
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}

	// member 전위 연산자 
	Point& operator++()
	{
		xpos += 1;
		ypos += 1;
		return *this;
	}

	// member 후위 연산자 
	const Point operator++(int)			// 반환형의 변경은 불가능 하다. 
	{
		const Point retobj(xpos, ypos);   // const Point retobj(*this);		// retobj는 변경을 할 수 없다, - retobj객체는 const 함수만 호출 가능하다. 
		xpos += 1;
		ypos += 1;
		return retobj;
	}

	friend Point operator+(const Point &pos1, const Point &pos2);
	friend Point& operator--(Point &ref);
	friend const Point operator--(Point &ref, int);
};

Point operator+(const Point &pos1, const Point &pos2)
{
	return Point(pos1.xpos + pos2.xpos, pos1.ypos + pos2.ypos);
}


// global 전위 연산자 
Point& operator--(Point &ref)		
{
	ref.xpos -= 1;
	ref.ypos -= 1;
	return ref;
}

// gloal 후위 연산자 
const Point operator--(Point &ref, int)		// 매개변수의 참조자에 대해서 const Point &ref 로 사용하면 안된다. (pos--)-- 와 같은 연속계산 막기 위해서. 
											// 왜냐면, (Point형 const 임시객체).operator++() 이므로 const함수만 사용가능
{
	const Point retobj(ref);
	ref.xpos -= 1;
	ref.ypos -= 1;
	return retobj;
}

int main(void)
{
	Point pos(3, 5);
	Point cpy;
	cpy = pos--;
	cpy.ShowPosition();
	pos.ShowPosition();

	cpy = pos++;
	cpy.ShowPosition();
	pos.ShowPosition();

	Point pos1(1, 0), pos2(0, 1), pos3(1, 1);
	Point rp = pos1 + pos2;
	rp.ShowPosition();
	Point rpp = pos1 + pos2 + pos3;
	rpp.ShowPosition();
	return 0;
}
#endif 

//	10-3	; 교환법칙 문제 
/*	서로 다른 자료형 간의 연산은 형 변환이 진행된후에 연산이 이뤄져야한다. 
	pos*3 은 되지만,  3*pos는 안된다.	
	※ 전역함수 형태로 곱셉연산자를 오버로딩하여 
		operator*(3, pos) 가 되도록 해야한다. 	*/
#if 0
#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y)
	{  }
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}
	Point operator*(int times)
	{
		Point pos(xpos*times, ypos*times);
		return pos;
	}
	friend Point operator*(int times, Point & ref);
};

Point operator*(int times, Point & ref)
{
	return ref*times;
}

int main(void)
{
	Point pos(1, 2);
	Point cpy;

	cpy = 3 * pos;
	cpy.ShowPosition();

	cpy = 2 * pos * 3;
	cpy.ShowPosition();
	return 0;
}
#endif

 //	10-4	; cout, cin, endl 의 정체 
/*	Background: 함수 포인터 
	함수 포인터는 함수를 가리킬 수 있다.
	void (*fp)(); 를 선언하면 

	void hello()     // 반환값과 매개변수가 없음
	{
    printf("Hello, world!\n");
	}

	fp = hello; 이렇게 hello 함수를 가리키게 할 수 있고, 
	fp();           // Hello, world!: 함수 포인터로 hello 함수 호출	

	※ cout은 namspace std 안에 정의된 ostream 클래스의 객체이다.	*/
#if 0
// IterateConsoleOutput.cpp
#include <iostream>	

namespace mystd
{
	using namespace std;

	class ostream
	{
	public:
		ostream& operator<< (char * str)
		{
			printf("%s", str);
			return *this;
		}
		ostream& operator<< (char str)
		{
			printf("%c", str);
			return *this;
		}
		ostream& operator<< (int num)
		{
			printf("%d", num);
			return *this;
		}
		ostream& operator<< (double e)
		{
			printf("%g", e);
			return *this;
		}
		ostream& operator<< (ostream& (*fp)(ostream &ostm))
		{
			return fp(*this);
		}
	};

	ostream& endl(ostream &ostm)
	{
		ostm << '\n';
		fflush(stdout);
		return ostm;
	}
	ostream cout;
}

int main(void)
{
	using mystd::cout;
	using mystd::endl;
	cout << 3.14 << endl << 123 << endl;
	return 0;
}
#endif 

/*	<<, >> 연산자의 오버로딩 
	cout은 ostream 객체 이므로 
	member함수로 오버로딩을 할 경우, cout.operator<<(pos)
	global함수로 오버로딩을 할 경우, cout.operator<<(cout, pos)
	형태가 되어야한다. 
	 하지만, member함수로 오버로딩 할 경우, namespace std 안에있는 ostream class에 오버로딩 연산에 대한 정의롤 써야하므로 
			 이 방법을 사용하지 않고, 
			 global함수로 오버로딩 한다!!	*/
#if 0 
#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y)
	{  }
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}

	// global function으로서 overloading 을 하기 위해 ostream class에 접근 할 수 있어야하므로 friend 선언! 
	friend ostream& operator<<(ostream&, const Point&);
	friend istream& operator>>(istream&, const Point&);

};


ostream& operator<<(ostream& os, const Point& pos)
{
	os << '[' << pos.xpos << ", " << pos.ypos << ']' << endl;
	return os;
}

istream& operator>>(istream& is, const Point& pos)
{
	is >> pos.xpos >> pos.ypos;
	return is;
}


int main(void)
{
	Point pos1(1, 3);
	cout << pos1;
	Point pos2(101, 303);
	cout << pos2;
	return 0;
}

#endif 