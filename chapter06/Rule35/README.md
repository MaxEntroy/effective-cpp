## Rule35: Consider alternatives to virtual functions

### Virtual interface

- 手法
  - 声明public virtual interface
  - 派生类进行override

- 优点
  - 简单，直接。pure virtual functions的语义就是interface

- 缺点
  - 如果是impure virtual functions存在Rule34当中的接口和实现未分离的情形

```cpp
// game_character.h
#ifndef GAME_CHARACTER_H_
#define GAME_CHARACTER_H_

#include "common.h"

namespace ec {

class GameCharacter {
 public:
  GameCharacter() : hv_(0), level_(kJunior) {}
  GameCharacter(int hv, CharacterLevel level) : hv_(hv), level_(level) {}
  virtual ~GameCharacter() {}

 public:
  int hv() const { return hv_; }
  CharacterLevel level() const { return level_; }

  void set_hv(int hv) { hv_ = hv; }
  void set_level(CharacterLevel level) { level_ = level; }

  // health value is based on:
  // 1. damage type
  // 2. damage value
  // 3. character level
  virtual void UnderAttack(DamageType damage_type, int damage_value) = 0;

 protected:
  int hv_;
  CharacterLevel level_;
};

} // namespace ec

#endif // GAME_CHARACTER_H_


// warrior.h
#ifndef WARRIOR_H_
#define WARRIOR_H_

#include "game_character.h"

namespace ec {

class Warrior : public GameCharacter {
 public:
  Warrior() : GameCharacter() {}
  Warrior(int hv, CharacterLevel level) : GameCharacter(hv, level) {}

 public:
  void UnderAttack(DamageType damage_type, int damage_value) override;
};

} // namespace ec

#endif // WARRIOR_H_

// warlock.h
#ifndef WARLOCK_H_
#define WARLOCK_H_

#include "game_character.h"

namespace ec {

class Warlock : public GameCharacter {
 public:
   Warlock() : GameCharacter() {}
   Warlock(int hv, CharacterLevel level) : GameCharacter(hv, level) {}

 public:
   void UnderAttack(DamageType damage_type, int damage_value) override;
};

} // namespace ec

#endif // WARLOCK_H_
```

### Non-virtual interface

- 手法
  - 提供public non-virtual interface(严格来说不算interface，non-virtual肯定会有实现)
  - impure virtual fuctions已private/protected形式提供
  - 通过public non-virtual成员函数，间接调用，private/procted virtual函数

- 可能的形式如下

```cpp
class GameCharacter {
 public:
  int HealthValue() const {
    // ... do some start up work

    int retval = doHealthValue();
    
    // ... do some tear down work
    
    return retval;
  }
 private:
  virtual int doHealthValue() const {
    // ...
  }
};
```

- 优点
  - doHealthValue专注在对应逻辑上
  - HealthValue负责做一些预处理或者善后的逻辑
  - 分工明确，如果只提供一个virtual interface，那么需要它做所有工作

- 注意
  - private member在derived class中不可见，但并非不能override
  - 调用的权利还是保留在base class当中
  - ps: pure virtual function在abstract class当中可以被其余member functions调用(确实不好理解，没有定义的函数，为什么能被调用呢？)

  q:NVI idiom的好处我在优点中也提到，但是语义上的优点总感觉理解的不透彻，这么做，在语义上有什么好处？
  >看了stackover flow上的一段讲解，豁然开朗。
  >
  >Because the public interface is non-virtual, all derived classes automatically have logging as well. If instead you would have made SetStateBool and SetStateInt public, you could not have enforced logging for all derived classes.
  >
  >So the recommendation to use the NVI idiom is not a syntactic requirement, but it's a tool to enforce the base class semantics (logging, or caching) on all derived classes.
  >
  >其实，本质来说，确实是让SetStateBool/SetStateInt更专注于自己的工作。更细节的考虑在于，公共语义还是要放到base class当中，这样来确保derived class都能继承公共语义。

```cpp
  class Engine
{
public:
    void SetState( int var, bool val );
    {  
        logToFile(); 
        SetStateBool( int var, bool val ); 
    }

    void SetState( int var, int val );
    {   
        logToFile();
        SetStateInt( int var, int val ); 
    }
private:
    virtual void SetStateBool(int var, bool val ) = 0;    
    virtual void SetStateInt(int var, int val ) = 0;
    void logToFile();    
};
```

- 缺点
  - 可能导致FCB问题
  - 多一层调用，有额外的负担

- 实现

```cpp
// game_character.h
#ifndef GAME_CHARACTER_H_
#define GAME_CHARACTER_H_

#include "common.h"

namespace ec {

class GameCharacter {
 public:
  GameCharacter() : hv_(0), level_(kJunior) {}
  GameCharacter(int hv, CharacterLevel level) : hv_(hv), level_(level) {}
  virtual ~GameCharacter() {}

 public:
  int hv() const { return hv_; }
  CharacterLevel level() const { return level_; }

  void set_hv(int hv) { hv_ = hv; }
  void set_level(CharacterLevel level) { level_ = level; }

  // health value is based on:
  // 1. damage type
  // 2. damage value
  // 3. character level
  void UnderAttack(DamageType damage_type, int damage_value);

 private:

  virtual void DoUnderAttack(DamageType damage_type, int damage_value) = 0;

 protected:
  int hv_;
  CharacterLevel level_;
};

} // namespace ec

#endif // GAME_CHARACTER_H_

// warrior.h
#ifndef WARRIOR_H_
#define WARRIOR_H_

#include "game_character.h"

namespace ec {

class Warrior : public GameCharacter {
 public:
  Warrior() : GameCharacter() {}
  Warrior(int hv, CharacterLevel level) : GameCharacter(hv, level) {}

 private:
  void DoUnderAttack(DamageType damage_type, int damage_value) override;
};

} // namespace ec

#endif // WARRIOR_H_

// warlock.h
#ifndef WARLOCK_H_
#define WARLOCK_H_

#include "game_character.h"

namespace ec {

class Warlock : public GameCharacter {
 public:
   Warlock() : GameCharacter() {}
   Warlock(int hv, CharacterLevel level) : GameCharacter(hv, level) {}

 private:
   void DoUnderAttack(DamageType damage_type, int damage_value) override;
};

} // namespace ec

#endif // WARLOCK_H_

```

参考<br>
[Under the NVI idiom, why can't the virtual function be public?](https://stackoverflow.com/questions/32592419/under-the-nvi-idiom-why-cant-the-virtual-function-be-public)<br>
[【C++程序设计技巧】NVI（Non-Virtual Interface ）](https://www.cnblogs.com/gnuhpc/archive/2012/01/17/2324836.html)

### Strategy pattern

前2种方法是strategy的一种分解形式，最后一种是古典strategy

#### 将virtual functions替换为"函数指针成员变量"

#### 将virtual functions替换为"std::function成员变量"

#### 将virtual functions替换为"另一个继承体系当中的virtual functions"

### 总结
