// DecoratorPattern.cpp

// Pattern Description:
// The Decorator Pattern attaches additional responsibilities to an object dynamically.
// Decorators provide a flexible alternative to subclassing for extending functionality.
// The Decorator design pattern is a design pattern that allows behavior to be added to an individual object, either statically or dynamically,
// without affecting the behavior of other objects from the same class.
// It is a structural pattern that involves a set of decorator classes that are used to wrap concrete components.

// Example Description:
// In this example, Component is an abstract class that defines the interface for objects that can have responsibilities added to them dynamically.
// ConcreteComponent is a class that implements the basic functionality of the Component class,
// and Decorator and ConcreteDecoratorA and ConcreteDecoratorB are classes that represent specific types of decorators.
// Each decorator class wraps a Component object and adds its own behavior to it.

#include <iostream>

// The Component interface defines operations that can be
// altered by decorators.
class Component {
public:
    virtual ~Component() = default;
    virtual void Operation() const = 0;
};

// Concrete components provide default implementations of
// the operations. There might be several variations of these
// classes.
class ConcreteComponent : public Component {
public:
    void Operation() const override {
        std::cout << "ConcreteComponent" << std::endl;
    }
};

// The Decorator class follows the same interface as the other
// components. The primary purpose of this class is to define
// the wrapping interface for all concrete decorators. The
// default implementation of the wrapping code might include
// a field for storing a wrapped component and the means to
// initialize it.
class Decorator : public Component {
protected:
    Component* component_;

public:
    Decorator(Component* component) : component_(component) {}

    void Operation() const override {
        // ... You can add some code before or after calling the
        // operation on a wrapped component.
        if (component_) {
            component_->Operation();
        }
    }
};

// Concrete decorators override some operations of the
// base component or add new behaviors.
class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(Component* component) : Decorator(component) {}

    void Operation() const override {
        // ... You can add some code before or after calling the
        // operation on a wrapped component.
        std::cout << "ConcreteDecoratorA ";
        Decorator::Operation();
    }
};

class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(Component* component) : Decorator(component) {}

    void Operation() const override {
        // ... You can add some code before or after calling the
        // operation on a wrapped component.
        std::cout << "ConcreteDecoratorB ";
        Decorator::Operation();
    }
};

int main() {
    // The client code can work with all objects using the Component
    // interface. This way it can stay independent of the concrete
    // classes of components it works with.
    ConcreteComponent c;
    ConcreteDecoratorA d1(&c);
    ConcreteDecoratorB d2(&d1);
    d2.Operation();
    return 0;
}
