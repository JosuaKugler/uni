template<class T>
class Ptr {
  struct RefCntObj {
    int count;
    T* obj;
    RefCntObj (T* q) { count = 1; obj = q; }
  };
  RefCntObj* p;
    
  void report () {
    std::cout << "refcnt = " << p->count << std::endl;
  }
  void increment () {
    p->count = p->count + 1;
    report();
  }
  void decrement () {
    p->count = p->count - 1;
    report();
    if (p->count==0) {
      delete p->obj; // Geht nicht fuer Felder!
      delete p;
    }
  }

public:
  Ptr () { p=0; }

  Ptr (T* q) {
    p = new RefCntObj(q);
    report();
  }

  Ptr (const Ptr<T>& y) {
    p = y.p;
    if (p!=0) increment();
  }

  ~Ptr () {
    if (p!=0) decrement();
  }

  Ptr<T>& operator= (const Ptr<T>& y) {
    if (p!=y.p) {
      if (p!=0) decrement();
      p = y.p;
      if (p!=0) increment();
    }
    return *this;
  }

  T& operator* () { return *(p->obj); }

  T* operator-> () { return p->obj; }
};
