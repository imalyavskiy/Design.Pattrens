#pragma once
#ifndef __BUILDER_MAIN_H__
#define __BUILDER_MAIN_H__

// Product
class Pizza
{
private:
	std::string dough;
	std::string sauce;
	std::string topping;

public:
	void SetDough(const std::string& d);
	void SetSauce(const std::string& s);
	void SetTopping(const std::string& t);

	void ShowPizza();
};

// Abstract Builder
class PizzaBuilder
{
protected:
	std::shared_ptr<Pizza> pizza;

public:
	virtual ~PizzaBuilder();

	std::shared_ptr<Pizza> GetPizza();

	void createNewPizzaProduct();

	virtual void buildDough() = 0;
	virtual void buildSauce() = 0;
	virtual void buildTopping() = 0;

};

// ConcreteBuilder
class HawaiianPizzaBuilder 
	: public PizzaBuilder
{
public:
	void buildDough() final override;
	void buildSauce() final override;
	void buildTopping() final override;
};

// ConcreteBuilder
class SpicyPizzaBuilder : public PizzaBuilder
{
public:
	void buildDough() final override;
	void buildSauce() final override;
	void buildTopping() final override;
};

// Director
class Waiter
{
private:
	PizzaBuilder* pizzaBuilder = nullptr;

public:
	void SetPizzaBuilder(PizzaBuilder* b);
	std::shared_ptr<Pizza> GetPizza();
	void ConstructPizza();
};

#endif // __BUILDER_MAIN_H__
