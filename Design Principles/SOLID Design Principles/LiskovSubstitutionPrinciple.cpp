// Liskov Substitution Principle

// Description of Principle:
// Subtypes should be immediately substitutable for their base types.

// Explanation of File:
// This file demonstrates a violation of the principle.


#include <iostream>
#include <cstdio>
#include <string>
#include<vector>
#include<fstream>

using namespace std;

class Rectangle
{
protected:
    int width, height;
public:
    Rectangle(int width, int height) : width(width), height(height) {}

    virtual void SetWidth(int width)
    {
        Rectangle::width = width;
    }

    virtual void SetHeight(int height)
    {
        Rectangle::height = height;
    }

    int GetHeight() const noexcept
    {
        return height;
    }

    int GetWidth() const noexcept
    {
        return width;
    }

    int area() const noexcept { return width * height; }
};

// Square created a violation.
class Square : public Rectangle
{
public:
    Square(int size) : Rectangle(size, size) {}

    void SetHeight(int height) override
    {
        this->width = this->height = height;
    }

    void SetWidth(int width) override
    {
        this->width = this->height = width;
    }
};

void Process(Rectangle& r)
{
    int w = r.GetWidth();
    r.SetHeight(10);
    cout << "Expected Area: " << (w * 10) << ", Got: " << r.area() << endl;
}

int main()
{
    Rectangle r{ 10, 20 };
    Process(r);

    // This breaks the Liskov Sub principle.
    // Here, square which is derived from rectangle is not directly substitutable for rectangle.
    Square sq{ 5 };
    Process(sq);

    return 0;
}

// Note: A solution to this violation might be a factory class (RectangleFactory)