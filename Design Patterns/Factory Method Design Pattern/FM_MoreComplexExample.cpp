// FactoryMethodMoreComplexExample.cpp

// In this example, the Product class is the abstract base class that defines the interface for the products that can be created by the factory method.
// The ConcreteProductA and ConcreteProductB classes are concrete implementations of the Product class,
// and they provide specific functionality for their respective products.
//
// The Creator class is an abstract class that defines the factory method, which creates an instance of a Product object.
// The ConcreteCreator class is a concrete implementation of the Creator class,
// and it provides the implementation for the factory method by using a switch statement to determine the type of product to create
// and returning a unique_ptr of the corresponding concrete product.
//
// In the main function, an instance of ConcreteCreator is created and the FactoryMethod function is used to create instances of ConcreteProductA
// and ConcreteProductB, and then Use() function is called on them.
//
// By using the factory method design pattern in this way, the client code(in this case,
// the main function) can create objects of different types without needing to know the specific classes of those objects,
// making the code more flexible and easier to extend.

#include <iostream>

class Product
{
public:
    virtual ~Product() = default;
    virtual void Use() = 0;
};

class ConcreteProductA : public Product
{
public:
    void Use() override
    {
        std::cout << "Using Concrete Product A" << std::endl;
    }
};

class ConcreteProductB : public Product
{
public:
    void Use() override
    {
        std::cout << "Using Concrete Product B" << std::endl;
    }
};

enum class ProductType
{
    A,
    B
};

class Creator
{
public:
    virtual ~Creator() = default;
    virtual std::unique_ptr<Product> FactoryMethod(ProductType type) = 0;
};

class ConcreteCreator : public Creator
{
public:
    std::unique_ptr<Product> FactoryMethod(ProductType type) override
    {
        switch (type) {
        case ProductType::A:
            return std::make_unique<ConcreteProductA>();
        case ProductType::B:
            return std::make_unique<ConcreteProductB>();
        default:
            return nullptr;
        }
    }
};

int main()
{
    ConcreteCreator creator;
    auto productA = creator.FactoryMethod(ProductType::A);
    productA->Use();
    auto productB = creator.FactoryMethod(ProductType::B);
    productB->Use();
    return 0;
}
