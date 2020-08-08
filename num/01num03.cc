#include <iomanip>
#include <iostream>

using namespace std;

int main()
{
    //float x;
    double x;
    cin >> x;
    x = x + 1;
    cout << setprecision(50) << x;
}