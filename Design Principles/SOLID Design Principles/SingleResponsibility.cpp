// Example of the single responsibility SOLID design principle


#include <iostream>
#include <cstdio>
#include <string>
#include<vector>
#include<fstream>

using namespace std;

struct Journal
{
    string title;
    vector<string> entries;

    Journal(const string& title) : title(title) {}

    void AddEntry(const string& entry)
    {
        static int count = 1;
        entries.push_back(entry);
    }

    // We dont want a save function here, breaks single responsibility
    // Need to add a new class "Persistence Manager" for load/save responsibility
};

struct PersistenceManager
{
    static void Save(const Journal& j, const string& filename)
    {
        ofstream ofs(filename);
        for (auto& e : j.entries)
        {
            ofs << e << endl;
        }
    }

    static void Load() {}
};

int main()
{
    Journal journal("My Journal");
    journal.AddEntry("I ate a bug.");
    journal.AddEntry("I cried today.");
    PersistenceManager pm;
    pm.Save(journal, "MyJournal.txt");
    return 0;
}
