# 在python中展现面向对象的三大特征: 封装 继承 多态
# 子继承父类的属性与行为 子类有的属性与行为 父类不一定拥有
# 单继承
class Animal:
    def eat(self):
        print('大家吃饭了')
        pass
    pass
class Cat(Animal):
    def miaomiaojiao(self):
        print('小猫喵喵叫')
        pass
    pass
class Dog(Animal):
    def wangwangjiao(self):
        print('小狗汪汪叫')
        pass
    pass

d1 = Dog()
c1 = Cat()
d1.eat()
d1.wangwangjiao()
c1.eat()
c1.miaomiaojiao()
# 多继承 加入多个父类
# 问题是当多个父类存在相同方法时 应该调用哪一个
class A:
    def eat(self):
        print('A 吃饭了')
        pass
    pass
class B:
    def eat(self):
        print('B 吃饭了')
        pass
    pass
class C(A):
    def eat(self):
        print('C 吃饭了')
        pass
    pass
class D(B,C):
    pass
a = C()
a.eat()
# 类的继承顺序 先找到谁先执行 从子类向父类进行

# 类的间接继承
# 类的传递过程中 我们把父类称为基类,子类又称为派生类,父类的属性和方法可以一级一级传递到子类
class GrandFather:
    def eat(self):
        print('爷爷吃饭')
class Father(GrandFather):
    pass
class Son(Father):
    pass
a = Son()
a.eat()

# 重写父类方法 子类中的方法会覆盖父类中相同的方法
# 为什么要重写: 父类的方法已经不满足子类需求 就可以去完善或重写父类
# super().__init__()自动找到父类 进而调用方法,假设继承了多个父类,那么将逐个进行
