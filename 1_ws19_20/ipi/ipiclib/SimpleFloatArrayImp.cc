SimpleFloatArray::SimpleFloatArray (int s, 
				    float v)
{
  n = s;
  try {
    p = new float[n];
  }
  catch (std::bad_alloc) {
    n = 0;
    throw;
  }
  for (int i=0; i<n; i=i+1) p[i]=v;
}

SimpleFloatArray::~SimpleFloatArray () { delete[] p; }

int SimpleFloatArray::numIndices () { return n; }

int SimpleFloatArray::minIndex () { return 0; }

int SimpleFloatArray::maxIndex () { return n-1; }

bool SimpleFloatArray::isMember (int i)
{
  return (i>=0 && i<n);
}
