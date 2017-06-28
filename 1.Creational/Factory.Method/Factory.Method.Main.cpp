#include <cstdio>
#include <memory>

struct Weapon {
	virtual void attack() = 0;
	
	virtual ~Weapon() 
	{}
};

struct Sword : Weapon {
	virtual void attack() override 
	{ std::puts("Slash!"); }
};

struct Bow : Weapon {
	virtual void attack() override 
	{ std::puts("Pew!"); }
};

struct Hero {
	virtual std::shared_ptr<Weapon> getWeapon() = 0; // Factory method
	virtual ~Hero() 
	{}
};

struct Knight : Hero {
	virtual std::shared_ptr<Weapon> getWeapon() override
	{ return std::shared_ptr<Weapon>(new Sword()); }
};

struct Rogue : Hero {
	virtual std::shared_ptr<Weapon> getWeapon() override
	{ return std::shared_ptr<Weapon>(new Bow()); }
};

int main() {
	auto elf(std::make_shared<Rogue>());
	auto human(std::make_shared<Knight>());
	
	std::shared_ptr<Weapon> wpn;
	
	wpn = elf->getWeapon();
	wpn->attack();

	wpn = human->getWeapon();
	wpn->attack();

	return 0;
}