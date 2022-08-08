// Auswertung
float Polynomial::eval (float x)
{
  float sum=0.0;

  // Hornerschema
  for (int i=maxIndex(); i>=0; i=i-1)
    sum = sum*x + operator[](i);
  return sum;
}
