#include <iostream>


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

IntListElem* find_first_x(IntList l, int x)
{
    for (IntListElem* p = l.first; p != 0; p = p->next)
    {
        if (p->value == x)
        {
            return p;
        }
    }
    return 0;
} 

void insert_in_list_cycle(IntList* list, IntListElem* where, IntListElem* ins)
{
    if (where == 0)
    {
        ins->next = ins;
        list->first = ins;
        ++list->count;
    }
    else
    {
        ins->next = where->next;
        where->next = ins;
        list->count = list->count + 1;
    }
}

void insert_in_list(IntList* list, IntListElem* where, IntListElem* ins)
{
    if (where == 0)
    {
        ins->next = list->first;
        list->first = ins;
        ++list->count;
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
    for (IntListElem* p = l.first; p != 0 and p->value != 0; p = p->next)
    {
        std::cout << p->value <<  " ";
    }
}

int haseigle(IntList* list)
{  
    bool meet = false;
    int count = 0; 
    IntListElem* hase = list->first;
    for (IntListElem* igel = list->first; igel != 0 and hase != 0; igel = igel->next)
    {
        ++count;
        hase = hase->next;
        if (hase != 0)
        {
            hase = hase->next;
            if (hase != 0)
            {
                if(hase->next == igel->next and meet == false)
                {
                    meet = true;
                    count = 0;        
                }
                else if(hase->next == igel->next)
                {
                    return count;
                }
            }
        }
    }
    return 0;
}

void createListandhase(int n,int k)
{
    IntList mylist;
    IntList myklist;
    bool nandk0 = false;
    empty_list(&mylist);
    IntListElem* nextpointer = mylist.first;
    if (n != 0)
    {
        for (int i = n-1; i >= 0; --i)
        {
            IntListElem* newelementpointer = new IntListElem;
            newelementpointer->value = i;
            insert_in_list_cycle(&mylist, nextpointer, newelementpointer);
            nextpointer = newelementpointer;
        }
        
        if (k != 0)
        {
            empty_list(&myklist);
            IntListElem* nextkpointer = myklist.first;
            for (int i = k-1; i >= 0; --i)
            {
                IntListElem* newelementpointer = new IntListElem;
                newelementpointer->value = i;
                insert_in_list(&myklist, nextkpointer, newelementpointer);
                nextkpointer = newelementpointer;
            }
            nextkpointer->next = mylist.first;
        }
        else
        {
            myklist = mylist;
        }
    }
    else
    {
        if (k != 0)
        {
            empty_list(&myklist);
            IntListElem* nextkpointer = myklist.first;
            for (int i = k-1; i >= 0; --i)
            {
                IntListElem* newelementpointer = new IntListElem;
                newelementpointer->value = i;
                insert_in_list(&myklist, nextkpointer, newelementpointer);
                nextkpointer = newelementpointer;
            }
        }
        else//n = 0 and k = 0 
        {
            nandk0 = true;
        }    
    }
    if (not nandk0)
    {
    std::cout << haseigle(&myklist) << std::endl;
    }
    else
    {
        std::cout << 0 << std::endl;    
    }  
}



int main()
{
    createListandhase(5,3);
    return 0;
}