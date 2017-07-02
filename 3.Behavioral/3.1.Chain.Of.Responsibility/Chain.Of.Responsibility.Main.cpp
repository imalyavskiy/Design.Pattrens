#include <iostream>
#include <string>
#include <memory>
#include <locale.h>

/**
* Вспомогательный класс, описывающий некоторое преступление
*/
class CriminalAction {

	friend class Policeman;     // Полицейские имеют доступ к материалам следствия

	int complexity;             // Сложность дела

	const std::string description;    // Краткое описание преступления

public:
	CriminalAction(int complexity, const std::string& description) : complexity(complexity), description(description) {}
	
	typedef std::shared_ptr<CriminalAction> ptr;
};

/**
* Абстрактный полицейский, который может заниматься расследованием преступлений
*/

class Policeman 
{
public:
	typedef std::shared_ptr<Policeman> ptr;

protected:

	int deduction;      // дедукция (умение распутывать сложные дела) у данного полицейского

	ptr next;    // более умелый полицейский, который получит дело, если для текущего оно слишком сложное

	virtual void investigateConcrete(const std::string& description) {}    // собственно расследование

public:

	Policeman(int deduction) : deduction(deduction) {}

	virtual ~Policeman() {
		next.reset();
	}

	/**
	* Добавляет в цепочку ответственности более опытного полицейского, который сможет принять на себя
	* расследование, если текущий не справится
	*/
	ptr setNext(ptr& policeman) {
		next = policeman;
		return next;
	}

	/**
	* Полицейский начинает расследование или, если дело слишком сложное, передает ее более опытному коллеге
	*/
	void investigate(CriminalAction::ptr& criminalAction) 
	{
		if (deduction < criminalAction->complexity) 
		{
			if (next)
				next->investigate(criminalAction);
			else
				std::cout << "Это дело не раскрыть никому." << std::endl;
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
		std::cout << "Расследование по делу \"" << description << "\" ведет сержант Мартин Риггс" << std::endl;
	}

public:

	MartinRiggs(int deduction) : Policeman(deduction) {}
};

class JohnMcClane : public Policeman {

protected:

	void investigateConcrete(const std::string& description) override
	{
		std::cout << "Расследование по делу \"" << description << "\" ведет детектив Джон Макклейн" << std::endl;
	}

public:
	JohnMcClane(int deduction) : Policeman(deduction) {}
};

class VincentHanna : public Policeman {

protected:

	void investigateConcrete(const char* description) {
		std::cout << "Расследование по делу \"" << description << "\" ведет лейтенант Винсент Ханна" << std::endl;
	}

public:
	VincentHanna(int deduction) : Policeman(deduction) {}
};

int main() {
	setlocale(LC_ALL, "Russian");

	std::cout << "OUTPUT:" << std::endl;
	Policeman::ptr policeman(new MartinRiggs(3));  // полицейский с наименьшим навыком ведения расследований
	policeman
		->setNext(Policeman::ptr(new JohnMcClane(5)))
		->setNext(Policeman::ptr(new VincentHanna(8)));     // добавляем ему двух опытных коллег
	policeman->investigate(CriminalAction::ptr(new CriminalAction(2, "Торговля наркотиками из Вьетнама")));
	policeman->investigate(CriminalAction::ptr(new CriminalAction(7, "Дерзкое ограбление банка в центре Лос-Анджелеса")));
	policeman->investigate(CriminalAction::ptr(new CriminalAction(5, "Серия взрывов в центре Нью-Йорка")));
	return 0;
}

/**
* OUTPUT:
* Расследование по делу "Торговля наркотиками из Вьетнама" ведет сержант Мартин Риггс
* Расследование по делу "Дерзкое ограбление банка в центре Лос-Анджелеса" ведет лейтенант Винсент Ханна
* Расследование по делу "Серия взрывов в центре Нью-Йорка" ведет детектив Джон Макклейн
*/