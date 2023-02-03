// Dependency Inversion SOLID Design Principle

// The dependency inversion principle is not really about  injection,
// its simply specifies the best way to form dependencies between different objects.

// 1. High-level modules shouldnt depend on low level modules, they should both depend on abstractions.
// 2. Abstractions should not depend on details. Details should depend on abstractions.


#include <iostream>
#include <cstdio>
#include <string>
#include<vector>
#include<fstream>
#include <tuple>

using namespace std;

enum class Relationship
{
    parent,
    child,
    sibling
};

struct Person
{
    string name;
};

struct RelationshipBrowser
{
    virtual vector<Person> FinalAllChildrenOf(const string& name) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////
// Low-level module
struct Relationships : RelationshipBrowser
{
    vector<tuple<Person, Relationship, Person>> relations;

    void AddParentAndChild(const Person& parent, const Person& child)
    {
        relations.push_back({ parent, Relationship::parent, child });
        relations.push_back({ child, Relationship::child, parent });
    }

    vector <Person> FinalAllChildrenOf(const string& name)
    {
        vector<Person> result;
        for (auto&& [first, rel, second] : relations)
        {
            if (first.name == name && rel == Relationship::parent)
            {
                result.push_back(second);
            }
        }
        return result;
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////

// High-level Module
// We need to add an abstraction instead of depending on the Relationships low-level module.
struct Research //high-level module
{
    Research(RelationshipBrowser& browser)
    {
        for (auto& child : browser.FinalAllChildrenOf("John"))
        {
            cout << "John has a child called " << child.name << endl;
        }
    }

    // Dependency on low-level module breaks dependency inversion principle
    // Research(Relationships& relationships)
    // {
    //     auto& relations = relationships.relations;
    //     for (auto&& [first, rel, second] : relations)
    //     {
    //         if(first.name == "John" && rel == Relationship::parent)
    //             cout << "John has a child called " << second.name << endl;
    //     }
    // }

    // Using the RelationshipBrowser, we can re-write the Research implementation

};
///////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    Person parent{ "John" };
    Person child1{ "Chris" };
    Person child2{ "Matt" };

    Relationships relationships;
    relationships.AddParentAndChild(parent, child1);
    relationships.AddParentAndChild(parent, child2);

    Research _(relationships);

    return 0;
}
