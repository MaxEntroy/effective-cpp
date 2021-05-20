## Chapter01 Basics

### Item2: Prefer c++ style casts

#### Why?
- For one thing, they’re rather crude beasts, letting you cast pretty much any type to pretty much any other type. It would be nice to be able to specify more precisely the purpose of each cast.Traditional C-style casts make no such distinctions.(This is hardly a surprise. C-style casts were designed for C, not C++.)
- A second problem with casts is that they are hard to find.

>我的理解，第一条很明显，c style casts可以进行任意类型转换，语义不明确。如果在c里面使用，可能是ok的。但是c++则不行，比如downcasting，c style cast做不好。
第二条是说，(type)(identifier)不好找。

#### How?

- A static_cast is used for all conversions that are well-defined.
  - typical castless conversions
  - narrowing (information-losing) conversion
  - forcing a conversion from a void*
  - implicit type conversions
  - and static navigation of class hierarchies

```cpp
//: C24:Statcast.cpp
// Examples of static_cast

class Base { /* ... */ };
class Derived : public Base {
public:
  // ...
  // Automatic type conversion:
  operator int() { return 1; }
};

void func(int) {}

class Other {};

int main() {
  int i = 0x7fff; // Max pos value = 32767
  long l;
  float f;
  // (1) typical castless conversions:
  l = i;
  f = i;
  // Also works:
  l = static_cast<long>(i);
  f = static_cast<float>(i);

  // (2) narrowing conversions:
  i = l; // May lose digits
  i = f; // May lose info
  // Says "I know," eliminates warnings:
  i = static_cast<int>(l);
  i = static_cast<int>(f);
  char c = static_cast<char>(i);

  // (3) forcing a conversion from void* :
  void* vp = &i;
  // Old way produces a dangerous conversion:
  float* fp = (float*)vp;
  // The new way is equally dangerous:
  fp = static_cast<float*>(vp);

  // (4) implicit type conversions, normally
  // Performed by the compiler:
  Derived d;
  Base* bp = &d; // Upcast: normal and OK
  bp = static_cast<Base*>(&d); // More explicit
  int x = d; // Automatic type conversion
  x = static_cast<int>(d); // More explicit
  func(d); // Automatic type conversion
  func(static_cast<int>(d)); // More explicit

  // (5) Static Navigation of class hierarchies:
  Derived* dp = static_cast<Derived*>(bp);
  // ONLY an efficiency hack. dynamic_cast is
  // Always safer. However:
  // Other* op = static_cast<Other*>(bp);
  // Conveniently gives an error message, while
  Other* op2 = (Other*)bp;
  // Does not.
} ///:~
```

>第1,2,4都好理解。我觉得第4条应该避免，使用explicit syntax. 3可以这么做的原因是，void*是泛型指针，所以它转换为其他类型，是类型兼容的。5其实不建议这么做了，
还可以是因为知道基类指针指向了派生类对象，downcast就不要这么使用了。关于static_cast中well-defined的理解，我觉得可以理解为类型兼容。

- const_cast is used to cast away the constness or volatileness of an expression.

```cpp
//: C24:Constcst.cpp
// Const casts

int main() {
  const int i = 0;
  int* j = (int*)&i; // Deprecated form
  j  = const_cast<int*>(&i); // Preferred
  // Can't do simultaneous additional casting:
//! long* l = const_cast<long*>(&i); // Error
  volatile int k = 0;
  int* u = const_cast<int*>(&k);
}

class X {
  int i;
// mutable int i; // A better approach
public:
  void f() const {
    // Casting away const-ness:
    (const_cast<X*>(this))->i = 1;
  }
}; ///:~
```

>const_cast的使用语义非常明确，一般不会用错。

- dynamic_cast, is used to perform safe casts down or across an inheritance hierarchy. 

```cpp
Widget *pw;
...
update(dynamic_cast<SpecialWidget*>(pw));
// fine, passes to update a pointer
// to the SpecialWidget pw points to
// if pw really points to one,
// otherwise passes the null pointer
void updateViaRef(SpecialWidget& rsw);
updateViaRef(dynamic_cast<SpecialWidget&>(*pw));
// fine, passes to updateViaRef the
// SpecialWidget pw points to if pw
// really points to one, otherwise
// throws an exception
```

>dynamic_cast的使用语义也非常明确，继承体系，safety down-casting.

- reinterpret_cast
  - A reinterpret_cast pretends that an object is just a bit pattern that can be treated (for some dark purpose) as if it were an entirely different type of object.
  - This is the low-level bit twiddling that C is notorious for.
  - A reinterpret_cast lets you force compilers to see things your way
  - Of course, this is inadvisable and nonportable programming.

```cpp
//: C24:Reinterp.cpp
// Reinterpret_cast
// Example depends on VPTR location,
// Which may differ between compilers.
#include <cstring>
#include <fstream>
using namespace std;
ofstream out("reinterp.out");

class X {
  static const int sz = 5 ;
  int a[sz];
public:
  X() { memset(a, 0, sz * sizeof(int)); }
  virtual void f() {}
  // Size of all the data members:
  int membsize() { return sizeof(a); }
  friend ostream&
    operator<<(ostream& os, const X& x) {
      for(int i = 0; i < sz; i++)
        os << x.a[i] << ' ';
      return os;
  }
  virtual ~X() {}
};

int main() {
  X x;
  out << x << endl; // Initialized to zeroes
  int* xp = reinterpret_cast<int*>(&x);
  xp[1] = 47;
  out << x << endl; // Oops!

  X x2;
  const int vptr_size= sizeof(X) - x2.membsize();
  long l = reinterpret_cast<long>(&x2);
  // *IF* the VPTR is first in the object:
  l += vptr_size; // Move past VPTR
  xp = reinterpret_cast<int*>(l);
  xp[1] = 47;
  out << x2 << endl;
} ///:~
/*Clearly, it’s not safe to assume that the data in the object begins at the starting address of the object. 
In fact, this compiler puts the VPTR at the beginning of the object, so if xp[0] had been selected instead of xp[1], 
it would have trashed the VPTR.*/
```

>我个人的理解是，这是最灵活的一种cast，同时也是最不安全的一种转换。最不安全主要是说，这里面已经没有类型了。完全暴露给你的变量就是bit，你可以自己定义如何解释。
慎用！

#### More?

>Whenever you use a cast, you’re breaking the type system. [69] 
You’re telling the compiler that even though you know an object is a certain type, you’re going to pretend it is a different type. 
This is an inherently dangerous activity, and a clear source of errors.

[Explicit cast syntax](https://www.fi.muni.cz/usr/jkucera/tic/tic0277.html)
