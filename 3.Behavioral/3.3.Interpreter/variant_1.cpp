#include <iostream>
#include <list>

#include "variant_1.h"

using namespace variant_1;

void variant_1::test()
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
	for (AbstractExpression* p : list)
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