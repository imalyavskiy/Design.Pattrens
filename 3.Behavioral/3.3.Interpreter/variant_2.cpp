#include <iostream>
#include <map>
#include <string>
#include <memory>

#include "variant_2.h"

using namespace variant_2;

// 	Контекст среды исполнения интерпретатора
class Context
{
protected:
	std::map<std::string, bool> _variables;
public:
	Context()
	{
// 		:param variables: словарь соответствий имен переменных их значениям
	}

// 	Исключение, прокидываемое в случае некорректной работы с данным классом
	class ContextException : public std::exception
	{
	protected:
		const std::string _description;
	public:
		ContextException(const std::string description)
			: _description(description)
		{
			;
		}

		char const* what() const override
		{
			return _description.c_str();
		}
	};

	bool& lookup(const std::string& name)
	{
// 		Получает значение переменной по ее имени
// 		:param name: имя переменной
		auto it = _variables.find(name);
		if (it != _variables.end())
			return _variables[name];

		throw ContextException(std::string("Неизвестная переменная ") + name);
	}

	void assign(std::string name, bool value)
	{
// 		Назначает значение переменной по ее имени
// 		:param name: имя переменной
// 		:param value: значение переменной
		_variables[name] = value;
	}
};

//	Абстрактное логическое выражение
class BooleanExp
{
public:
//	Получение результата логического выражения
	virtual bool evaluate(Context& context) const = 0;

	typedef std::shared_ptr<BooleanExp> ptr;
};

//	Логическая константа
class ConstantExp : public BooleanExp
{
protected:
	const bool _value;

public:
	ConstantExp(bool value)
// 		:param value: значение выражения (True или False)
		: _value(value)
	{
	}

	bool evaluate(Context& context) const override
	{
		return _value;
	}
};

//	Логическая переменная (значение переменных хранится в объекте контекста интерпретатора)
class VariableExp : public BooleanExp
{
protected:
	const std::string _name;

public:
	VariableExp(std::string name)
		// 		:param name: название переменной
		: _name(name)
	{
		;
	}

	bool evaluate(Context& context) const override
	{
		return context.lookup(_name);
	}
};

//	Абстрактный класс для бинарных логических операций
class BinaryOperationExp : public BooleanExp
{
protected:
	const BooleanExp* _left;
	const BooleanExp* _right;

public:

	~BinaryOperationExp()
	{
		delete _left;
		_left = nullptr;
		
		delete _right;
		_right = nullptr;
	}

	BinaryOperationExp(const BooleanExp* left, const BooleanExp* right)
		: _left(left)
		, _right(right)
	{
		;
	}
};

//	Конъюнкция
class AndExp 
	: public BinaryOperationExp
{
public:
	AndExp(const BooleanExp* left, const BooleanExp* right)
		: BinaryOperationExp(left, right)
	{
		;
	}

	bool evaluate(Context& context) const override
	{
		return _left->evaluate(context) && _right->evaluate(context);
	}
};

//	Дизъюнкция
class OrExp : public BinaryOperationExp
{
public:
	OrExp(const BooleanExp* left, const BooleanExp* right)
		: BinaryOperationExp(left, right)
	{
		;
	}

	bool evaluate(Context& context) const override
	{
		return _left->evaluate(context) || _right->evaluate(context);
	}
};

//	Отрицание
class NotExp 
	: public BooleanExp
{
protected:
	BooleanExp* _operand;
public:
//	:param operand: операнд, к которому применяется операция
	NotExp(BooleanExp* operand)
		: _operand(operand)
	{
		;
	}

	bool evaluate(Context& context) const override
	{
		return !_operand->evaluate(context);
	}
};

void execute_test(Context& context, bool x, bool y)
{
//	Функция для выполнения тестирования нашего интерпретатора
	context.assign("x", x);
	context.assign("y", y);

	//(True and x) or (у and (not x))
	BooleanExp::ptr expression(new OrExp(new AndExp(new ConstantExp(true), new VariableExp("x")), new AndExp(new VariableExp("y"), new NotExp(new VariableExp("x")))));

	std::cout << (expression->evaluate(context) ? "true" : "false") << std::endl;
}

void variant_2::test()
{
	std::cout << "OUTPUT:" << std::endl;
	
	Context context;

	execute_test(context, true, false);
	execute_test(context, false, true);
	execute_test(context, false, false);
}

/*
OUTPUT:
True
True
False
*/