#include <iostream>
#include "Template.h"
using namespace std;

int main()
{
    Container<int>* c = new tree<int>();

    for(int i = 1; i < 10; i++)
        c->insert(i*i);
   // c->print();
    if(!c->exists(111))
        cout << "Search for value 111: not found" << endl;

    delete c;
    return 0;
}