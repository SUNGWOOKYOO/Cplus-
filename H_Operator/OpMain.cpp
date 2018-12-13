// Chap 10

// 10-1
/*	������ overloading�ϴ� 2���� ���	(��� �Լ��� ���� overloading�� �켱������ ����.)
	pos1 + pos 2 
	1. ��� �Լ��� ���� op overloading
		pos1.operator+(pos2);		
	2. ���� �Լ��� ���� op overloading		
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
	Point operator+(const Point &ref)    //operator+��� �̸��� �Լ�
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
	const Point& operator+=(const Point &ref)		// ��ȯ���� reference�� �ϸ�, copy constructor�� ȣ�� ���� �ʱ� ������ �޸𸮸� ȿ�������� ��밡��
													// �� �ڼ��� ������ �ڿ� ���� 
	{
		xpos = xpos + ref.xpos;
		ypos = ypos + ref.ypos;
		return *this;								
	}

	// global function �ε� private member�� ������ ���� �ϱ� ���� friend ���� 
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
	�� member function ���θ� ������ operator
		��ü�� ������� �����ؾ� �ǹ̰� ���ϱ� ������ 
		= , (), [], ->
	�� operator�� �켱������ �״�� �����ȴ�. 
	�� �Ű������� default �� ���� �Ұ��� 
*/

// 10-2	; ���� ������ 
/*	���� ������ 	
		++pos 
		--pos		
	member �� ���	; pos.operator++()
	global �� ���	; operator++(pos)		
	��	������ ��ȯ�� �� ���, 
			���� operator ������ �����ϴ�. 
		������ ��ȯ�� ���� �ʴ°��, 
			���� operator ���� �Ұ���. �ֳĸ�, ��ȯ�� ���� ��Ų �� ��ü�� copy�Ǿ� �ӽ� ��ü�� �����ǰ�, ���� �� ��ü�� ������� �ǹǷ� 
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

	++(++pos);			// ������ ��ȯ�� ���Ұ�� ���� ����� ���� �ʴ´�.	++�ѹ��� �ȴ�.  
	pos.ShowPosition();
	--(--pos);			// ������ ��ȯ�� ���Ұ�� ���� ��� ����! 
	pos.ShowPosition();
	return 0;
}
#endif

/*	���� ������	
	pos++
	pos--
	member �� ���  ; pos.operator++(int)
	global�� ���	; operator++(pos, int)
	��	������ ��ȯ�� �ϸ� �ȵȴ�. ; copy constructor�� ����, ���� �ٿ��� �����Ǳ� ���� ���� �ӽð�ü�� const �ӽð�ü ���·� ��ȯ�Ѵ�.  
		���� �����ڴ� const ��ü�� ��ȯ�ؾ��Ѵ�. ; ����, (pos++)++ ���� ���� operator ������ �Ұ��� �ϵ��� �Ͽ���. 
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

	// member ���� ������ 
	Point& operator++()
	{
		xpos += 1;
		ypos += 1;
		return *this;
	}

	// member ���� ������ 
	const Point operator++(int)			// ��ȯ���� ������ �Ұ��� �ϴ�. 
	{
		const Point retobj(xpos, ypos);   // const Point retobj(*this);		// retobj�� ������ �� �� ����, - retobj��ü�� const �Լ��� ȣ�� �����ϴ�. 
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


// global ���� ������ 
Point& operator--(Point &ref)		
{
	ref.xpos -= 1;
	ref.ypos -= 1;
	return ref;
}

// gloal ���� ������ 
const Point operator--(Point &ref, int)		// �Ű������� �����ڿ� ���ؼ� const Point &ref �� ����ϸ� �ȵȴ�. (pos--)-- �� ���� ���Ӱ�� ���� ���ؼ�. 
											// �ֳĸ�, (Point�� const �ӽð�ü).operator++() �̹Ƿ� const�Լ��� ��밡��
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

//	10-3	; ��ȯ��Ģ ���� 
/*	���� �ٸ� �ڷ��� ���� ������ �� ��ȯ�� ������Ŀ� ������ �̷������Ѵ�. 
	pos*3 �� ������,  3*pos�� �ȵȴ�.	
	�� �����Լ� ���·� ���������ڸ� �����ε��Ͽ� 
		operator*(3, pos) �� �ǵ��� �ؾ��Ѵ�. 	*/
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

 //	10-4	; cout, cin, endl �� ��ü 
/*	Background: �Լ� ������ 
	�Լ� �����ʹ� �Լ��� ����ų �� �ִ�.
	void (*fp)(); �� �����ϸ� 

	void hello()     // ��ȯ���� �Ű������� ����
	{
    printf("Hello, world!\n");
	}

	fp = hello; �̷��� hello �Լ��� ����Ű�� �� �� �ְ�, 
	fp();           // Hello, world!: �Լ� �����ͷ� hello �Լ� ȣ��	

	�� cout�� namspace std �ȿ� ���ǵ� ostream Ŭ������ ��ü�̴�.	*/
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

/*	<<, >> �������� �����ε� 
	cout�� ostream ��ü �̹Ƿ� 
	member�Լ��� �����ε��� �� ���, cout.operator<<(pos)
	global�Լ��� �����ε��� �� ���, cout.operator<<(cout, pos)
	���°� �Ǿ���Ѵ�. 
	 ������, member�Լ��� �����ε� �� ���, namespace std �ȿ��ִ� ostream class�� �����ε� ���꿡 ���� ���Ƿ� ����ϹǷ� 
			 �� ����� ������� �ʰ�, 
			 global�Լ��� �����ε� �Ѵ�!!	*/
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

	// global function���μ� overloading �� �ϱ� ���� ostream class�� ���� �� �� �־���ϹǷ� friend ����! 
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