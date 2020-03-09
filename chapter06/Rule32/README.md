### Rule32: Make sure public inheritance models "is-a".

q:如何理解is-a?
>public inheritance意味着is-a，详细点来说，即适用于
base class身上的每一件事情(注意，是每一件事情),都适用于derived class.
否则，不能用public inheritance来描述classes之间的关系

q:对于is-a，作者都举了哪些例子？
>rectange和square的例子，令人映像深刻。主观的直觉在继承体系当中一定要小心，
正方形是矩形，这是有严格数学证明的。没有任何问题。但是我们如果用is-a关系
来描述正方形和矩形的关系，显然会失败。比如矩形可以单独增加width或者height，
但是对于正方形，显然这个方法不满足，因此，不能用is-a来进行构造

q:是否rectange和square就一定不能用is-a来构造呢？
>不是。不存在完美设计，只存在最佳设计。一定要具体问题，具体分析。
假如我们构造类之间的关系时，只考虑面积，那么可以用is-a来构造
square和rectangle之间的关系。is-a只是提醒我们，base class的所有行为
都适用于派生类，但是base class本身要定义哪些行为，需要具体问题，具体分析