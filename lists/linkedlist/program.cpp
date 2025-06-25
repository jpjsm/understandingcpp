/* **************************************************************************
 
  program.cpp

  Testing functionality in linkedlist.
  

  Created by Juan Pablo Jofre on 2019-08-09.
  Copyright © 2019 Juan Pablo Jofre (juanpablo.jofre@live.com). All rights reserved.

   ***************************************************************************/

#include "linkedlist.h"
#include <iostream>
using namespace std;
void main()
{
    linkedlist<int> l;
    
    for (int i = 0; i < 10; i++)
    {
        l.insert(i);
    }

    l.insert_last(-1);

    l.insert_at(-1, 11);
    l.insert_at(25,-2);
    l.insert_at(1,10);

    int p;
    p = l.find(11);
    p = l.find(9);
    p = l.find(-1);
    p = l.find(-2);
    p = l.find(25);
    p = l.find(-4);

    linkedlist<int> e;
    p = e.find(5);
    
    try
    {
        e.remove();
    }
    catch(char* ex)
    {
        cout << ex << '\n';
    }
    
    int i = 0;
    try
    {
        while (true)
        {
            l.remove();
            i++;
        }      
    }
    catch(char* ex)
    {
        cout << ex << '\n';
        cout << "Total items removed: " << i << '\n';
    }
    
    for (int i = 0; i < 3; i++)
    {
        l.insert(i);
    }

    try
    {
        while (true)
        {
            cout << "Item removed: " << l.remove_last() << '\n';
        }      
    }
    catch(char* ex)
    {
        cout << ex << '\n';
    }

    cout << "Preparing to test destructor ..." << endl;
    
    for (int i = 0; i < 3; i++)
    {
        l.insert(i);
        cout << "   ... inserted " << i << endl;
    }

    delete &l;

    cout << "Done testing linkedlist !!" << endl;
}