#include <iostream>
#include <list>
#include <algorithm>
#include <memory>

class IText 
{
public:
	typedef std::shared_ptr<IText> TextPtr;

	virtual void draw() = 0;

	virtual void add(const TextPtr&) 
	{
		throw std::runtime_error("IText: Can't add to a leaf");
	}

	virtual void remove(const TextPtr&) 
	{
		throw std::runtime_error("IText: Can't remove from a leaf");
	}
};

class CompositeText : public IText
{
public:
	void add(const TextPtr& pText) override
	{
		children_.push_back(pText);
	}

	void remove(const TextPtr& pText) override
	{
		children_.remove(pText);
	}

	void replace(const TextPtr& oldValue, const TextPtr& newValue) 
	{
		std::replace(children_.begin(), children_.end(), oldValue, newValue);
	}

	virtual void draw() override
	{
		for (TextPtr& pText : children_) 
		{
			pText->draw();
		}
	}

private:
	std::list<TextPtr> children_;
};

class Letter : public IText 
{
public:
	Letter(char c) 
		: c_(c) 
	{
		;
	}

	virtual void draw() override
	{
		std::putchar(c_);
	}

private:
	char c_;
};


int main() 
{

	CompositeText sentence;

	IText::TextPtr lSpace(new Letter(' '));
	IText::TextPtr lExcl(new Letter('!'));
	IText::TextPtr lComma(new Letter(','));
	IText::TextPtr lNewLine(new Letter('\n'));
	IText::TextPtr lH(new Letter('H')); // letter 'H'
	IText::TextPtr le(new Letter('e')); // letter 'e'
	IText::TextPtr ll(new Letter('l')); // letter 'l'
	IText::TextPtr lo(new Letter('o')); // letter 'o'
	IText::TextPtr lW(new Letter('W')); // letter 'W'
	IText::TextPtr lr(new Letter('r')); // letter 'r'
	IText::TextPtr ld(new Letter('d')); // letter 'd'
	IText::TextPtr li(new Letter('i')); // letter 'i'

	IText::TextPtr wHello(new CompositeText);
	wHello->add(lH);
	wHello->add(le);
	wHello->add(ll);
	wHello->add(ll);
	wHello->add(lo);

	IText::TextPtr wWorld(new CompositeText); // word "World"
	wWorld->add(lW);
	wWorld->add(lo);
	wWorld->add(lr);
	wWorld->add(ll);
	wWorld->add(ld);

	sentence.add(wHello);
	sentence.add(lComma);
	sentence.add(lSpace);
	sentence.add(wWorld);
	sentence.add(lExcl);
	sentence.add(lNewLine);

	sentence.draw();  // prints "Hello, World!\n"

	IText::TextPtr wHi(new CompositeText); // word "Hi"
	wHi->add(lH);
	wHi->add(li);

	sentence.replace(wHello, wHi);
	sentence.draw();  // prints "Hi, World!\n"

	sentence.remove(wWorld);
	sentence.remove(lSpace);
	sentence.remove(lComma);
	sentence.draw();  // prints "Hi!\n"

	return 0;
}