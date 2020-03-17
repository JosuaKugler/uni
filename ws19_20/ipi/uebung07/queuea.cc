#include <iostream>
#include <cstdlib>

struct IntListElem
{
    IntListElem* next;
    int value;
};

struct IntList
{
    int count;
    IntListElem* first;
};

void empty_list(IntList* l)
{
    l->first = 0;
    l->count = 0;
}

void insert_in_list(IntList* list, IntListElem* where, IntListElem* ins)
{
    if (where == 0)
    {
        ins->next = list->first;
        list->first = ins;
        list->count = list->count + 1;
    }
    else
    {
        ins->next = where->next;
        where->next = ins;
        list->count = list->count + 1;
    }
}

IntListElem* remove_from_list(IntList* list, IntListElem* where)
{
    IntListElem* p;

    if (where == 0)
    {
        p = list->first;
        if (p != 0)
        {
            list->first = p->next;
            list->count = list->count - 1;
        }
        return p;
    }

    p = where->next;
    if(p != 0)
    {
        where->next = p->next;
        list->count = list->count - 1;
    }
    return p;
}

void print_List(IntList l)
{
    for (IntListElem* p = l.first; p != 0; p = p->next)
    {
        std::cout << p->value << std::endl;
    }
}

IntListElem* getfirst(IntList* list)
{
    return remove_from_list(list, 0);
}

void appendelement(IntList* list, IntListElem* element)
{
    IntListElem* letztesp = 0;
    for (IntListElem* p = list->first; p != 0; p = p->next)
    {
        letztesp = p;
    }
    insert_in_list(list, letztesp, element);
}

int main()
{
    int n = 100000;
    IntList mylist;
    empty_list(&mylist);
    IntListElem* nextpointer = mylist.first;
    for (int i = 0; i < n; ++i)
    {
        IntListElem* newelementpointer = new IntListElem;
        newelementpointer->value = rand();
        appendelement(&mylist, newelementpointer);
        nextpointer = newelementpointer;
    }
    for (int i = 0; i < n; ++i)
    {
        getfirst(&mylist);
    }
    print_List(mylist);
    return 0;
}