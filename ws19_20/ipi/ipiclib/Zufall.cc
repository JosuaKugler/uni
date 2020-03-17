class Zufall {
public:
    Zufall (unsigned int anfang);
    unsigned int ziehe_zahl ();
private:
    unsigned int x;
} ;

Zufall::Zufall (unsigned int anfang) {
    x = anfang;
}

// Implementierung ohne lange Arithmetik
// siehe Numerical Recipes, Kap. 7.     
unsigned int Zufall::ziehe_zahl ()
{
    // a = 7^5, m = 2^31-1                  
    unsigned int ia = 16807,  im = 2147483647;
    unsigned int iq = 127773, ir = 2836;
    unsigned int k = x/iq;
    x = ia*(x-k*iq)-ir*k;
    if (x<0) x = x+im;   
    return x;            
}
