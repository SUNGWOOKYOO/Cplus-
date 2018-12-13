//	Chap 15

/*	try
	{ 
		if('�����ǰ��'){throw '����';}
		...(�������κ� �ǳ� �ٰ� �ȴ�.)
	}, 
	catch(���� ����){}		*/
#if 0
#include <iostream>
using namespace std;

int main(void)
{
	int num1, num2;
	cout << "�� ���� ���� �Է�: ";
	cin >> num1 >> num2;

	try
	{
		if (num2 == 0)
			throw num2;

		cout << "�������� ��: " << num1 / num2 << endl;
		cout << "�������� ������: " << num1%num2 << endl;
	}
	catch (int expn)
	{
		cout << "������ " << expn << "�� �� �� �����ϴ�." << endl;
		cout << "���α׷��� �ٽ� �����ϼ���." << endl;
	}
	cout << "end of main" << endl;
	return 0;
}
#endif

// �Լ� ���� throw �� �����ϰ� ȣ���� try������ ��� (�Լ��� �����)
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
		cout << "�� ���� ���� �Է�: ";
		cin >> str1 >> str2;

		try
		{
			cout << str1 << " + " << str2 << " = " << StoI(str1) + StoI(str2) << endl;
			break;
		}
		catch (char ch)
		{
			cout << "���� " << ch << "�� �ԷµǾ����ϴ�." << endl;
			cout << "���Է� �����մϴ�." << endl << endl;
		}
	}
	cout << "���α׷��� �����մϴ�." << endl;
	return 0;
}
#endif

/*	���� ������ ���̱� ���� (���ð� ���� ������ ��Ե�)
	����, �ý��� ������ ���ܰ� �ƴ� ��Ȳ���� ���ܰ� �߻��ϸ�,
	�ݵ�� ���ܻ�Ȳ�� ó���ؾ��Ѵ�.
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
		cout << "�����ڵ�: " << expn << endl;
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