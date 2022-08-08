template<class T>
class Heap {
public:
  bool empty ();
  void push (T x);
  void pop ();
  T top ();
private:
  std::vector<T> data;
  void reheap (int i);
} ;

template<class T>
void Heap<T>::push (T x) {
  int i = data.size();
  data.push_back(x);
  while (i>0 && data[i]>data[(i-1)/2])
    {
      std::swap(data[i],data[(i-1)/2]);
      i = (i-1)/2;
    }
}

template <class T> 
void Heap<T>::reheap (int i)  {
  int n = data.size();
  while (2*i+1<n)
    {
      int l = 2*i+1;
      int r = l+1;
      int k = ((r<n) && (data[r]>data[l])) ? r : l;
      if (data[k]<=data[i]) break;
      std::swap(data[k], data[i]);
      i = k;
    }
}

template<class T>
void Heap<T>::pop () {
  std::swap(data.front(), data.back());
  data.pop_back();
  reheap(0);
}

template<class T>
T Heap<T>::top () {
  return data[0];
}

template<class T>
inline bool Heap<T>::empty () {
  return data.size()==0;
}
  
