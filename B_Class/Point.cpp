#include <iostream>
#include "Point.h"
using namespace std;

#if 1			// RectangleConstructor.cpp ; Point, Rectangle class�� Constructor �߰� ���� 
Point::Point(const int &xpos, const int &ypos)
{
	x = xpos;
	y = ypos;
}
#else
bool Point::InitMembers(int xpos, int ypos)
{
	if(xpos<0 || ypos<0)
	{
		cout<<"��� ������ �� ����"<<endl;
		return false;
	}
	
	x=xpos;
	y=ypos;
	return true;
}
#endif

//int Point::GetX() { return x;} 
int Point::GetX() const {return x;}
int Point::GetY() const {return y;}

bool Point::SetX(int xpos)
{
	if(0>xpos || xpos>100)
	{
		cout<<"��� ������ �� ����"<<endl;
		return false;
	}

	x=xpos;
	return true;
}	
bool Point::SetY(int ypos)
{
	if(0>ypos || ypos>100)
	{
		cout<<"��� ������ �� ����"<<endl;
		return false;
	}

	y=ypos;
	return true;
}