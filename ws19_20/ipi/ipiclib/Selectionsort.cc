template <class C> 
void selectionsort (C& a) 
{
  for (int i=0; i<a.size()-1; i=i+1)
    {   // i Elemente sind sortiert
      int min = i;
      for (int j=i+1; j<a.size(); j=j+1)
	if (a[j]<a[min]) min=j;
      std::swap(a[i],a[min]);
    }
}
