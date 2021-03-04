### GameCharacter

游戏人物抽象基类,提供如下属性和方法
- hv。血量
- level.游戏人物的等级。设计这个属性的目的在于，不同等级的同一个游戏人物，受到同一种伤害值的实际伤害值并不一定相同。
- UnderAttack()。接口，派生类实现该接口，提供不同游戏人物受到上还时，计算血量的方法。
- hv和level均为protected member，如果为private member，派生类重写的UnderAttack接口没有能力访问这2个属性

### Warrior

- UnderAttack()
  - 物理攻击。正常伤害
  - 魔法攻击。实际伤害值取决于人物不同的等级
    - 初级warrior，多受到30点攻击
    - 中级warrior，多受到20点攻击
    - 高级warrior，多受到10点攻击

### Warlock

- UnderAttack()
  - 魔法攻击。正常伤害。
  - 物理攻击。实际伤害值取决于人物不同的等级
    - 初级warlock,多受到30点攻击
    - 中级warlock，多受到20点攻击
    - 高级warlock，多受到10点攻击
