// 06-1
/*	Const	; ConstObject.c, ConstOverloading.c
	const object�� const �ɹ� �Լ��� ȣ�� ���� 
	const �Լ� overloading ����
	�� Const �ɹ� ����(= const  �ɹ� ���)�� �����ڴ� ����� ���ÿ� �ʱ�ȭ �ؾ��ϴµ� Member Initializer�� �̿��ϸ� �ʱ�ȭ�� �����ϴ� . */
#if 0
#include <iostream>
using namespace std;

class SoSimple
{
private:
	int num;
public:
	SoSimple(int n) : num(n)
	{ }
	SoSimple& AddNum(int n)
	{
		num += n;
		return *this;
	}
	void ShowData() const
	{
		cout << "num: " << num << endl;
	}

	// overloading
	void SimpleFunc()
	{
		cout << "SimpleFunc: " << num << endl;
	}
	void SimpleFunc() const
	{
		cout << "const SimpleFunc: " << num << endl;
	}
};

void YourFunc(const SoSimple &obj)
{
	obj.SimpleFunc();
}

int main(void)
{
	const SoSimple obj(7);
	// obj.AddNum(20);		//const object�� const �ɹ� �Լ��� ȣ�� ���� 
	obj.ShowData();


	SoSimple obj1(2);
	const SoSimple obj2(7);

	obj1.SimpleFunc();
	obj2.SimpleFunc();

	YourFunc(obj1);
	YourFunc(obj2);


	return 0;
}

#endif

// 06-2
/*	Friend	; ���������� ���ʶ߸� �� ������, ������ overloading�� ���ؼ��� �ʿ��ϴ�! 
	�� friend ������ �Լ� ���� ����� ������ ������ �Ѵ�. 
	class�� ������� ���� : friend [class ����]							; ex) friend class boy;
	member�� ������� ���� : friend [member ����; ����������(::) ����]	; ex) friend void boy::ShowYourFriendInfo(Girl &frn);	
	�ܺ� �Լ� ������� ���� : friend [�Լ� ����]	*/
#if 0
#if 0
#include <iostream>
#include <cstring>
using namespace std;

class Girl;

class Boy
{
private:
	int height;
	friend class Girl;				// Girl object -> Boy class�� private���� ���� ���� 
public:
	Boy(int len) : height(len)
	{ }
	void ShowYourFriendInfo(Girl &frn);
};

class Girl
{
private:
	char phNum[20];
public:
	Girl(char * num)
	{
		strcpy_s(phNum, strlen(num)+1 ,num);
	}
	void ShowYourFriendInfo(Boy &frn);
	friend class Boy;
};

void Boy::ShowYourFriendInfo(Girl &frn)
{
	cout << "Her phone number: " << frn.phNum << endl;
}

void Girl::ShowYourFriendInfo(Boy &frn)
{
	cout << "His height: " << frn.height << endl;
}

int main(void)
{
	Boy boy(170);
	Girl girl("010-1234-5678");

	boy.ShowYourFriendInfo(girl);
	girl.ShowYourFriendInfo(boy);
	return 0;
}
#elif 0
#include <iostream>
using namespace std;

class Point;

class PointOP	// Point �Լ��� operation time�� ������� class 
{
private:
	int opcnt;
public:
	PointOP() : opcnt(0)
	{  }

	Point PointAdd(const Point&, const Point&);
	Point PointSub(const Point&, const Point&);
	~PointOP()
	{
		cout << "Operation times: " << opcnt << endl;
	}
};

class Point
{
private:
	int x;
	int y;
public:
	Point(const int &xpos, const int &ypos) : x(xpos), y(ypos)
	{  }
	friend Point PointOP::PointAdd(const Point&, const Point&);
	friend Point PointOP::PointSub(const Point&, const Point&);
	friend void ShowPointPos(const Point&);
};

Point PointOP::PointAdd(const Point& pnt1, const Point& pnt2)
{
	opcnt++;
	return Point(pnt1.x + pnt2.x, pnt1.y + pnt2.y);
}

Point PointOP::PointSub(const Point& pnt1, const Point& pnt2)
{
	opcnt++;
	return Point(pnt1.x - pnt2.x, pnt1.y - pnt2.y);
}

int main(void)
{
	Point pos1(1, 2);
	Point pos2(2, 4);
	PointOP op;

	ShowPointPos(op.PointAdd(pos1, pos2));
	ShowPointPos(op.PointSub(pos2, pos1));
	return 0;
}

void ShowPointPos(const Point& pos)
{
	cout << "x: " << pos.x << ", ";
	cout << "y: " << pos.y << endl;
}
#endif 
#endif

// 06-3
/*	Static ; ���������� ����� �ϵ� �������� ���ټ��� ���� ����� ���� �ʿ��ϴ�!  
	�� C����... static ������ �ʱ�ȭ ���� ���� ���, ������ ���� �ƴ� 0���� �ʱ�ȭ �ȴ�. ���� �ѹ��� �ʱ�ȭ�ȴ�; ������ ������ �Լ��� ���͵� �ѹ��� ����ȴ�.
	�� C++����...	
		-	static ������ 
			class ���Ǻο� �����ϸ�, ��ü�� �����ϰ� �������� �ʰ�, ��ü �ܺ� �޸� ������ �� �ϳ��� �Ҵ��� �Ǿ� �����Ǵ� ����.(���� �� �Ҹ� ������ ���������� ����)
			class ���� ���ο��� 0���� �ʱ�ȭ �����ϸ� ������; class �ۿ��� 0���� �ʱ�ȭ �����ؾ��Ѵ�.
			private: �ش� Ŭ������ ��ü�鸸 ���� ����
			public : �ش� Ŭ������ �̸� or ��ü�� �̸��� ���� ��𼭵� ���� ����	 
		-	static ����Լ���
			class ���Ǻο� �����ϸ�, static �������� Ư���� �״�� ����
			�� ����� �ڸ��� ��ġ������, �޸� ������ ��ü �ܺο� �Ҵ��� �ǹǷ�, member variable�� �������� ���� �Ұ�, static member ������ member �Լ��� ���ٰ���
		-	const static member ������ class ���Ǻο� ������ ���,
			const�� Ư���� const  �ɹ� ����� ������(������ ����; ������� ����)�� ����� ���ÿ� �ʱ�ȭ�ؾ� �ϹǷ�, 
			����� ���ÿ� �ʱ�ȭ �ؾ��Ѵ�.*/
#if 0
#if 0 // CComStatic.cpp
/*	���������� �����Ѱ� ������, �ٸ���
	���������� �����Ѱ� ������, �ٸ���. */
#include <iostream>
using namespace std;

void Counter()
{
	static int cnt;	// ������ ������ �Լ��� ���͵� �ѹ��� ����ȴ�. �ʱⰪ 0
	cnt++;
	cout << "Current cnt: " << cnt << endl;
}

int main(void)
{
	for (int i = 0; i<10; i++)
		Counter();
	return 0;
}
#elif 0
/*	StaticMember.cpp
	class �� member variable�μ��� static ����; ������ member variable�� �Ȱ��� �ƴϴ�.  
	�� class �� objects���� �� ������ share�ϰ� ���� �� �ַ� ��� */
#include <iostream>
using namespace std;

class SoSimple
{
private:
	static int simObjCnt;
public:
	SoSimple()
	{
		simObjCnt++;
		cout << simObjCnt << "��° SoSimple ��ü" << endl;
	}
};
int SoSimple::simObjCnt = 0;	// �ܺο��� �ʱ�ȭ�� �ؾ��Ѵ�. why? ��ü�� �����ɶ� �����Ǵ� ������ �ƴ�, �̹� �޸� ������ �Ҵ��� �̷���� �����̱� �����̴�.

class SoComplex
{
private:
	static int cmxObjCnt;
public:
	SoComplex()
	{
		cmxObjCnt++;
		cout << cmxObjCnt << "��° SoComplex ��ü" << endl;
	}
	SoComplex(SoComplex &copy)
	{
		cmxObjCnt++;
		cout << cmxObjCnt << "��° SoComplex ��ü" << endl;
	}
};
int SoComplex::cmxObjCnt = 0;

int main(void)
{
	SoSimple sim1;
	SoSimple sim2;

	SoComplex cmx1;
	SoComplex cmx2 = cmx1;
	SoComplex();
	return 0;
}

#elif 0
/*	PublicStaticMember.cpp
	public ������ �ִ� static ���� 
	�������� ���� : Sosimple:simobjCnt */
#include <iostream>
using namespace std;

class SoSimple
{
public:
	static int simObjCnt;
public:
	SoSimple()
	{
		simObjCnt++;
	}
};
int SoSimple::simObjCnt = 0;

int main(void)
{
	cout << SoSimple::simObjCnt << "��° SoSimple ��ü" << endl;
	SoSimple sim1;
	SoSimple sim2;

	cout << SoSimple::simObjCnt << "��° SoSimple ��ü" << endl;
	cout << sim1.simObjCnt << "��° SoSimple ��ü" << endl;
	cout << sim2.simObjCnt << "��° SoSimple ��ü" << endl;
	return 0;
}
#elif 0
/* const static member variable 
	- ��ü ���� ���� ��밡��		*/
#include <iostream>
using namespace std;

class CountryArea
{
public:
	const static int RUSSIA = 1707540;
	const static int CANADA = 998467;
	const static int CHINA = 957290;
	const static int SOUTH_KOREA = 9922;
};

int main(void)
{
	cout << "���þ� ����: " << CountryArea::RUSSIA << "��" << endl;
	cout << "ĳ���� ����: " << CountryArea::CANADA << "��" << endl;
	cout << "�߱� ����: " << CountryArea::CHINA << "��" << endl;
	cout << "�ѱ� ����: " << CountryArea::SOUTH_KOREA << "��" << endl;
	return 0;
}
#endif
#endif 