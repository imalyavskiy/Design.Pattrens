#include <iostream>
#include <string>

class Colleague;
class Mediator;
class ConcreteMediator;
class ConcreteColleague1;
class ConcreteColleague2;

class Mediator
{
public:
	virtual void Send(std::string const& message, Colleague *colleague) const = 0;
};

class Colleague
{
protected:
	Mediator* mediator_;

public:
	explicit Colleague(Mediator *mediator) :mediator_(mediator)
	{
	}

	virtual void Send(std::string const& message) = 0;
	virtual void Notify(std::string const& message) = 0;
};

class ConcreteColleague1 :public Colleague
{
public:
	explicit ConcreteColleague1(Mediator* mediator) 
		: Colleague(mediator)
	{
	}

	void Send(std::string const& message) override
	{
		mediator_->Send(message, this);
	}

	void Notify(std::string const& message) override
	{
		std::cout << "Colleague1 gets message '" << message << "'" << std::endl;
	}
};

class ConcreteColleague2 :public Colleague
{
public:
	explicit ConcreteColleague2(Mediator *mediator) :Colleague(mediator)
	{
	}

	void Send(std::string const& message) override
	{
		mediator_->Send(message, this);
	}

	void Notify(std::string const& message) override
	{
		std::cout << "Colleague2 gets message '" << message << "'" << std::endl;
	}
};

class ConcreteMediator :public Mediator
{
protected:
	Colleague      *m_Colleague1;
	Colleague      *m_Colleague2;

public:
	void SetColleague(Colleague *c)
	{
		if (!m_Colleague1)
			m_Colleague1 = c;
		else if (!m_Colleague2)
			m_Colleague2 = c;
	}

	virtual void Send(std::string const& message, Colleague *colleague) const override
	{
		if (colleague == m_Colleague1)
		{
			m_Colleague2->Notify(message);
		}
		else if (colleague == m_Colleague2)
		{
			m_Colleague1->Notify(message);
		}
	}
};

int main()
{
	ConcreteMediator  mediator;

	ConcreteColleague1 colleague_1(&mediator);
	ConcreteColleague2 colleague_2(&mediator);

	mediator.SetColleague(&colleague_1);
	mediator.SetColleague(&colleague_2);

	colleague_1.Send("How are you?");
	colleague_2.Send("Fine, thanks");

	std::cin.get();
	return 0;
}

/*
Output
Colleague2 gets message 'How are you?'
Colleague1 gets message 'Fine, thanks'
*/