[TOC]
## Rule40: Use multiple inheritance judiously

### Outline

### Practice

### Key Point

- 多重继承比单一继承复杂。它可能导致新的歧义性，以及对virtual inheritance的需要
- virtual inheritance会增加大小，速度，初始化(及赋值)复杂度等等成本。如果virtual base class不带有任何数据，将是最具有实用价值的情况。
- 多重继承的确有正当用途。其中一个情节涉及，"public inheritance某个interface class"和"private inheritance某个协助实现的class"的两者组合
