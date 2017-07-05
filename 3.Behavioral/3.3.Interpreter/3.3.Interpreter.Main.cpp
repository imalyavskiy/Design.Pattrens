#include <iostream>
#include <list>

/// The 'Context' class
class Context
{
};

/// The 'AbstractExpression' abstract class
class AbstractExpression
{
public:
	virtual void Interpret(Context* context) = 0;
};

/// The 'TerminalExpression' class
class TerminalExpression : public AbstractExpression
{
public: 
	void Interpret(Context* context) override
	{
		std::cout << "Called Terminal.Interpret()" << std::endl;
	}
};

/// The 'NonterminalExpression' class
class NonterminalExpression : public AbstractExpression
{
public:
	void Interpret(Context* context) override
	{
		std::cout << "Called Nonterminal.Interpret()" << std::endl;
	}
};

/// Entry point into console application.
void main()
{
	Context* context = new Context();

	// Usually a tree
	std::list<AbstractExpression*> list;

	// Populate 'abstract syntax tree'
	list.push_back(new TerminalExpression());
	list.push_back(new NonterminalExpression());
	list.push_back(new TerminalExpression());
	list.push_back(new TerminalExpression());

	// Interpret
	for( AbstractExpression* p : list)
	{
		p->Interpret(context);
	}
}


/* Output
Called Terminal.Interpret()
Called Nonterminal.Interpret()
Called Terminal.Interpret()
Called Terminal.Interpret()
*/