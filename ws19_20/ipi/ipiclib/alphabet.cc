#include "fcpp.hh"
char* alphabet (int n) {
    char buffer[n];
    for (int i=0; i<26; i++) buffer[i] = i+65;
    buffer[26]=0;
    print(buffer);
    return buffer;
}
int main () {
    print(alphabet(27));
}
