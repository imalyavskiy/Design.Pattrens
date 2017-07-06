#include <iostream>
#include <memory>
#include <string>

/*
sample code in C++
This structural code demonstrates the Iterator pattern which provides for a way to traverse (iterate) over a collection of items without detailing the underlying structure of the collection.
*/

// Iterator pattern -- Structural example


/// The 'Iterator' abstract class

/// Entry point into console application.
class Container
{
	friend class Iterator;
protected:
	const size_t _size = 0;
	std::string* _pdata = nullptr;

public: 
	Container()
		: _size(4)
	{
		_pdata = new std::string[_size];

		_pdata[0] = "Item A";
		_pdata[1] = "Item B";
		_pdata[2] = "Item C";
		_pdata[3] = "Item D";
	}

	~Container()
	{
		delete[] _pdata;
		_pdata = nullptr;
	}

	size_t size() const { return _size; }
};

class Iterator
{
protected:
	Container* _container;
	size_t _index = 0;

public:
	Iterator(const Iterator& other)
		: _container(other._container)
		, _index(other._index)
	{

	}
	
	Iterator(Container& container)
		: _container(&container)
	{
		;
	}

	~Iterator()
	{
		;
	}

	Iterator& operator=(Iterator& other)
	{
		_container = other._container;
		_index = other._index;

		return *this;
	}

	void Reset()
	{
		_index = 0;
	}

	operator bool()
	{
		return _index < _container->size();
	}

	bool Move()
	{
		++_index;
		return operator bool();
	}

	std::string& value()
	{
		return _container->_pdata[_index];
	}
};

void main()
{
    Container container;

    // Create Iterator and provide aggregate
    Iterator i(container);

    std::cout << "Iterating over collection:" << std::endl;

	for(Iterator i(container);i;i.Move())
		std::cout << i.value() << std::endl;
}

/*
Iterating over collection:
Item A
Item B
Item C
Item D
*/