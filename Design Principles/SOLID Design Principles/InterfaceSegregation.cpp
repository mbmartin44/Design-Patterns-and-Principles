// Interface Segregation Principle
// Description: Don't cause implementers to have to implement complex interfaces.

#include <iostream>
#include <cstdio>
#include <string>
#include<vector>
#include<fstream>

using namespace std;

struct Document;

// Breaking the Interface Segregation Principle:
// struct IMachine
// {
//     virtual void Print(Document& doc) = 0;
//     virtual void Scan(Document& doc) = 0;
//     virtual void Fax(Document& doc) = 0;
// };
//
// struct MultiFuncPrinter : IMachine
// {
//     void Print(Document& doc) override{}
//     void Scan(Document& doc) override{}
//     void Fax(Document& doc) override{}
// };
//
// struct Scanner : IMachine
// {
//     void Print(Document& doc) override {} // Problem here: Giving a print API to clients which is invalid.
//     void Scan(Document& doc) override {}
//     void Fax(Document& doc) override {}
// };

struct IPrinter
{
    virtual void Print(Document& doc) = 0;
};

struct IScanner
{
    virtual void Scan(Document& doc) = 0;
};

struct IFax
{
    virtual void Fax(Document& doc) = 0;
};

struct Printer : IPrinter
{
    void Print(Document& doc) override {}
};

struct Scanner : IScanner
{
    void Scan(Document& doc) override {}
};

// This is how you would extend/combine the interfaces to make a more complex interface
struct IMachine : IPrinter, IScanner {};

struct Machine : IMachine
{
    IPrinter& printer;
    IScanner& scanner;

    Machine(IPrinter& printer, IScanner& scanner) : printer(printer), scanner(scanner) {}

    void Print(Document& doc) override
    {
        printer.Print(doc);
    }

    void Scan(Document& doc) override
    {
        scanner.Scan(doc);
    }
};

int main()
{
    return 0;
}
