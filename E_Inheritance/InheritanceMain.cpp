// [Chap7]
/*	Inheritance�� ���α׷��� �������� Ȯ�强�� �����̴�. 
	�Ϲ������� Class�� 2���� �������� ������. 
	1. Data oriented class	; �������� ������ ���ϴ�(derived class, sub class)
	2. func oriendted class ; Control Class, or handler class */

//	07-2;
/*	����� �ްԵǸ�, ����� ��������, ������ ���� ���� 
	class [child class name] : [���� ���� ������(public, or private, or protected)] [parent class name]
	��	child �����ڿ� parient ������ �����ؾ���
		private member �� ��ӹ��� ���, ::���� ���������� ���� ����(�������� �Ұ�) 
		public member �� ��ӹ��� ���, ::���� or access func ����, ���� ���� ����	*/
#if 0
/* �����ڿ� �Ҹ��ڴ� �ӽð�ü �̹Ƿ� Stack������ �Ҵ�ȴ�. �� ������ ���̰��ִ�. */
#include <iostream>
using namespace std;

class SoBase
{
private:
	int baseNum;
public:
	SoBase(int n) : baseNum(n)
	{
		cout << "SoBase() : " << baseNum << endl;
	}
	~SoBase()
	{
		cout << "~SoBase() : " << baseNum << endl;
	}
};

class SoDerived : public SoBase
{
private:
	int derivNum;
public:
	SoDerived(int n) : SoBase(n), derivNum(n)
	{
		cout << "SoDerived() : " << derivNum << endl;
	}
	~SoDerived()
	{
		cout << "~SoDerived() : " << derivNum << endl;
	}
};

int main(void)
{
	SoDerived drv1(15);
	SoDerived drv2(27);
	return 0;
};
#endif

// 07-3
/*	���� ���� ������(access specifier)
	class �� ��ӿ� ���� �����ؾ��� ���� ���� ���� ���
	class Base;
	class Derived : [access specfier] Base
	{
	[access specfier] :
	member ...
	};
	��	member ���� access specifier.. 
		private	: Ŭ���� �ܺο��� ���ٺҰ�		; derived class �������� �Ұ�, ���������� ���ٰ���
		protected : Ŭ���� �ܺο��� ���� �Ұ�	; derived class �������� ����!
		public :	Ŭ���� �ܺο��� ���� ����	; derived class �������� ����!
												# ��� Class ���� ���ο����� �θ� class�� private ��� ����� ��� ���� ���ٰ���
	��	class ���� access specifier 
		protected ����� ��� ; �θ��� ����� protected �̻��� ���� ������ protectedȭ ��Ű�� ��ӹ޴´�. 
					private	: Ŭ���� �ܺο��� ���ٺҰ�		; derived class ����, ���� �Ұ�; ���������� ���ٰ���
					protected : Ŭ���� �ܺο��� ���� �Ұ�	; derived class	����, protectedȭ; Ŭ���� �ܺο��� ���� �Ұ� ;
					public :	Ŭ���� �ܺο��� ���� ����	; derived class ����, protectedȭ; Ŭ���� �ܺο��� ���� �Ұ� ;
		private ����� ��� ; �θ��� ����� protected �̻��� ���� ������ private ȭ ��Ű�� ��ӹ޴´�.
					private	: Ŭ���� �ܺο��� ���ٺҰ�		; derived class ����, ���� �Ұ�; ���������� ���ٰ���
					protected : Ŭ���� �ܺο��� ���� �Ұ�	; derived class	����, protectedȭ; Ŭ���� �ܺο��� ���� �Ұ� ;
					public :	Ŭ���� �ܺο��� ���� ����	; derived class ����, protectedȭ; Ŭ���� �ܺο��� ���� �Ұ� ;
		private ����� ��� ; �θ��� ����� private ����� �����ϰ�� �״�� ��� �ްڴ�. 
					# ��κ��� ����� public ����̴�. 
	*/
#if 0
#if 0
/* member���ִ� �θ�Ŭ������ access specifier���� */
#include <iostream>
using namespace std;

class Base
{
private:
	int num1;
protected:
	int num2;
public:
	int num3;
	void ShowData() { cout << num1 << ", " << num2 << num3; }
};

class Derived : public Base
{
public:
	void ShowBaseMember()
	{
		//cout << num1;		//compile error!! direct access is impossible
		cout << num2;
		cout << num3;
	}
};

int main(void)
{
	return 0;
};
#elif 0
/*	class ���� access specifier : protected ���*/
#include <iostream>
using namespace std;

class Base
{
private:
	int num1;
protected:
	int num2;
public:
	int num3;

	Base() : num1(1), num2(2), num3(3)
	{  }
};

// num3�� protectedȭ �Ǿ����Ƿ� class ���� �ȿ����� ���� ��밡��, but Ŭ���� �ܺο��� ���� ��� �Ұ�
class Derived : protected Base { };	

int main(void)
{
	Derived drv;
	//cout << drv.num3 << endl;			// compile error!
	return 0;
}
#elif 0
/*	class ���� access specifier : private ���*/
#include <iostream>
using namespace std;

class Base
{
private:
	int num1;
protected:
	int num2;
public:
	int num3;

	Base() : num1(1), num2(2), num3(3)
	{  }
};

// num2, num3�� private ȭ �Ǿ����Ƿ� class ���� �ȿ����� �������� ����, �ܺο����� �Ұ�
class Derived : private Base { };

int main(void)
{
	Derived drv;
	//cout << drv.num2 << endl;
	//cout << drv.num3 << endl;			// compile error!
	return 0;
}
#endif

#endif

// 07-4 ����� ��������
/*	����� ���̴� ��� 
	1. Is - a ���� �϶� : [derived class] is a [base class] ; ���� ��ӿ� ������ ����. 
	2. has - a �����϶� :  [derived class] has a [base class] ; ��� ���� ������, ������ �� �� �ִ�. */
#if 0
#if 0
/* is a ���� */
#include <iostream>
#include <cstring>
using namespace std;

class Computer
{
private:
	char owner[50];
public:
	Computer(char * name)
	{
		strcpy_s(owner, strlen(name)+1, name);
	}
	void Calculate()
	{
		cout << "��û ������ ����մϴ�." << endl;
	}
};

class NotebookComp : public Computer
{
private:
	int battary;
public:
	NotebookComp(char * name, int initChag)
		: Computer(name), battary(initChag)
	{  }
	void Charging() { battary += 5; }
	void UseBattary() { battary -= 1; }
	void MovingCal()
	{
		if (GetBattaryInfo()<1)
		{
			cout << "������ �ʿ��մϴ�." << endl;
			return;
		}

		cout << "�̵��ϸ鼭 ";
		Calculate();
		UseBattary();
	}
	int GetBattaryInfo() { return battary; }
};

class TabletNotebook : public NotebookComp
{
private:
	char regstPenModel[50];
public:
	TabletNotebook(char * name, int initChag, char * pen)
		: NotebookComp(name, initChag)
	{
		strcpy_s(regstPenModel, strlen(pen)+1, pen);
	}
	void Write(char * penInfo)
	{
		if (GetBattaryInfo()<1)
		{
			cout << "������ �ʿ��մϴ�." << endl;
			return;
		}
		if (strcmp(regstPenModel, penInfo) != 0)
		{
			cout << "��ϵ� ���� �ƴմϴ�.";
			return;
		}
		cout << "�ʱ� ������ ó���մϴ�." << endl;
		UseBattary();
	}
};

int main(void)
{
	NotebookComp nc("�̼���", 5);
	TabletNotebook tn("������", 5, "ISE-241-242");
	nc.MovingCal();
	tn.Write("ISE-241-242");
	return 0;
}
#elif 0
/* has a ���� : ���Ѽ������� ���� ���� ǥ�� ��ƴ� */
#include <iostream>
#include <cstring>
using namespace std;

class Gun
{
private:
	int bullet;    	// ������ �Ѿ��� ��
public:
	Gun(int bnum) : bullet(bnum)
	{ }
	void Shut()
	{
		cout << "BBANG!" << endl;
		bullet--;
	}
};

class Police : public Gun
{
private:
	int handcuffs;	    // ������ ������ ��
public:
	Police(int bnum, int bcuff)
		: Gun(bnum), handcuffs(bcuff)
	{  }
	void PutHandcuff()
	{
		cout << "SNAP!" << endl;
		handcuffs--;
	}
};

int main(void)
{
	Police pman(5, 3);	// �Ѿ� 5, ���� 3
	pman.Shut();
	pman.PutHandcuff();
	return 0;
}
#elif 0
/* has a �����϶�, ��� ���� ���� */
#include <iostream>
#include <cstring>
using namespace std;

class Gun
{
private:
	int bullet;    	// ������ �Ѿ��� ��
public:
	Gun(int bnum) : bullet(bnum)
	{ }
	void Shut()
	{
		cout << "BBANG!" << endl;
		bullet--;
	}
};

class Police
{
private:
	int handcuffs;    // ������ ������ ��
	Gun * pistol;     // �����ϰ� �ִ� ����
public:
	Police(int bnum, int bcuff)
		: handcuffs(bcuff)
	{
		if (bnum>0)
			pistol = new Gun(bnum);
		else
			pistol = NULL;
	}
	void PutHandcuff()
	{
		cout << "SNAP!" << endl;
		handcuffs--;
	}
	void Shut()
	{
		if (pistol == NULL)
			cout << "Hut BBANG!" << endl;
		else
			pistol->Shut();
	}
	~Police()
	{
		if (pistol != NULL)
			delete pistol;
	}
};

int main(void)
{
	Police pman1(5, 3);
	pman1.Shut();
	pman1.PutHandcuff();

	Police pman2(0, 3);     // ���Ѽ������� ���� ����
	pman2.Shut();
	pman2.PutHandcuff();
	return 0;
}
#endif
#endif 
