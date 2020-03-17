int fib (int n)
{
    int a=0;
    int b=1;
    for (int i=0; i<n; i=i+1)
    {
        int t=a+b; a = b; b = t;
    }
    return a;
}
