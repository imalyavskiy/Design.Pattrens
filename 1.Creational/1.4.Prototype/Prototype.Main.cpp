#include <iostream>
#include <string>
#include <memory>
#include <random>

class Meal {
public:
	virtual ~Meal() = default;

	// Uses this as prototype for new instance of a child
	virtual std::shared_ptr<Meal> clone() const = 0;

	virtual const std::string& WhatIsThis() = 0;
};

class Spaghetti : public Meal 
{
protected:
	const std::string name = "Spaghetti";

public:
	Spaghetti() = default;
	Spaghetti(const Spaghetti& other) = default;

	std::shared_ptr<Meal> clone() const override
	{ 
		return std::shared_ptr<Meal>(new Spaghetti(*this));
	}

	const std::string& WhatIsThis() override
	{
		return name;
	}
};

class Lasagne : public Meal
{
protected:
	const std::string name = "Lasagne";

public:
	Lasagne() = default;
	Lasagne(const Lasagne& other) = default;

	std::shared_ptr<Meal> clone() const override
	{
		return std::shared_ptr<Meal>(new Lasagne(*this));
	}

	const std::string& WhatIsThis() override
	{
		return name;
	}
};

std::shared_ptr<Meal> dice_drop(const std::shared_ptr<Meal>& _1, const std::shared_ptr<Meal>& _2)
{
	// Instances at _1 and _2 are used as prototypes for returned instance of _1 or _2 chosen randomly. 
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 10);


	if(dis(gen) % 2)
		return _1->clone();
	return _2->clone();
}

void main()
{
	std::shared_ptr<Meal> spaghetti(new Spaghetti());
	std::shared_ptr<Meal> lasagne(new Lasagne());

	std::shared_ptr<Meal> chance(dice_drop(spaghetti, lasagne));

	std::cout << "You've got: "<< chance->WhatIsThis() << std::endl;

	return;
}