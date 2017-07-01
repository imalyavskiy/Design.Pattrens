#include <memory>
#include <iostream>

// "Adaptee"
class Adaptee
{
public:
	void SpecificRequest()
	{
		std::cout << "Called SpecificRequest()" << std::endl;
	}
};

// "Target"
class Target
{
public:
	virtual void Request()
	{
		std::cout << "Called Target Request()" << std::endl;
	}
};

// "Adapter"
class Adapter : public Target
{
private:
	std::shared_ptr<Adaptee> adaptee;

public:
	Adapter()
		: adaptee(new Adaptee())
	{

	}

	void Request() override
	{
		// Possibly do some other work
		// and then call SpecificRequest
		adaptee->SpecificRequest();
	}
};
	
void main()
{
	// Create adapter and place a request
	std::shared_ptr<Target> target(new Adapter());
	target->Request();
}
