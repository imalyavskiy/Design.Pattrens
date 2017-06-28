#include "stdafx.h"

#include "Builder.Main.h"
// Реализация на C++.

// Product
void 
Pizza::SetDough(const std::string& d) 
{ 
	dough = d; 
}

void 
Pizza::SetSauce(const std::string& s) 
{ 
	sauce = s; 
}

void 
Pizza::SetTopping(const std::string& t) 
{ 
	topping = t; 
}

void 
Pizza::ShowPizza()
{
	std::cout << " Yummy !!!" << std::endl;
	std::cout << "Pizza with Dough as " << dough;
	std::cout << ", Sauce as " << sauce;
	std::cout << " and Topping as " << topping;
	std::cout << " !!! " << std::endl;
}

// Abstract Builder
PizzaBuilder::~PizzaBuilder()
{

}

std::shared_ptr<Pizza> 
PizzaBuilder::GetPizza()
{
	return std::shared_ptr<Pizza>(std::move(pizza)); 
}

void 
PizzaBuilder::createNewPizzaProduct()
{ 
	pizza.reset(new Pizza); 
}

// ConcreteBuilder
void 
HawaiianPizzaBuilder::buildDough() 
{
	pizza->SetDough("cross"); 
}

void 
HawaiianPizzaBuilder::buildSauce() 
{ 
	pizza->SetSauce("mild");
}

void 
HawaiianPizzaBuilder::buildTopping() 
{ 
	pizza->SetTopping("ham and pineapple"); 
}

// ConcreteBuilder
void 
SpicyPizzaBuilder::buildDough() {
	pizza->SetDough("pan baked"); 
}

void 
SpicyPizzaBuilder::buildSauce() 
{
	pizza->SetSauce("hot"); 
}

void 
SpicyPizzaBuilder::buildTopping() 
{ 
	pizza->SetTopping("pepperoni and salami"); 
}

// Director
void 
Waiter::SetPizzaBuilder(PizzaBuilder* b) 
{ 
	pizzaBuilder = b; 
}

std::shared_ptr<Pizza> 
Waiter::GetPizza() 
{ 
	return pizzaBuilder->GetPizza(); 
}

void 
Waiter::ConstructPizza()
{
	pizzaBuilder->createNewPizzaProduct();
	pizzaBuilder->buildDough();
	pizzaBuilder->buildSauce();
	pizzaBuilder->buildTopping();
}

// Client orders 2 pizzas.
int main()
{
	Waiter waiter;
	std::shared_ptr<Pizza> pizza;

	HawaiianPizzaBuilder hawaiianPizzaBuilder;
	waiter.SetPizzaBuilder(&hawaiianPizzaBuilder);
	waiter.ConstructPizza();
	pizza = waiter.GetPizza();
	pizza->ShowPizza();

	SpicyPizzaBuilder spicyPizzaBuilder;
	waiter.SetPizzaBuilder(&spicyPizzaBuilder);
	waiter.ConstructPizza();
	pizza = waiter.GetPizza();
	pizza->ShowPizza();

	return EXIT_SUCCESS;
}