# 属性 :类属性与实例属性
# 类属性 就是类对象所拥有的属性
import time


class Student:
    name = '李明'  # 属于类属性 就是类对象所用的
    def __init__(self,age):
        self.age = age  # 实例属性
        pass
    pass
lm = Student(18)
print(lm.age)  # 通过实例对象去访问类属性
print(lm.age)
print('****通过类对象 student去访问name***')
print(Student.name)  # 通过类对象访问类属性  如 类名.实例属性 去访问
#  print(Student.age)
print('小花来了')
lh = Student(28)
print(lm.name)
print(lm.age)
# 小结
# 类属性可以被类对象和实例对象共同访问的 实例属性只能由实例对象所访问
# 所有实例对象的类对象指针指向统一类对象,存储在同一个地址下
# 实例属性在每个实例中独有一份,而类属性是在所有实例对象中共有一份

# 类属性修改与访问
class Student:
    name = '李明'  # 属于类属性 就是类对象所用的
    def __init__(self,age):
        self.age = age  # 实例属性
        pass
    pass
# Student.name = '李毅'  # 通过类对象去修改类属性 类属性的所拥有权是类对象
lm1 = Student(18)
lm1.name = '刘德华'  # 不能通过实例化对象修改类属性 把原来类属性覆盖 追加了新的实例化属性
print(lm1.age)
print(lm1.name)
lh1 = Student(28)
print(lh1.age)
print(lh1.name)
print('*********属性结束********')


# 类方法与静态方法

class People:
    country = '中国'

    def __init__(self):
        pass
    pass

    @classmethod  # 类方法标识符
    def get_country(cls):
        return cls.country  # 访问类属性
        pass

    @staticmethod  #静态方法
    def getDta():
        return People.country

print('******类方法******')
print(People.get_country())  # 通过类对象直接引用
p = People()
print('通过实例对象访问%s' % p.get_country())

# 为什么要使用静态方法 由于静态方法主要存放逻辑性代码,本身和类以及实力对象没有交互不会涉及到类中方法和属性的操作 数据资源能有效的利用
print('************静态方法**********')
print(People.getDta())  # 注意我们一般不一哦那个实例对象去访问静态方法

# demo 返回系统当前时间
class Time:
    def __init__(self, hour, min, second):
        self.hour = hour
        self.min = min
        self.second = second

    @staticmethod  # 独立的功能
    def showTime():
        return time.strftime("%H:%M:%S", time.localtime())
    pass
print(Time.showTime())

