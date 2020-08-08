#include<iostream>

using namespace std;

double f(double x) {
    return (x < 0.5) ? 2*x : 2 - 2*x;
}

int main(){
    double x = 0.01401;
    for (size_t i = 0; i < 100; i++)
    {
        cout << i << "," << x << endl;
        x = f(x); 
    }
    cout << x << endl;
    return 0;
}