#include <map>
#include <iostream>
#include <memory>

// "Flyweight"
class Character
{
public:
	virtual ~Character() {}
	virtual void display() const = 0;

protected:
	char mSymbol;
	int  mWidth;
	int  mHeight;
	int  mAscent;
	int  mDescent;
	int  mPointSize;
};

// "ConcreteFlyweight"
class ConcreteCharacter 
	: public Character
{
public:
	// Constructor
	ConcreteCharacter(char aSymbol, int aPointSize)
	{
		mSymbol		= aSymbol;
		mWidth		= 120;
		mHeight		= 100;
		mAscent		= 70;
		mDescent	= 0;
		mPointSize	= aPointSize;
	}

	// from Character
	void display() const override{
		std::cout << mSymbol << " ( PointSize " << mPointSize << " )\n";
	}
};

// "FlyweightFactory"
template < int POINT_SIZE = 10 >
class CharacterFactory
{
public:
	const Character& getCharacter(char aKey)
	{
		// Uses "lazy initialization" - эт чо?
		const auto it = mCharacters.find(aKey);
		if (mCharacters.end() == it) {
			auto character(std::make_shared<ConcreteCharacter>(aKey, POINT_SIZE));
			mCharacters.insert(Characters::value_type(aKey, character));
			return *(character);
		}
		else {
			return *(it->second);
		}
	}

	virtual ~CharacterFactory() {
		for (auto it = mCharacters.begin(); it != mCharacters.end(); ++it)
			it->second.reset();
	}

private:
	typedef std::map < char, std::shared_ptr<Character> > Characters;
	Characters mCharacters;
};

int main() {
	std::string document = "AAZZBBZB";

	CharacterFactory<12> characterFactory;

	for (std::string::const_iterator it = document.begin(); it != document.end(); ++it) {
		const Character& character = characterFactory.getCharacter(*it);
		character.display();
	}
	return 0;
}