#include <iostream>
#include <string>
#include <memory>
#include <locale.h>

/**
* ��������������� �����, ����������� ��������� ������������
*/
class CriminalAction {

	friend class Policeman;     // ����������� ����� ������ � ���������� ���������

	int complexity;             // ��������� ����

	const std::string description;    // ������� �������� ������������

public:
	CriminalAction(int complexity, const std::string& description) : complexity(complexity), description(description) {}
	
	typedef std::shared_ptr<CriminalAction> ptr;
};

/**
* ����������� �����������, ������� ����� ���������� �������������� ������������
*/

class Policeman 
{
public:
	typedef std::shared_ptr<Policeman> ptr;

protected:

	int deduction;      // �������� (������ ����������� ������� ����) � ������� ������������

	ptr next;    // ����� ������ �����������, ������� ������� ����, ���� ��� �������� ��� ������� �������

	virtual void investigateConcrete(const std::string& description) {}    // ���������� �������������

public:

	Policeman(int deduction) : deduction(deduction) {}

	virtual ~Policeman() {
		next.reset();
	}

	/**
	* ��������� � ������� ��������������� ����� �������� ������������, ������� ������ ������� �� ����
	* �������������, ���� ������� �� ���������
	*/
	ptr setNext(ptr& policeman) {
		next = policeman;
		return next;
	}

	/**
	* ����������� �������� ������������� ���, ���� ���� ������� �������, �������� �� ����� �������� �������
	*/
	void investigate(CriminalAction::ptr& criminalAction) 
	{
		if (deduction < criminalAction->complexity) 
		{
			if (next)
				next->investigate(criminalAction);
			else
				std::cout << "��� ���� �� �������� ������." << std::endl;
		}
		else 
		{
			investigateConcrete(criminalAction->description);
		}
	}
};

class MartinRiggs : public Policeman {

protected:

	void investigateConcrete(const std::string& description) override 
	{
		std::cout << "������������� �� ���� \"" << description << "\" ����� ������� ������ �����" << std::endl;
	}

public:

	MartinRiggs(int deduction) : Policeman(deduction) {}
};

class JohnMcClane : public Policeman {

protected:

	void investigateConcrete(const std::string& description) override
	{
		std::cout << "������������� �� ���� \"" << description << "\" ����� �������� ���� ��������" << std::endl;
	}

public:
	JohnMcClane(int deduction) : Policeman(deduction) {}
};

class VincentHanna : public Policeman {

protected:

	void investigateConcrete(const char* description) {
		std::cout << "������������� �� ���� \"" << description << "\" ����� ��������� ������� �����" << std::endl;
	}

public:
	VincentHanna(int deduction) : Policeman(deduction) {}
};

int main() {
	setlocale(LC_ALL, "Russian");

	std::cout << "OUTPUT:" << std::endl;
	Policeman::ptr policeman(new MartinRiggs(3));  // ����������� � ���������� ������� ������� �������������
	policeman
		->setNext(Policeman::ptr(new JohnMcClane(5)))
		->setNext(Policeman::ptr(new VincentHanna(8)));     // ��������� ��� ���� ������� ������
	policeman->investigate(CriminalAction::ptr(new CriminalAction(2, "�������� ����������� �� ��������")));
	policeman->investigate(CriminalAction::ptr(new CriminalAction(7, "������� ���������� ����� � ������ ���-���������")));
	policeman->investigate(CriminalAction::ptr(new CriminalAction(5, "����� ������� � ������ ���-�����")));
	return 0;
}

/**
* OUTPUT:
* ������������� �� ���� "�������� ����������� �� ��������" ����� ������� ������ �����
* ������������� �� ���� "������� ���������� ����� � ������ ���-���������" ����� ��������� ������� �����
* ������������� �� ���� "����� ������� � ������ ���-�����" ����� �������� ���� ��������
*/