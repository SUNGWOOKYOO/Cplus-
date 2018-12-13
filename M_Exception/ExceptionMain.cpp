//	Chap 15

/*	try
	{ 
		if('예외의경우'){throw '예외';}
		...(나머지부분 건너 뛰게 된다.)
	}, 
	catch(예외 변수){}		*/
#if 0
#include <iostream>
using namespace std;

int main(void)
{
	int num1, num2;
	cout << "두 개의 숫자 입력: ";
	cin >> num1 >> num2;

	try
	{
		if (num2 == 0)
			throw num2;

		cout << "나눗셈의 몫: " << num1 / num2 << endl;
		cout << "나눗셈의 나머지: " << num1%num2 << endl;
	}
	catch (int expn)
	{
		cout << "제수는 " << expn << "이 될 수 없습니다." << endl;
		cout << "프로그램을 다시 실행하세요." << endl;
	}
	cout << "end of main" << endl;
	return 0;
}
#endif

// 함수 내에 throw 를 구성하고 호출을 try내에서 사용 (함수가 종료됨)
#if 0
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int StoI(char * str)
{
	int len = strlen(str);
	int num = 0;

	for (int i = 0; i<len; i++)
	{
		if (str[i]<'0' || str[i]>'9')
			throw str[i];

		num += (int)(pow((double)10, (len - 1) - i) * (str[i] + (7 - '7')));
	}
	return num;
}

int main(void)
{
	char str1[100];
	char str2[200];

	while (1)
	{
		cout << "두 개의 숫자 입력: ";
		cin >> str1 >> str2;

		try
		{
			cout << str1 << " + " << str2 << " = " << StoI(str1) + StoI(str2) << endl;
			break;
		}
		catch (char ch)
		{
			cout << "문자 " << ch << "가 입력되었습니다." << endl;
			cout << "재입력 진행합니다." << endl << endl;
		}
	}
	cout << "프로그램을 종료합니다." << endl;
	return 0;
}
#endif

/*	위의 구조를 보이기 위해 (스택과 같은 구조를 띄게됨)
	따라서, 시스템 오류의 예외가 아닌 상황에서 예외가 발생하면,
	반드시 예외상황을 처리해야한다.
*/
#if 0
#include <iostream>
using namespace std;

void SimpleFuncOne(void);
void SimpleFuncTwo(void);
void SimpleFuncThree(void);

int main(void)
{
	try
	{
		SimpleFuncOne();
	}
	catch (int expn)
	{
		cout << "예외코드: " << expn << endl;
	}
	return 0;
}

void SimpleFuncOne(void)
{
	cout << "SimpleFuncOne(void)" << endl;
	SimpleFuncTwo();
}
void SimpleFuncTwo(void)
{
	cout << "SimpleFuncTwo(void)" << endl;
	SimpleFuncThree();
}
void SimpleFuncThree(void)
{
	cout << "SimpleFuncThree(void)" << endl;
	throw - 1;
}
#endif