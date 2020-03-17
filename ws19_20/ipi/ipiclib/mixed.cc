enum Kind {rational, complex};

struct Rational {    // rationale Zahl
  int n; int d;
} ;

struct Complex {    // komplexe Zahl
  float re; float im;
} ;

union Combination { // vereinige beide
  Rational p; Complex  c;
} ;

struct Mixed {     // gemischte Zahl
  Kind a;          // welche bist Du?
  Combination com; // benutze je nach Art
} ;
