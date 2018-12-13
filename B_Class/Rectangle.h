#ifndef __RECTANGLE_H_
#define __RECTANGLE_H_

#include "Point.h"

class Rectangle
{
private:
	Point upLeft;
	Point lowRight;

public:

#if 1		// 	RectangleConstructor.cpp ; Point, Rectangle class의 Constructor 추가 버전 
	Rectangle(const int &x1, const int &y1, const int &x2, const int &y2);
#else
	// 인자로 const Point &ul, const Point &lr 사용했으므로, Point 객체의 access function이 이곳에서 쓰였다면 반드시 const 함수가 되어야한다.	int GetX() const;
	bool InitMembers(const Point &ul, const Point &lr);
#endif

	void ShowRecInfo() const;			// const 함수로 하지 않아도 되지만, Information Hiding 규칙을 만족시키기 위해 const로 했다.
};

#endif
