#include <iostream>
#include <iomanip>
#include <memory>
#include <stack>
#include <cmath>

const float pi = 3.141592653f;

inline float Degrees2Radians(float degrees)
{
	return (degrees / 180.0f) * pi;
}

struct vector2D
{
	vector2D(const float _x, const float _y) : x(_x), y(_y) { };
	vector2D(const vector2D& other) : x(other.x), y(other.y) {};

	const vector2D& operator=(const vector2D& other)
	{
		x = other.x;
		y = other.y;

		std::cout << "[" 
			<< ((x >= 0) ? " " : "") << std::fixed << x 
			<< "," 
			<< ((y >= 0) ? " " : "") << std::fixed << y
			<< "]" << std::endl;

		return (*this);
	}

private:
	float x;
	float y;
};

struct point2D : vector2D
{
	point2D(const float _x = 0, const float _y = 0) : vector2D(_x ,_y) {};
	point2D(const point2D& other) : vector2D(other) {};

	const point2D& operator=(const point2D& other)
	{
		vector2D::operator=(other);
		return (*this);
	}

	void Move(const vector2D& direction)
	{
		vector2D::operator=(direction);
	}
};

struct IMemento
{
	typedef std::shared_ptr<IMemento> ptr;
	
	virtual ~IMemento() {};
	virtual bool Restore() = 0;
};

class Originator : public std::enable_shared_from_this<Originator>
{
	friend class Memento;
public:
	typedef std::shared_ptr<Originator> sptr;
	typedef std::weak_ptr<Originator>	wptr;

protected:
	
	struct State
	{
		State() { };

		State& operator=(const State& arg) { point = arg.point; return (*this); }

		point2D point;
	};

	class Memento : public IMemento
	{
	protected:
		Originator::wptr originator;
		State state;

	public:
		Memento(const State& arg, Originator::sptr& o)
			: originator(o)
			, state(arg)
		{};

		bool Restore() override
		{
			auto ptr = originator.lock();
			if (ptr)
			{
				ptr->state = state;
				return true;
			}

			return false;
		}
	};

protected:
	State state;

public:

	IMemento::ptr GetState()
	{
		return IMemento::ptr(new Memento(state, shared_from_this()));
	}

	void Move(const vector2D& direction = vector2D(0.0, 0.0))
	{
		state.point.Move(direction);
	}
};

class CareTaker
{
protected:
	Originator::wptr originator;
	std::stack<IMemento::ptr> changes;

public:
	typedef std::shared_ptr<CareTaker> sptr;

	CareTaker(Originator::sptr& o) : originator(o) { };

	~CareTaker() 
	{ 
		while (!changes.empty() && changes.top()->Restore())
			changes.pop();
	}

	bool TakeState()
	{
		Originator::sptr sp = originator.lock();
		if(sp)
		{
			changes.push(sp->GetState());
			return true;
		}

		return false;
	}

	bool RestoreState()
	{
		if(!changes.empty() && changes.top()->Restore())
		{
			changes.pop();
			return true;
		}

		return false;
	}
};

void main()
{
	Originator::sptr originator(new Originator());
	CareTaker::sptr caretacker(std::make_shared<CareTaker>(originator));
	
	// degree
	std::cout << "Initial position is: " << std::endl;
	originator->Move(vector2D(0.0, 0.0));
	std::cout << "----------------------" << std::endl;

	const float angle_step = 30.0;
	for(float angle = 0.0; angle <= 360.0; angle += angle_step)
	{
		originator->Move(vector2D(std::cosf(Degrees2Radians(angle)), std::sinf(Degrees2Radians(angle))));
		caretacker->TakeState();
	}

	std::cout << "----------------------" << std::endl;

	// Here the CareTaker instance will push back states as F.I.L.O.
	caretacker.reset();

	std::cout << "----------------------" << std::endl;

	originator.reset();
}