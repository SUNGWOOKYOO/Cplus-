#include <iostream>
#include "Rectangle.h"
using namespace std;

#if 1			// 	RectangleConstructor.cpp ; Point, Rectangle class의 Constructor 추가 버전 
Rectangle::Rectangle(const int &x1, const int &y1, const int &x2, const int &y2)
	:upLeft(x1, y1), lowRight(x2, y2)
{
	// empty
}
#else
bool Rectangle::InitMembers(const Point &ul, const Point &lr)
{
	// 인자로 const Point &ul, const Point &lr 사용했으므로, Point 객체의 access function이 이곳에서 쓰였다면 const 함수가 되어야한다; 
 	if(ul.GetX()>lr.GetX() || ul.GetY()>lr.GetY())
	{
		cout<<"잘못된 위치정보 전달"<<endl;
		return false;
	}

	upLeft=ul;
	lowRight=lr;
	return true;
}
#endif

void Rectangle::ShowRecInfo() const					
{
	cout<<"좌 상단: "<<'['<<upLeft.GetX()<<", ";
	cout<<upLeft.GetY()<<']'<<endl;
	cout<<"우 하단: "<<'['<<lowRight.GetX()<<", ";
	cout<<lowRight.GetY()<<']'<<endl<<endl;
}