SimpleFloatArray::SimpleFloatArray (const SimpleFloatArray& a) {
  n = a.n;
  p = new float[n];
  for (int i=0; i<n; i=i+1)
    p[i]=a.p[i];
}
