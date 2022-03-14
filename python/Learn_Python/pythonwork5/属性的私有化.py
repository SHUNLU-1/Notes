#  属性私有化
#  1,把一个属性隐藏起来 不想让类的外部进行直接调用
#  2,保护这个属性 不能随意改变 不允许派生类的调用

#  私有化属性
class Person:
    __hobby = '打游戏'  # 私有化类属性
    def __init__(self):
        self.__name = '李四'  # 加两个下划线 将此属性私有化
        self.age = 10
        print(self.__name)   # 在内部打印
        pass
    def __str__(self):
        '''
        私有化属性可以在内部使用 self.__name
        :return:
        '''
        return '{}的年龄是{},爱好是{}'.format(self.__name, self.age, Person.__hobby)
xl = Person()
print(xl.age)
print(xl)
print('******私有化属性结束*****')

#  私有化方法  子类不能继承 父类不能调用
class Animal:
    # __hobby = '打游戏'  # 私有化类属性
    # def __init__(self):
    #     self.__name = '李四'  # 加两个下划线 将此属性私有化
    #     self.age = 10
    #     print(self.__name)   # 在内部打印
    #     pass
    # def __str__(self):
    #     '''
    #     私有化属性可以在内部使用 self.__name
    #     :return:
    #     '''
    #     return '{}的年龄是{},爱好是{}'.format(self.__name, self.age, Person.__hobby)
    def __eat(self):
        print('吃饭')
        pass
    def run(self):
        self.__eat()
        print('跑步')
        pass
b1 = Animal()
b1.run()
print('******私有化方法结束*******')

# 属性函数 (保护属性方法)(Property)

class Person1:

    def __init__(self):
        self.__name = '李四'
        self.__age = 10
        print(self.__name)

    def get_age(self):  # 访问私有化属性
        return print(self.__age)

    def set_age(self, age):  # 修改私有化实例属性
        if age < 0:
            print('年龄不能小于0')
        else:
            self.__age = age
            print(self.__age)


    # 方式一 定义一个类属性 实现通过直接访问属性的形式去访问私有的属性
    age = property(get_age, set_age)
    # 方式二 通过装饰器方式去声明
    @property # 添加装饰器

    def get_age(self):  # 访问私有化属性
        return print(self.__age)

    # @set_age1.setter
    # def set_age1(self, age):  # 修改私有化实例属性
    #     if age < 0:
    #         print('年龄不能小于0')
    #     else:
    #         self.__age = age
    #         print(self.__age)

p1 = Person1()
print(p1.age)
# p1.set_age(12)
# p1.get_age()
