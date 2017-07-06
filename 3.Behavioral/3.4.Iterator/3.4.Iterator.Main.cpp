#include <iostream>
#include <memory>
#include <string>

/*
sample code in C++
This structural code demonstrates the Iterator pattern which provides for a way to traverse (iterate) over a collection of items without detailing the underlying structure of the collection.
*/

// Iterator pattern -- Structural example

/// The 'Aggregate' abstract class
class Aggregate
{
public:
    virtual Iterator& CreateIterator() = 0;
	virtual int size() = 0;
};

/// The 'ConcreteAggregate' class
class ConcreteAggregate : public Aggregate
{
    private readonly ArrayList _items = new ArrayList();

    public override Iterator CreateIterator()
    {
        return new ConcreteIterator(this);
    }

    // Gets item count
    public override int Count
    {
        get { return _items.Count; }
        protected set { }
    }

    // Indexer
    public override object this[int index]
    {
        get { return _items[index]; }
        set { _items.Insert(index, value); }
    }
};

/// The 'Iterator' abstract class
class Iterator
{
public:
    virtual Iterator& First() = 0;
    virtual Iterator& Next() = 0;
    virtual bool	  IsDone() = 0;
    virtual Iterator& CurrentItem() = 0;
};

/// The 'ConcreteIterator' class
class ConcreteIterator : public Iterator
{
private :
		const Aggregate* _aggregate;
		int _current;

public:
    // Constructor
	ConcreteIterator(Aggregate* aggregate)
        : _aggregate(aggregate)
    {
    }

    // Gets first iteration item
    Iterator& First() override
    {
        return _aggregate[0];
    }

    // Gets next iteration item
    object Next() override
    {
        object ret = null;

        _current++;

        if (_current < _aggregate.Count)
        {
            ret = _aggregate[_current];
        }

        return ret;
    }

    // Gets current iteration item
    public override object CurrentItem()
    {
        return _aggregate[_current];
    }

    // Gets whether iterations are complete
    public override bool IsDone()
    {
        return _current >= _aggregate.Count;
    }
};

/// Entry point into console application.
void main()
{
    ConcreteAggregate* a = new ConcreteAggregate();
    a[0] = "Item A";
    a[1] = "Item B";
    a[2] = "Item C";
    a[3] = "Item D";

    // Create Iterator and provide aggregate
    ConcreteIterator i = new ConcreteIterator(a);

    std::cout << "Iterating over collection:" << std::endl;

    object item = i.First();
    while (!i.IsDone())
    {
        Console.WriteLine(item);
        item = i.Next();
    }

    // Wait for user
    Console.ReadKey();
}

/*
Output
Iterating over collection:
Item A
Item B
Item C
Item D
*/