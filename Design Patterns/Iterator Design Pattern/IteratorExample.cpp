// IteratorExample.cpp

// Pattern Description:
// The Iterator pattern is a design pattern that allows clients to traverse a collection of objects,
// such as a list or an array, without having to know the underlying representation of the collection.
// It provides a way to access the elements of an aggregate object sequentially without exposing its underlying representation.
//
// The Iterator pattern defines an interface for iterators that includes methods such as first(), next(), and is_done().
// The collection class, or aggregate, typically has a method that returns an iterator, such as create_iterator().
// Clients use the iterator to traverse the collection, rather than accessing the collection directly.
// NOTE:
// The STL (Standard Template Library) already provides several classes that implement the iterator pattern
// such as `std::vector`, `std::list`, `std::set`, `std::map`, and others,
// so it's not necessary to implement the iterator pattern in most cases, you can just use the provided iterators.
// ******************************************************************************************************************************************************************************
// Example Description
// In this example, the Iterator class defines an interface for iterators.
// The Aggregate class defines an interface for collections.
// The ConcreteIterator class is an implementation of the Iterator interface that works with the Concrete Aggregate class, which is an implementation of the Aggregate interface.
// The ConcreteAggregate class is a concrete implementation of the Aggregate class that is backed by a std::vector<int>.
// The create_iterator() method of the ConcreteAggregate class returns a new ConcreteIterator object that is initialized with a pointer to the ConcreteAggregate object.
// Clients can use the Iterator interface to traverse the elements of a ConcreteAggregate object without having to know the underlying representation of the collection.
// ******************************************************************************************************************************************************************************

#include <iostream>
#include <vector>

class Iterator {
public:
    virtual ~Iterator() {}
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool is_done() const = 0;
    virtual int current() const = 0;
};

class Aggregate {
public:
    virtual ~Aggregate() {}
    virtual std::unique_ptr<Iterator> Create_iterator() = 0;
    virtual int size() const = 0;
    virtual int operator[](int index) const = 0;
};

class ConcreteIterator : public Iterator {
    Aggregate* aggregate_;
    int current_;
public:
    ConcreteIterator(Aggregate* aggregate) : aggregate_(aggregate), current_(0) {}
    void first() override { current_ = 0; }
    void next() override { current_++; }
    bool is_done() const override { return current_ == aggregate_->size(); }
    int current() const override { return (*aggregate_)[current_]; }
};

class ConcreteAggregate : public Aggregate {
    std::vector<int> data_;
public:
    ConcreteAggregate(const std::vector<int>& data) : data_(data) {}
    std::unique_ptr<Iterator> Create_iterator() override { return std::make_unique<ConcreteIterator>(this); }
    int size() const override { return data_.size(); }
    int operator[](int index) const override { return data_[index]; }
    auto begin() const { return data_.begin(); }
    auto end() const { return data_.end(); }
};

int main()
{
    std::vector<int> data = { 1, 2, 3, 4, 5 };
    ConcreteAggregate aggregate(data);
    auto iterator = aggregate.Create_iterator();

    std::cout << "Traversing the aggregate using the iterator:" << std::endl;

    for (iterator->first(); !iterator->is_done(); iterator->next())
    {
        std::cout << iterator->current() << " ";
    }

    std::cout << std::endl;
    std::cout << "Traversing the aggregate using range-based for loop:" << std::endl;

    for (auto& i : aggregate)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;
    return 0;
}