#pragma once
namespace variant_1
{
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

	void test();
}