// FactoryMethodExample.cpp

// Pattern Description:
// The Factory Method Pattern defines an interface for creating an object, but lets subclasses decide which class to instantiate.
// Factory Method lets a class defer instantiation to subclasses.

// Example Description:
// An example of the Factory Method pattern would be a factory class that creates objects of a specific class, such as a shape, based on input from the client.
// Here is an example of a simple shape factory:

// In this example, the ShapeFactory class has a static method createShape()
// that takes a string as an input and returns an object of the corresponding class (Circle or Square).
// The main() function creates two shapes, one of type "circle" and one of type "square" using the factory method and then calls their draw() method.
// This pattern is useful when a class can't anticipate the type of objects it must create,
// and when a class wants its subclasses to specify the objects it creates.

#include <iostream>

// Abstract base class for different types of shape
class Shape
{
public:
    virtual void Draw() = 0;
};

// Concrete implementation for drawing a Circle
class Circle : public Shape
{
public:
    void Draw()
    {
        std::cout << "Drawing a Circle" << std::endl;
    }
};

// Concrete implementation for drawing a Square
class Square : public Shape
{
public:
    void Draw()
    {
        std::cout << "Drawing a Square" << std::endl;
    }
};

class ShapeFactory
{

public:
    // Factory method to create a shape object based on the given type
    static std::unique_ptr<Shape> CreateShape(std::string type)
    {
        if (type == "Circle")
        {
            return std::make_unique<Circle>();
        }
        else if (type == "Square")
        {
            return std::make_unique<Square>();
        }
        else
        {
            return nullptr;
        }
    }
};

int main()
{
    // Create a Circle shape and call its draw method
    auto shape1 = ShapeFactory::CreateShape("circle");
    shape1->Draw();
    // Create a Square shape and call its draw method
    auto shape2 = ShapeFactory::CreateShape("square");
    shape2->Draw();

    return 0;
}
