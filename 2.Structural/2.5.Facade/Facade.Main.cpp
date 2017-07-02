#include <iostream>
#include <string>
#include <sstream>
#include <memory>

/** Абстрактный музыкант - не является обязательной составляющей паттерна, введен для упрощения кода */
class Musician 
{

	const std::string name_;

public:
	Musician(std::string name) 
		: name_(name)
	{
		;
	}

	virtual ~Musician() 
	{

	}

protected:
	void output(std::string text) const 
	{
		std::cout << name_ << " " << text << "." << std::endl;
	}
};

/** Конкретные музыканты */
class Vocalist : public Musician
{

public:
	Vocalist(const std::string& name) : Musician(name) {}

	void singCouplet(const int coupletNumber) 
	{
		std::stringstream sstr;
		sstr << "sings a verse #" << coupletNumber;
		output(sstr.str());
	}

	void singChorus() 
	{
		output("sings a refrain");
	}
};

class Guitarist : public Musician 
{

public:
	Guitarist(const char* name) : Musician(name) {}

	void playCoolOpening()
	{
		output("starts with an awesome intro");
	}

	void playCoolRiffs() 
	{
		output("plays a cool riffs");
	}

	void playAnotherCoolRiffs() 
	{
		output("plays other cool riffs");
	}

	void playIncrediblyCoolSolo()
	{
		output("burns an incredible solo");
	}

	void playFinalAccord()
	{
		output("ends the song with a forceful chord");
	}
};

class Bassist : public Musician {

public:
	Bassist(const char* name) : Musician(name) {}

	void followTheDrums() 
	{
		output("follows the drums");
	}

	void changeRhythm(const char* type) 
	{
		std::stringstream sstr;
		sstr << "switches to the rythm of a " << type;
		output(sstr.str());
	}

	void stopPlaying() 
	{
		output("stops playing");
	}
};

class Drummer : public Musician {

public:
	Drummer(const char* name) : Musician(name) {}

	void startPlaying() 
	{
		output("starts playing");
	}

	void stopPlaying() 
	{
		output("stops playing");
	}
};

/** Фасад, в данном случае - знаменитая рок-группа */
class BlackSabbath {
private:
	std::shared_ptr<Vocalist>	vocal;
	std::shared_ptr<Guitarist>	guitar;
	std::shared_ptr<Bassist>	bass;
	std::shared_ptr<Drummer>	drums;

public:
	BlackSabbath() 
	{
		vocal.reset(new Vocalist("Ozzy Osbourne"));
		guitar.reset(new Guitarist("Tony Iommi"));
		bass.reset(new Bassist("Geezer Butler"));
		drums.reset(new Drummer("Bill Ward"));
	}

	void playCoolSong() 
	{
		guitar->playCoolOpening();
		drums->startPlaying();
		bass->followTheDrums();
		guitar->playCoolRiffs();
		vocal->singCouplet(1);
		bass->changeRhythm("refrain");
		guitar->playAnotherCoolRiffs();
		vocal->singChorus();
		bass->changeRhythm("verse");
		guitar->playCoolRiffs();
		vocal->singCouplet(2);
		bass->changeRhythm("refrain");
		guitar->playAnotherCoolRiffs();
		vocal->singChorus();
		bass->changeRhythm("verse");
		guitar->playIncrediblyCoolSolo();
		guitar->playCoolRiffs();
		vocal->singCouplet(3);
		bass->changeRhythm("refrain");
		guitar->playAnotherCoolRiffs();
		vocal->singChorus();
		bass->changeRhythm("verse");
		guitar->playCoolRiffs();
		bass->stopPlaying();
		drums->stopPlaying();
		guitar->playFinalAccord();
	}
};

int main() 
{
	std::cout << "Performance:" << std::endl;
	std::shared_ptr<BlackSabbath> band(new BlackSabbath());

	band->playCoolSong();
	return 0;
}

/**
* Performance:
* Tony Iommi starts with an awesome intro.
* Bill Ward starts playing.
* Geezer Butler follows the drums.
* Tony Iommi plays a cool riffs.
* Ozzy Osbourne sings a verse #1.
* Geezer Butler switches to the rythm of a refrain.
* Tony Iommi plays other cool riffs.
* Ozzy Osbourne sings a refrain.
* Geezer Butler switches to the rythm of a verse.
* Tony Iommi plays a cool riffs.
* Ozzy Osbourne sings a verse #2.
* Geezer Butler switches to the rythm of a refrain.
* Tony Iommi plays other cool riffs.
* Ozzy Osbourne sings a refrain.
* Geezer Butler switches to the rythm of a verse.
* Tony Iommi burns an incredible solo.
* Tony Iommi plays a cool riffs.
* Ozzy Osbourne sings a verse #3.
* Geezer Butler switches to the rythm of a refrain.
* Tony Iommi plays other cool riffs.
* Ozzy Osbourne sings a refrain.
* Geezer Butler switches to the rythm of a verse.
* Tony Iommi plays a cool riffs.
* Geezer Butler stops playing.
* Bill Ward stops playing.
* Tony Iommi ends the song with a forceful chord.
*/
