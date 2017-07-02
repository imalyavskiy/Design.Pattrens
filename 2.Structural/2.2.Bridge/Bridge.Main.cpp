#include <iostream>
#include <memory>

class Implementor
{
public:
	virtual void Operation() = 0;
};

class ConcreteImplementorA : public Implementor
{
public:
	void Operation() override
	{
		std::cout << "ConcreteImplementorA Operation" << std::endl;
	}
};

class ConcreteImplementorB : public Implementor
{
public:
	void Operation() override
	{
		std::cout << "ConcreteImplementorB Operation" << std::endl;
	}
};

class Abstraction
{
protected:
	// This aggregation is The Bridge itself.
	std::shared_ptr<Implementor> m_pImplementor;

public:
	
	std::shared_ptr<Implementor> getImplementor()
	{
		return m_pImplementor;
	};

	void setImplementor(const std::shared_ptr<Implementor>& a)
	{
		m_pImplementor = a;
	}

	virtual void Operation()
	{
		m_pImplementor->Operation();
	}
};

class RefinedAbstraction : public Abstraction
{
public:
	void Operation() override
	{
		m_pImplementor->Operation();
	}
};

// MainApp test application
void main()
{
	std::shared_ptr<Abstraction> ab(new RefinedAbstraction());

 	// Set implementation and call
	std::shared_ptr<ConcreteImplementorA> ImpA(new ConcreteImplementorA);
 	ab->setImplementor(std::static_pointer_cast<Implementor>(ImpA));
 	ab->Operation();
 
 	// Change implementation and call
	std::shared_ptr<ConcreteImplementorB> ImpB(new ConcreteImplementorB);
 	ab->setImplementor(std::static_pointer_cast<Implementor>(ImpB));
 	ab->Operation();
}
