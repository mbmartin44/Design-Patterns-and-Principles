// This is a demonstration of the Open/Closed SOLID design principle

// This principle states that your system should be open to extension,
// but closed to modificiation.



#include <iostream>
#include <cstdio>
#include <string>
#include<vector>
#include<fstream>

using namespace std;

enum class Color { red, green, blue };
enum class Size { small, medium, large };

struct Product
{
    string name;
    Color color;
    Size size;
};

struct ProductFilter_v1
{
    vector <Product*> ByColor(vector<Product*> items, Color color)
    {
        vector <Product*> result;
        for (auto& i : items)
        {
            if (i->color == color)
            {
                result.push_back(i);
            }
        }
        return result;
    }

    // This implementation requires copy/paste as new filters are added.
    // Solution DOES NOT SCALE.

    // This breaks the open/closed principle, because what we are doing
    // by adding new filtering functions is modification.
};


template <typename T>
struct ISpecification
{
    virtual bool IsSatisfied(T* item) = 0;
};

template <typename T>
struct IFilter
{
    virtual vector<T*> Filter(vector<T*> items, ISpecification<T>& spec) = 0;
};

struct BetterFilter : IFilter<Product>
{
    vector<Product*> Filter(vector<Product*> items, ISpecification<Product>& spec) override
    {
        vector<Product*> result;
        for (auto& item : items)
        {
            if (spec.IsSatisfied(item))
            {
                result.push_back(item);
            }
        }
        return result;
    }
};

struct ColorSpecification : ISpecification<Product>
{
    Color color;
    ColorSpecification(Color color) : color(color) {}

    bool IsSatisfied(Product* item) override
    {
        return item->color == color;
    }

};


int main()
{
    Product apple{ "Apple", Color::green, Size::small };
    Product tree{ "Tree", Color::green, Size::large };
    Product house{ "House", Color::blue, Size::large };

    vector<Product*> items{ &apple, &tree, &house };

    BetterFilter bpf;
    ColorSpecification green(Color::green);

    for (auto& item : bpf.Filter(items, green))
    {
        cout << item->name << " is green." << endl;
    }

    return 0;
}
