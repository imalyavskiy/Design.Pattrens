#include <iostream>
#include <memory>

class IComponent {
public:
	typedef std::shared_ptr<IComponent> ptr;

	virtual void operation() = 0;
	virtual ~IComponent() {}
};

class Component : public IComponent {
public:
	void operation() override {
		std::cout << "World!" << std::endl;
	}
};

class DecoratorOne : public IComponent {
	IComponent::ptr m_component;

public:
	DecoratorOne(IComponent* component) : m_component(component) {}

	void operation() override {
		std::cout << ", ";
		m_component->operation();
	}
};

class DecoratorTwo : public IComponent {
	IComponent::ptr m_component;

public:
	DecoratorTwo(IComponent* component) : m_component(component) {}

	void operation() override {
		std::cout << "Hello";
		m_component->operation();
	}
};

int main() {
	DecoratorTwo obj(new DecoratorOne(new Component()));
	obj.operation(); // prints "Hello, World!\n"

	return 0;
}