## Rule35: Consider alternatives to virtual functions

### virtual functions

这么做的思路也非常简单。抽象类定义接口，派生类实现接口。
对于抽象类的设计，有一些更多的思考，参看/demo-01/README.md

```cpp
// game_character.h

// warrior.h

// warlock.h
```


### Non-virtual interface

### Strategy pattern

前2种方法是strategy的一种分解形式，最后一种是古典strategy

#### 将virtual functions替换为"函数指针成员变量"

#### 将virtual functions替换为"std::function成员变量"

#### 将virtual functions替换为"另一个继承体系当中的virtual functions"

### 总结
