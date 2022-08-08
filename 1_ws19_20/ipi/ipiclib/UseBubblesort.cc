#include<iostream>

// SimpleFloatArray mit virtuellem operator[]
#include "SimpleFloatArrayV.hh"
#include "SimpleFloatArrayImp.cc"
#include "SimpleFloatArrayIndex.cc"
#include "SimpleFloatArrayCopyCons.cc"
#include "SimpleFloatArrayAssign.cc"

// templatisierte Variante mit variabler Groesse
#include "SimpleArray.hh"
#include "SimpleArrayImp.cc"

// templatisierte Variante mit Compile-Zeit Groesse
#include "SimpleArrayCS.hh"
#include "SimpleArrayCSImp.cc"

// dynamisches listenbasiertes Feld
#include "FloatArray.hh"
#include "ListFloatArrayDerived.hh"
#include "ListFloatArrayImp.cc"

// Zeitmessung
#include "timestamp.cc"

// generischer bubblesort
#include "bubblesort_.cc"

// Zufallsgenerator
#include "Zufall.cc"

const int n = 32000;

static Zufall z(93576);

template <class T>
void initialisiere (T & a) {
    for (int i=0; i<n; i=i+1)
        a[i] = z.ziehe_zahl();
}
    
int main ()
{
    SimpleArrayCS<float,n> a(0.0);
    SimpleArray<float> b(n,0.0);
    SimpleFloatArray c(n,0.0);
    ListFloatArray d;

    initialisiere (a); initialisiere (b);
    initialisiere (c); initialisiere (d);

    time_stamp();
    std::cout << "SimpleArrayCS ...";
    bubblesort(a);
    std::cout << time_stamp() << " sec" << std::endl;
    std::cout << "SimpleArray ...";
    bubblesort(b);
    std::cout << time_stamp() << " sec" << std::endl;
    std::cout << "SimpleFloatArray ...";
    bubblesort(c);
    std::cout << time_stamp() << " sec" << std::endl;
    // cout << "ListFloatArray ...";
    // bubblesort(d);
    // cout << time_stamp() << " sec" << endl;
}
