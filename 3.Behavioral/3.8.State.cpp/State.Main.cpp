#include <iostream>
#include <memory>
#include <string>
#include <random>

#define interface struct

interface IAutomataState
{
	typedef std::shared_ptr<IAutomataState> sptr;

    virtual std::string GotApplication() = 0;
    virtual std::string CheckApplication() = 0;
    virtual std::string RentApartment() = 0;
    virtual std::string DispenseKeys() = 0;
};

interface IAutomata : std::enable_shared_from_this<IAutomata>
{
	typedef std::shared_ptr<IAutomata>	sptr;
	typedef std::weak_ptr<IAutomata>	wptr;

    virtual void					GotApplication() = 0;
    virtual void					CheckApplication() = 0;
    virtual void					RentApartment() = 0;
    virtual void					SetState(IAutomataState::sptr& s) = 0;
	virtual IAutomataState::sptr	GetWaitingState() = 0;
	virtual IAutomataState::sptr	GetGotApplicationState() = 0;
	virtual IAutomataState::sptr	GetApartmentRentedState() = 0;
	virtual IAutomataState::sptr	GetFullyRentedState() = 0;

	int32_t getCount() const { return Count; };
	void setCount(int32_t c) { Count = c; }

protected:
	int32_t Count = 0;
};

class WaitingState : public IAutomataState
{
private:
	const std::string _response = "You have to submit an application.";

    IAutomata::wptr _automata;

public:
	WaitingState(IAutomata::sptr automata)
    {
        _automata = automata;
    }

    std::string GotApplication()
    {
		auto automata = _automata.lock();
		if (!automata)
			return std::string();

        automata->SetState(automata->GetGotApplicationState());
        return "Thanks for the application.";
    }

    std::string CheckApplication() { return _response; }

    std::string RentApartment()    { return _response; }

    std::string DispenseKeys()     { return _response; }
};

class GotApplicationState : public IAutomataState
{
private:
	const std::string _response = "You must have your application checked.";
        
	IAutomata::wptr _automata;
 	
public:
	GotApplicationState(IAutomata::sptr automata)
        : _automata(automata)
    {
    }

    std::string GotApplication() { return "We already got your application."; }

    std::string CheckApplication()
    {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 1000);

		auto automata = _automata.lock();
		if (!automata)
			return std::string();

		int yesNo = dis(gen) % 10;

        if (yesNo > 4 && automata->getCount() > 0)
        {
            automata->SetState(automata->GetApartmentRentedState());
            return "Congratulations, you were approved.";
        }
        else
        {
            automata->SetState(automata->GetWaitingState());
            return "Sorry, you were not approved.";
        }
    }

    std::string RentApartment() { return _response; }

    std::string DispenseKeys() { return _response; }
};

class ApartmentRentedState : public IAutomataState
{
private:
	const std::string _response = "Hang on, we'ra renting you an apartmeny.";

	IAutomata::wptr _automata;

public:
	ApartmentRentedState(IAutomata::sptr automata)
    {
        _automata = automata;
    }

    std::string GotApplication()	{ return _response; }
    std::string CheckApplication()	{ return _response; }
    std::string RentApartment()
    {
		if(_automata.expired())
			return std::string();
		
		auto automata = _automata.lock();

        automata->setCount(automata->getCount() - 1);
        return "Renting you an apartment....";
    }

    std::string DispenseKeys()
    {
		if (_automata.expired())
			return std::string();
		
		auto automata = _automata.lock();

        if (automata->getCount() <= 0)
            automata->SetState(automata->GetFullyRentedState());
        else
            automata->SetState(automata->GetWaitingState());

        return "Here are your keys!";
    }
};

class FullyRentedState : public IAutomataState
{
private:
    const std::string _response = "Sorry, we're fully rented.";

	IAutomata::wptr _automata;

public:
    FullyRentedState(IAutomata::sptr automata)
    {
        _automata = automata;
    }

    std::string GotApplication()   { return _response; }
    std::string CheckApplication() { return _response; }
    std::string RentApartment()    { return _response; }
    std::string DispenseKeys()     { return _response; }
};

class Automata : public IAutomata
{
protected:
    IAutomataState::sptr _waitingState;
    IAutomataState::sptr _gotApplicationState;
    IAutomataState::sptr _apartmentRentedState;
    IAutomataState::sptr _fullyRentedState;
    IAutomataState::sptr _state;

    int32_t				 _count;

    Automata(const int32_t n)
        : _count(n)
    {
    }

	void init()
	{
		_waitingState.reset(new WaitingState(shared_from_this()));
		_gotApplicationState.reset(new GotApplicationState(shared_from_this()));
		_apartmentRentedState.reset(new ApartmentRentedState(shared_from_this()));
		_fullyRentedState.reset(new FullyRentedState(shared_from_this()));
		_state = _waitingState;
	}

public:
	static IAutomata::sptr Create(int arg)
	{
		Automata* p(new Automata(arg));
		IAutomata::sptr sp(p);
		
		p->init();

		return sp;
	}


    void GotApplication() override
    {
        std::cout << _state->GotApplication() << std::endl;
    }

    void CheckApplication()  override
    {
		std::cout << _state->CheckApplication() << std::endl;
    }

    void RentApartment()  override
    {
        std::cout << _state->RentApartment() << std::endl;
        std::cout << _state->DispenseKeys()  << std::endl;
    }

    void SetState(IAutomataState::sptr& s)  override { _state = s; }

    IAutomataState::sptr GetWaitingState()  override { return _waitingState; }
    IAutomataState::sptr GetGotApplicationState()  override { return _gotApplicationState; }
    IAutomataState::sptr GetApartmentRentedState()  override { return _apartmentRentedState; }
    IAutomataState::sptr GetFullyRentedState()  override { return _fullyRentedState; }

    int getCount() const { return Count; }
    void setCount(const int value){ _count = value; }

protected:
	int Count = 0;
};


void main()
{
	std::shared_ptr<IAutomata> automata(Automata::Create(9));
 
	automata->GotApplication();
	automata->CheckApplication();
	automata->RentApartment();
}