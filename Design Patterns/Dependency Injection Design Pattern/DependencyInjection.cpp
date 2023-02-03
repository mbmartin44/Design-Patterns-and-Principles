// DependencyInjection.cpp

// Conceptual Description:
// Dependency injection is a design pattern in which an object receives its dependencies(other objects it needs to function) through its
// constructor, method, or a property setter, rather than creating them itself.
// This allows for greater flexibility and testability, as dependencies can be easily swapped out or mocked for testing.

// Example Description:
// In this example, the Car class has a dependency on an object of type Engine.Instead of creating an instance of Engine inside the Car class,
// the Car class receives an instance of Engine through its constructor.

// This allows the client code to pass in a different implementation of Engine to the Car class,
// which can be useful for testing or for using different types of engines in different scenarios.

// As you can see, the Car class can be used with different engines such as a Real Engine, Electric Engine,
// or a Test Engine.This allows us to test the Car class with different engines and it makes testing the Car class much easier.

// Also, this allows to change the behavior of the Car class without modifying the code of the Car class.

// This is just a simple example, but in a real - world application,
// Dependency Injection can make your code more flexibleand testable by allowing you to swap out different implementations of dependencies for different scenarios,
// such as testing, production, or different configurations.

#include <iostream>

class Engine
{
public:
    Engine() {}
    virtual void start() { std::cout << "Start the engine" << std::endl; }
};

class Car
{
private:
    std::unique_ptr<Engine> engine;
public:
    Car(std::unique_ptr<Engine>&& e) : engine(std::move(e)) {}
    void start() { engine->start(); }
};

class ElectricEngine : public Engine
{
public:
    ElectricEngine() {}
    void start() override { std::cout << "Start the electric engine" << std::endl; }
};

class TestEngine : public Engine
{
public:
    TestEngine() {}
    void start() override { std::cout << "Start the test engine" << std::endl; }
};

int main()
{
    // Using a real engine
    auto e = std::make_unique<Engine>();
    Car c(std::move(e));
    c.start();

    // Using an electric engine
    auto electric_engine = std::make_unique<ElectricEngine>();
    Car electric_car(std::move(electric_engine));
    electric_car.start();

    // Using a test engine
    auto test_engine = std::make_unique<TestEngine>();
    Car test_car(std::move(test_engine));
    test_car.start();
    return 0;
}