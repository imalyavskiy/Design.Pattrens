// Abstract.Factory.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include <memory>

class AbstractProduct
{
public:
	virtual ~AbstractProduct() {};

	virtual std::string Name() = 0;
};

class AbstractProductA
	: public AbstractProduct
{
public:
	virtual ~AbstractProductA() {};

	std::string Name() override
	{
		return std::string("AbstractProductA");
	}
};

class AbstractProductB
	: public AbstractProduct
{
public:
	virtual ~AbstractProductB() {};

	virtual void Interact(std::shared_ptr<AbstractProductA>& a) = 0;

	std::string Name() override
	{
		return std::string("AbstractProductB");
	}
};


class ProductA1 : public AbstractProductA
{
public:
	virtual ~ProductA1() {};

	std::string Name() override
	{
		return std::string("ProductA1");
	}
};

class ProductB1 : public AbstractProductB
{
public:
	virtual ~ProductB1() {};

	void Interact(std::shared_ptr<AbstractProductA>& a) override
	{
		std::cout << Name() << " interacts with " << a->Name() << std::endl;
	}

	std::string Name() override
	{
		return std::string("ProductB1");
	}
};

class ProductA2 : public AbstractProductA
{
public:
	virtual ~ProductA2() {};

	std::string Name() override
	{
		return std::string("ProductA2");
	}
};

class ProductB2 : public AbstractProductB
{
public:
	void Interact(std::shared_ptr<AbstractProductA>& a) override
	{
		std::cout << Name() << " interacts with " << a->Name() << std::endl;
	}

	std::string Name() override
	{
		return std::string("ProductB2");
	}
};

class AbstractFactory
{
public:
	virtual std::shared_ptr<AbstractProductA> CreateProductA() = 0;
	virtual std::shared_ptr<AbstractProductB> CreateProductB() = 0;
};

class ConcreteFactory1 : public AbstractFactory
{
public:
	std::shared_ptr<AbstractProductA> CreateProductA() override
	{
		return std::make_shared<ProductA1>();
	}

	std::shared_ptr<AbstractProductB> CreateProductB() override
	{
		return std::make_shared<ProductB1>();
	}
};

class ConcreteFactory2 : public AbstractFactory
{
public:
	std::shared_ptr<AbstractProductA> CreateProductA() override
	{
		return std::make_shared<ProductA2>();
	}

	std::shared_ptr<AbstractProductB> CreateProductB() override
	{
		return std::make_shared<ProductB2>();
	}
};

class Client
{
private:
	std::shared_ptr<AbstractProductA> _abstractProductA;
	std::shared_ptr<AbstractProductB> _abstractProductB;

	// Constructor
public:
	Client(std::shared_ptr<AbstractFactory>& factory)
	{
		_abstractProductB = factory->CreateProductB();
		_abstractProductA = factory->CreateProductA();
	}

	void Run()
	{
		_abstractProductB->Interact(_abstractProductA);
	}
};

int main()
{
	// Abstract factory #1
	std::shared_ptr<AbstractFactory> factory1(std::make_shared<ConcreteFactory1>());
	std::shared_ptr<Client>			 client1(std::make_shared<Client>(factory1));
	client1->Run();

	// Abstract factory #2
	std::shared_ptr<AbstractFactory> factory2(std::make_shared<ConcreteFactory2>());
	std::shared_ptr<Client>			 client2(std::make_shared<Client>(factory2));
	client2->Run();

	return 0;
}

