#include <iostream>
#include "Point.h"
using namespace std;

#if 1			// RectangleConstructor.cpp ; Point, Rectangle class의 Constructor 추가 버전 
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
		cout<<"벗어난 범위의 값 전달"<<endl;
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
		cout<<"벗어난 범위의 값 전달"<<endl;
		return false;
	}

	x=xpos;
	return true;
}	
bool Point::SetY(int ypos)
{
	if(0>ypos || ypos>100)
	{
		cout<<"벗어난 범위의 값 전달"<<endl;
		return false;
	}

	y=ypos;
	return true;
}