// 06-1
/*	Const	; ConstObject.c, ConstOverloading.c
	const object는 const 맴버 함수만 호출 가능 
	const 함수 overloading 가능
	※ Const 맴버 변수(= const  맴버 상수)와 참조자는 선언과 동시에 초기화 해야하는데 Member Initializer를 이용하면 초기화가 가능하다 . */
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
	// obj.AddNum(20);		//const object는 const 맴버 함수만 호출 가능 
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
/*	Friend	; 정보은닉을 무너뜨릴 수 있으나, 연산자 overloading을 위해서는 필요하다! 
	※ friend 선언은 함수 원형 선언과 동일한 역할을 한다. 
	class를 대상으로 선언 : friend [class 선언문]							; ex) friend class boy;
	member를 대상으로 선언 : friend [member 선언문; 접근지시자(::) 포함]	; ex) friend void boy::ShowYourFriendInfo(Girl &frn);	
	외부 함수 대상으로 선언 : friend [함수 선언문]	*/
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
	friend class Girl;				// Girl object -> Boy class의 private으로 접근 가능 
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

class PointOP	// Point 함수의 operation time을 재기위한 class 
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
/*	Static ; 전역변수의 기능은 하되 안정적인 접근성을 갖는 사용을 위해 필요하다!  
	※ C에서... static 변수는 초기화 하지 않을 경우, 쓰레기 값이 아닌 0으로 초기화 된다. 또한 한번만 초기화된다; 선언문은 여러번 함수에 들어와도 한번만 실행된다.
	※ C++에서...	
		-	static 변수를 
			class 정의부에 선언하면, 객체를 생성하건 생성하지 않건, 객체 외부 메모리 공간에 딱 하나만 할당이 되어 공유되는 변수.(생성 및 소멸 시점은 전역변수와 동일)
			class 정의 내부에서 0으로 초기화 선언하면 에러남; class 밖에서 0으로 초기화 선언해야한다.
			private: 해당 클래스의 객체들만 접근 가능
			public : 해당 클래스의 이름 or 객체의 이름을 통해 어디서든 접근 가능	 
		-	static 멤버함수를
			class 정의부에 선언하면, static 변수때와 특성이 그대로 적용
			★ 멤버의 자리에 위치하지만, 메모리 공간이 객체 외부에 할당이 되므로, member variable에 직접적인 접근 불가, static member 변수와 member 함수만 접근가능
		-	const static member 변수를 class 정의부에 선언할 경우,
			const의 특성은 const  맴버 상수와 참조자(변수만 가능; 상수변수 포함)는 선언과 동시에 초기화해야 하므로, 
			선언과 동시에 초기화 해야한다.*/
#if 0
#if 0 // CComStatic.cpp
/*	전역변수와 유사한것 같지만, 다르다
	지역변수와 유사한것 같지만, 다르다. */
#include <iostream>
using namespace std;

void Counter()
{
	static int cnt;	// 선언문은 여러번 함수에 들어와도 한번만 실행된다. 초기값 0
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
	class 의 member variable로서의 static 선언; 실제로 member variable이 된것은 아니다.  
	한 class 의 objects들이 한 변수를 share하고 싶을 때 주로 사용 */
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
		cout << simObjCnt << "번째 SoSimple 객체" << endl;
	}
};
int SoSimple::simObjCnt = 0;	// 외부에서 초기화를 해야한다. why? 객체가 생성될때 생성되는 변수가 아닌, 이미 메모리 공간에 할당이 이루어진 변수이기 때문이다.

class SoComplex
{
private:
	static int cmxObjCnt;
public:
	SoComplex()
	{
		cmxObjCnt++;
		cout << cmxObjCnt << "번째 SoComplex 객체" << endl;
	}
	SoComplex(SoComplex &copy)
	{
		cmxObjCnt++;
		cout << cmxObjCnt << "번째 SoComplex 객체" << endl;
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
	public 영역에 있는 static 변수 
	정석적인 접근 : Sosimple:simobjCnt */
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
	cout << SoSimple::simObjCnt << "번째 SoSimple 객체" << endl;
	SoSimple sim1;
	SoSimple sim2;

	cout << SoSimple::simObjCnt << "번째 SoSimple 객체" << endl;
	cout << sim1.simObjCnt << "번째 SoSimple 객체" << endl;
	cout << sim2.simObjCnt << "번째 SoSimple 객체" << endl;
	return 0;
}
#elif 0
/* const static member variable 
	- 객체 생성 없이 사용가능		*/
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
	cout << "러시아 면적: " << CountryArea::RUSSIA << "㎢" << endl;
	cout << "캐나다 면적: " << CountryArea::CANADA << "㎢" << endl;
	cout << "중국 면적: " << CountryArea::CHINA << "㎢" << endl;
	cout << "한국 면적: " << CountryArea::SOUTH_KOREA << "㎢" << endl;
	return 0;
}
#endif
#endif 