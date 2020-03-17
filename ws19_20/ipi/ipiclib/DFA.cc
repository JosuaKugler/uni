class DynamicFloatArray : public FloatArray { 
public:
  DynamicFloatArray () {n=0; o=0; p=new float[1];}

  virtual ~DynamicFloatArray() {delete[] p;}
  virtual float& operator[](int i);
  virtual int numIndices () {return n;}
  int minIndex ()           {return o;}
  int maxIndex ()           {return o+n-1;}
  bool isMember (int i) {return (i>=o)&&(i<o+n);}
private:
  int n;      // Anzahl Elemente
  int o;      // Ursprung der Indexmenge
  float *p;   // Zeiger auf built-in array
} ;

float& DynamicFloatArray::operator[] (int i)
{
  if (i<o || i>=o+n)
    {    // resize
      int new_o, new_n;
      if (i<o) {
        new_o = i;
        new_n = n+o-i;
      }
      else {
        new_o = o;
        new_n = i-o+1;
      }
      float *q = new float[new_n];
      for (int i=0; i<new_n; i=i+1) q[i]=0.0;
      for (int i=0; i<n; i=i+1)
        q[i+o-new_o] = p[i];
      delete[] p;
      p = q;
      n = new_n;
      o = new_o;
    }
  return p[i-o];
}
