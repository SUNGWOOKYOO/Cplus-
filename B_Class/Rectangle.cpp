#include <iostream>
#include "Rectangle.h"
using namespace std;

#if 1			// 	RectangleConstructor.cpp ; Point, Rectangle class�� Constructor �߰� ���� 
Rectangle::Rectangle(const int &x1, const int &y1, const int &x2, const int &y2)
	:upLeft(x1, y1), lowRight(x2, y2)
{
	// empty
}
#else
bool Rectangle::InitMembers(const Point &ul, const Point &lr)
{
	// ���ڷ� const Point &ul, const Point &lr ��������Ƿ�, Point ��ü�� access function�� �̰����� �����ٸ� const �Լ��� �Ǿ���Ѵ�; 
 	if(ul.GetX()>lr.GetX() || ul.GetY()>lr.GetY())
	{
		cout<<"�߸��� ��ġ���� ����"<<endl;
		return false;
	}

	upLeft=ul;
	lowRight=lr;
	return true;
}
#endif

void Rectangle::ShowRecInfo() const					
{
	cout<<"�� ���: "<<'['<<upLeft.GetX()<<", ";
	cout<<upLeft.GetY()<<']'<<endl;
	cout<<"�� �ϴ�: "<<'['<<lowRight.GetX()<<", ";
	cout<<lowRight.GetY()<<']'<<endl<<endl;
}