#ifndef __RECTANGLE_H_
#define __RECTANGLE_H_

#include "Point.h"

class Rectangle
{
private:
	Point upLeft;
	Point lowRight;

public:

#if 1		// 	RectangleConstructor.cpp ; Point, Rectangle class�� Constructor �߰� ���� 
	Rectangle(const int &x1, const int &y1, const int &x2, const int &y2);
#else
	// ���ڷ� const Point &ul, const Point &lr ��������Ƿ�, Point ��ü�� access function�� �̰����� �����ٸ� �ݵ�� const �Լ��� �Ǿ���Ѵ�.	int GetX() const;
	bool InitMembers(const Point &ul, const Point &lr);
#endif

	void ShowRecInfo() const;			// const �Լ��� ���� �ʾƵ� ������, Information Hiding ��Ģ�� ������Ű�� ���� const�� �ߴ�.
};

#endif
