# 面向对象编程 oop 是一种python的编程思想
class Person:
    name = '小明'
    age = '19'
    def eat(self):
        print('吃饭')
        pass
#  类的实例化(创建一个新的类)
xm = Person()
xm.eat()  # 调用函数
print('{}的年龄:{}'.format(Person.name, Person.age))

