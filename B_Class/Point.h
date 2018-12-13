#ifndef __POINT_H_
#define __POINT_H_

class Point
{
private:
	int x; 
	int y;    

public:

#if 1	// 	RectangleConstructor.cpp ; Point, Rectangle class�� Constructor �߰� ���� 
	Point(const int &xpos, const int &ypos);
#else
	bool InitMembers(int xpos, int ypos);
#endif

//	int GetX();				//		error! why? Rantagle class�� point class �� ��ü�� member ������ �ΰ��ִµ�  Init �Լ����� 
							//		���ڷ� const Point &ul, const Point &lr ��������Ƿ�, Point ��ü�� access function�� �̰����� �����ٸ� const �Լ��� �Ǿ���Ѵ�.	int GetX() const;
	int GetX() const;
	int GetY() const;
	bool SetX(int xpos);
	bool SetY(int ypos);
};

#endif