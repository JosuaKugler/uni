CheckedSimpleFloatArray::CheckedSimpleFloatArray (int s, float f)
  : SimpleFloatArray (s,f)
{}

float& CheckedSimpleFloatArray::operator[] (int i)
{
  assert (i>=minIndex() && i<=maxIndex());
  return SimpleFloatArray::operator[](i);
}
