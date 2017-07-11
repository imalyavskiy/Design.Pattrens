#include <iostream>
#include <string>
#include <list>
#include <memory>

class Foo;
class Bar;
class Baz;

class Visitor {
public:
	virtual void visit(Foo &ref) = 0;
	virtual void visit(Bar &ref) = 0;
	virtual void visit(Baz &ref) = 0;

	virtual ~Visitor() = default;
};

class Element {
public:
	typedef std::shared_ptr<Element> ptr;

	virtual void accept(Visitor &v) = 0;

	virtual ~Element() = default;
};

class Foo : public Element {
public:
	void accept(Visitor &v) override {
		v.visit(*this);
	}
};

class Bar : public Element {
public:
	void accept(Visitor &v) override {
		v.visit(*this);
	}
};

class Baz : public Element {
public:
	void accept(Visitor &v) override {
		v.visit(*this);
	}
};

class GetType : public Visitor {
public:
	std::string value;

public:
	void visit(Foo &ref) override {
		value = "Foo";
	}
	void visit(Bar &ref) override {
		value = "Bar";
	}
	void visit(Baz &ref) override {
		value = "Baz";
	}
};

int main() {

	std::list<Element::ptr> elements = {
		Element::ptr(new Foo),
		Element::ptr(new Bar),
		Element::ptr(new Baz)
	};

	for (auto elem : elements) {
		GetType visitor;
		elem->accept(visitor);
		std::cout << visitor.value << std::endl;
	}

	return 0;
}