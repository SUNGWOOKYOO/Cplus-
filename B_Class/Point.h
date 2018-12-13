#ifndef __POINT_H_
#define __POINT_H_

class Point
{
private:
	int x; 
	int y;    

public:

#if 1	// 	RectangleConstructor.cpp ; Point, Rectangle class의 Constructor 추가 버전 
	Point(const int &xpos, const int &ypos);
#else
	bool InitMembers(int xpos, int ypos);
#endif

//	int GetX();				//		error! why? Rantagle class는 point class 의 객체를 member 변수로 두고있는데  Init 함수에서 
							//		인자로 const Point &ul, const Point &lr 사용했으므로, Point 객체의 access function이 이곳에서 쓰였다면 const 함수가 되어야한다.	int GetX() const;
	int GetX() const;
	int GetY() const;
	bool SetX(int xpos);
	bool SetY(int ypos);
};

#endif