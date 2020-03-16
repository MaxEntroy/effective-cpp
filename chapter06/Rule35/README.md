[TOC]
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

- 手法
  - virtual functons以non-member functions形式提供
  - 可以定义多个non-member functions来提供某种程度的多态
  - 类内提供function pointer member，用来接受non-member function

- 优点
  - 相比于virtual functions提供更强的灵活性(比如derived class对base class的virtual function进行override，只能提供UI个版本，但是non-member functions可以提供多个版本。)
  - 解耦合。本质上来说是把virtual functions在类内进行抽离

- 缺点
  - 弱化class 封装。(如果non-member functions需要访问non-public成员时，需要提供friend支持)

- 注意
  - function pointer的形式可以有多重理解。
  - 调用关系上，回调。
  - 语义上，此处的function pointer本质上实现了oo的多态(所以，c语言也完全有能力实现polymorphism)

- 实现
  - 本例派生类有增加成员的需求，定义派生类无可厚非。否则基类足以。
  - friend牵扯到头文件相互引用的问题。用forward declarations解决

```cpp
// game_charecter.h
#ifndef GAME_CHARACTER_H_
#define GAME_CHARACTER_H_

#include "common.h"

namespace ec {

// Forward declaration
class GameCharacter;

// UnderAttack Callback functions
void WarriorUnderAttack(GameCharacter*, DamageType, int);
void WarlockUnderAttack(GameCharacter*, DamageType, int);

class GameCharacter {
 public:
  typedef void(*DoUnderAttackFunc)(GameCharacter*, DamageType, int);
  friend void WarriorUnderAttack(GameCharacter*, DamageType, int);
  friend void WarlockUnderAttack(GameCharacter*, DamageType, int);

 public:
  GameCharacter() : hv_(0), level_(kJunior), do_under_attack_(nullptr) {}
  GameCharacter(int hv, CharacterLevel level, DoUnderAttackFunc func) : hv_(hv), level_(level), do_under_attack_(func) {}
  virtual ~GameCharacter() {}

 public:
  int hv() const { return hv_; }
  CharacterLevel level() const { return level_; }

  void set_hv(int hv) { hv_ = hv; }
  void set_level(CharacterLevel level) { level_ = level; }

  DoUnderAttackFunc do_under_attack() const {return do_under_attack_;}
  void set_do_under_attack(DoUnderAttackFunc func) {do_under_attack_ = func;}

  // health value is based on:
  // 1. damage type
  // 2. damage value
  // 3. character level
  void UnderAttack(DamageType damage_type, int damage_value);

 protected:
  int hv_;
  CharacterLevel level_;
  DoUnderAttackFunc do_under_attack_;
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
  Warrior() : GameCharacter(), age_(0) {}
  Warrior(int hv, CharacterLevel level, DoUnderAttackFunc func, int age)
    : GameCharacter(hv, level, func), age_(age) {}

 public:
  int age() const {return age_;}
  void set_age(int a) {age_ = a;}

 private:
  int age_;
};

} // namespace ec

#endif // WARRIOR_H_

// warlock.h
#ifndef WARLOCK_H_
#define WARLOCK_H_

#include <string>

#include "game_character.h"

namespace ec {

class Warlock : public GameCharacter {
 public:
  Warlock() : GameCharacter() {}
  Warlock(int hv, CharacterLevel level, DoUnderAttackFunc func, const std::string& g)
    : GameCharacter(hv, level, func), gender_(g) {}

 public:
  std::string gender() const {return gender_;}
  void set_gender(const std::string& g) {gender_ = g;}

 private:
  std::string gender_;
};

} // namespace ec

#endif // WARLOCK_H_
```

#### 将virtual functions替换为"std::function成员变量"

- 手法
  - 同上

- 优点
  - 设计上同上。
  - std::function vs functions pointers
    - 为什么计算生命值的计算逻辑必须是函数？
    - 如果一定是函数，为什么不能是一个成员函数？
    - 为什么一定得返回int而不是任何可被转化为int的类型(这个是书上的设计，我以为质疑的有理，我的实现是void)
    - 本质上来说，function pointers是c的常用做法，但是cpp则使用std::function来表达可调用对象这样的概念
      - 因为cpp中不是只有function这一种可调用对象
      - 并且std::function含有类型信息

- 缺点
  - 同上

- 实现
  - 增加UnderAttackWrapper，封装计算方法。解耦合。
  - GameCharacter为游戏基本任务。依赖UnderAttackWrapper.
  - Warlock and Warrior 继承GameCharacter，增加自己的角色属性

- 注意
  - std::bind的用法，有别于std::function提供的通用可调用对象能力
  - std::bind在本例的使用，主要是对函数进行某种形式的转化，使它不再接受4个参数，而是3个参数。从而可以当做实参传递给GameCharacter

```cpp
// under_attack_warpper.h
#ifndef UNDER_ATTACK_WRAPPER_H_
#define UNDER_ATTACK_WRAPPER_H_

#include "common.h"

namespace ec {

class UnderAttackWrapper {
 public:
  UnderAttackWrapper() {}

 public:
  // 物理基础伤害
  // 1.物理伤害不加倍
  // 2.魔法伤害根据角色等级加成
  int UnderAttackOnPhysical(DamageType damage_type,
                            CharacterLevel level,
                            int damage_value);

  // 魔法基础伤害
  // 1.魔法伤害不加倍
  // 2.物理伤害根据角色等级加成
  int UnderAttackOnMagic(DamageType damage_type,
                         CharacterLevel level,
                         int damage_value);
};

} // namespace ec

#endif // UNDER_ATTACK_WRAPPER_H_

// game_character.h
#ifndef GAME_CHARACTER_H_
#define GAME_CHARACTER_H_

#include <functional>

#include "common.h"

namespace ec {

class GameCharacter {
 public:
  typedef std::function<int(DamageType, CharacterLevel, int)> DoUnderAttackFunc;

 public:
  GameCharacter() : hv_(0), level_(kJunior), do_under_attack_(nullptr) {}
  GameCharacter(int hv, CharacterLevel level, DoUnderAttackFunc func) : hv_(hv), level_(level), do_under_attack_(func) {}
  virtual ~GameCharacter() {}

 public:
  int hv() const { return hv_; }
  void set_hv(int hv) { hv_ = hv; }

  CharacterLevel level() const { return level_; }
  void set_level(CharacterLevel level) { level_ = level; }

  DoUnderAttackFunc do_under_attack() const {return do_under_attack_;}
  void set_do_under_attack(DoUnderAttackFunc func) {do_under_attack_ = func;}

  // health value is based on:
  // 1. damage type
  // 2. damage value
  // 3. character level
  void UnderAttack(DamageType damage_type, int damage_value);

 protected:
  int hv_;
  CharacterLevel level_;
  DoUnderAttackFunc do_under_attack_;
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
  Warrior() : GameCharacter(), age_(0) {}
  Warrior(int hv, CharacterLevel level, DoUnderAttackFunc func, int age)
    : GameCharacter(hv, level, func), age_(age) {}

 public:
  int age() const {return age_;}
  void set_age(int a) {age_ = a;}

 private:
  int age_;
};

} // namespace ec

#endif // WARRIOR_H_

// warlock.h
#ifndef WARLOCK_H_
#define WARLOCK_H_

#include <string>

#include "game_character.h"

namespace ec {

class Warlock : public GameCharacter {
 public:
  Warlock() : GameCharacter() {}
  Warlock(int hv, CharacterLevel level, DoUnderAttackFunc func, const std::string& g)
    : GameCharacter(hv, level, func), gender_(g) {}

 public:
  std::string gender() const {return gender_;}
  void set_gender(const std::string& g) {gender_ = g;}

 private:
  std::string gender_;
};

} // namespace ec

#endif // WARLOCK_H_
```

#### 将virtual functions替换为"另一个继承体系当中的virtual functions"

- 手法
  - 标准strategy pattern
  - 提供一个Algorithm Interface, Context当中依赖该对象的基类指针

- 优点
  - 设计上同上，解耦合。把一个继承体系当中的虚函数抽出来，CalRealDamage更加独立。
  - 以上两种办法分别提供一组function list和member function list，本次提供一组继承体系当中的虚函数。

- 缺点
  - 同上

- 注意
  - Context Interface依赖Algorithm Interface对象的基类指针，本例的实现只接受栈对象地址，堆对象就需要考虑析构回收资源的问题

- 实现
```cpp
// under_attack.h
#ifndef UNDER_ATTACK_H_
#define UNDER_ATTACK_H_

#include "common.h"

namespace ec {

class UnderAttack {
 public:
  virtual ~UnderAttack() {}

 public:
  virtual int CalRealDamage(DamageType damage_type, CharacterLevel level, int damage_value) const = 0;
};

} // namespace ec

#endif // UNDER_ATTACK_H_

// under_attack_on_physical.h
#ifndef UNDER_ATTACK_ON_PHYSICAL_H_
#define UNDER_ATTACK_ON_PHYSICAL_H_

#include "under_attack.h"

namespace ec {

class UnderAttackOnPhysical : public UnderAttack {
 public:
  int CalRealDamage(DamageType damage_type, CharacterLevel level, int damage_value) const override;
};

} // namespace ec


#endif // UNDER_ATTACK_ON_PHYSICAL_H_

// under_attack_on_magic.h
#ifndef UNDER_ATTACK_ON_MAGIC_H_
#define UNDER_ATTACK_ON_MAGIC_H_

#include "under_attack.h"

namespace ec {

class UnderAttackOnMagic : public UnderAttack {
 public:
  int CalRealDamage(DamageType damage_type, CharacterLevel level, int damage_value) const override;
};

} // namespace ec

#endif // UNDER_ATTACK_ON_MAGIC_H_

// game_character.h
#ifndef GAME_CHARACTER_H_
#define GAME_CHARACTER_H_

#include "common.h"
#include "under_attack.h"

namespace ec {

class GameCharacter {
 public:
  typedef UnderAttack* PtrUnderAttack;

 public:
  GameCharacter() : hv_(0), level_(kJunior), attack_ptr_(nullptr) {}
  GameCharacter(int hv, CharacterLevel level, PtrUnderAttack attack_ptr) : hv_(hv), level_(level), attack_ptr_(attack_ptr) {}
  virtual ~GameCharacter() {}

 public:
  int hv() const { return hv_; }
  void set_hv(int hv) { hv_ = hv; }

  CharacterLevel level() const { return level_; }
  void set_level(CharacterLevel level) { level_ = level; }

  PtrUnderAttack attack_ptr() const {return attack_ptr_;}
  void set_attack_ptr(PtrUnderAttack attack_ptr) {attack_ptr_ = attack_ptr;}

  // health value is based on:
  // 1. damage type
  // 2. damage value
  // 3. character level
  void DoUnderAttack(DamageType damage_type, int damage_value);

 protected:
  int hv_;
  CharacterLevel level_;
  PtrUnderAttack attack_ptr_;
};

} // namespace ec

#endif // GAME_CHARACTER_H_

// warrior.h
#ifndef WARLOCK_H_
#define WARLOCK_H_

#include <string>

#include "game_character.h"

namespace ec {

class Warlock : public GameCharacter {
 public:
  Warlock() : GameCharacter() {}
  Warlock(int hv, CharacterLevel level, PtrUnderAttack attack_ptr, const std::string& g)
    : GameCharacter(hv, level, attack_ptr), gender_(g) {}

 public:
  std::string gender() const {return gender_;}
  void set_gender(const std::string& g) {gender_ = g;}

 private:
  std::string gender_;
};

} // namespace ec

#endif // WARLOCK_H_

// warlock.h
#ifndef WARLOCK_H_
#define WARLOCK_H_

#include <string>

#include "game_character.h"

namespace ec {

class Warlock : public GameCharacter {
 public:
  Warlock() : GameCharacter() {}
  Warlock(int hv, CharacterLevel level, PtrUnderAttack attack_ptr, const std::string& g)
    : GameCharacter(hv, level, attack_ptr), gender_(g) {}

 public:
  std::string gender() const {return gender_;}
  void set_gender(const std::string& g) {gender_ = g;}

 private:
  std::string gender_;
};

} // namespace ec

#endif // WARLOCK_H_
```

### 总结

我想本节的主要意图还是想告诉大家，当我们面对**多态**问题时，有如下的几种选择

- Virtual Interface(virtual functions)。首选方法，语义简单。如果虚函数不是为了多态而生，那它还有什么用
- Non-virtual Interface。
  - base class提供non-virtual interface，负责调用时机。具体来说，做一些准备和善后的工作，让虚函数专注自己的逻辑。否则，每一个继承的派生类在override时，都需要做准备和善后的工作。
  - base class提供private virtual interface.
- Strategy Pattern
  - 解耦合。通过另一组设计来实现多态，client通过回调的形式实现真正的多态逻辑。