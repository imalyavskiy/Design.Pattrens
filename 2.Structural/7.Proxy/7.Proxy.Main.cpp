#include <memory>
#include <iostream>

/**
* "Subject"
*/
class IMath
{
public:
	virtual double add(double, double) = 0;
	virtual double sub(double, double) = 0;
	virtual double mul(double, double) = 0;
	virtual double div(double, double) = 0;
};

/**
* "Real Subject"
*/
class Math : public IMath
{
public:
	double add(double x, double y) override
	{
		return x + y;
	}

	double sub(double x, double y) override
	{
		return x - y;
	}

	double mul(double x, double y) override
	{
		return x * y;
	}

	double div(double x, double y) override
	{
		return x / y;
	}
};

/**
* "Proxy Object"
*/
class MathProxy : public IMath
{
public:
	MathProxy()
		: pMath(std::make_shared<Math>())
	{
		;
	}

	virtual ~MathProxy()
	{
		;
	}

	double add(double x, double y) override
	{
		return pMath->add(x, y);
	}

	double sub(double x, double y) override
	{
		return pMath->sub(x, y);
	}

	double mul(double x, double y) override
	{
		return pMath->mul(x, y);
	}

	double div(double x, double y) override
	{
		return pMath->div(x, y);
	}

private:
	std::shared_ptr<IMath> pMath;
};

int main()
{
	// Create math proxy
	std::shared_ptr<IMath> proxy(std::make_shared<MathProxy>());

	// Do the math
	std::cout << "4 + 2 = " << proxy->add(4, 2) << std::endl;
	std::cout << "4 - 2 = " << proxy->sub(4, 2) << std::endl;
	std::cout << "4 * 2 = " << proxy->mul(4, 2) << std::endl;
	std::cout << "4 / 2 = " << proxy->div(4, 2) << std::endl;

	return 0;
}