[TOC]
## Rule36: Never redefine an inherited non-virtual function.

q:Rule36为什么说和Rule32,Rule33,Rule34是一脉相承的?
>
- Rule32表明，每一个派生类对象，都是一个基类对象。在Rule32的基础上，Rule33规则如果突破，则会违背Rule32规则。
- Rule34表明，在class内声明一个non-virtual functions，则会建立起一个不变性，凌驾其特异性。
>
>所以，如果我们在派生类当中redefine a non-virtual function.
对于Rule32来说，每一个派生类对象都是一个基类对象，这点不成立。因为重定义的方法在基类和派生类对象中，
表现出不同的行为。此时，派生类和基类的同一个行为发生偏离。
>
>对于Rule34来说，基类当中声明的non-virtual function，无法在派生类中反映出，不变性凌驾其特异性。
因为派生类对象调用该方法，表现的是派生类的特性，而不是基类的不变性。
>
>所以，从以上两个角度来说，在派生类当中，都不应该重定义继承而来的non-virtual function.

我们再多讨论一点，在Rule34当中,我们从继承语义的角度说明了接口之间的差异，下面我们从另一个角度再进行讨论。
我们先来回顾Rule34的讨论。

q:derived class当中的继承语义有哪些？
- 只继承函数接口
- 同时继承函数接口和实现，并能进行重写
- 同时继承函数接口和实现，不允许重写

q:c++当中是如何通过语法特性来支持上述继承语义的？
- 声明一个pure virtual function的目的，让derived class只继承其接口
  - pure virtual function在base class(abstract class)中无定义
  - derived class需要给出一个实现
- 声明一个impure virtual function的目的，让derived class继承其接口和缺省实现
  - impure virtual function在base class当中的实现为缺省实现(default implementation)
  - derived class可以给出自己的实现，也可以采用base class当中的缺省实现
- 声明一个non-virtual function的目的，让derived class继承接口和强制性实现

我们从另一个角度来理解

q:non-virtual function和virtual function(include pure virtual function)语义上有何区别?
- non-virtual function体现接口的不变性
- virtual function体现接口的特异性
