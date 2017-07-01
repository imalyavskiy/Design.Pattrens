#include <iostream>
#include <string>

class Singleton
{
	Singleton(const Singleton& root) = delete;
	Singleton& operator=(const Singleton&) = delete;

public:
	static const Singleton& Instance()
	{
		static Singleton theSingleInstance;
		return theSingleInstance;
	}

private:
	Singleton() {}
};

void main()
{
	const Singleton* pSingleton1 = &Singleton::Instance();
	const Singleton* pSingleton2 = &Singleton::Instance();
	
	bool flag = pSingleton2 == pSingleton1;
	
	return;
}