#  _new_方法 创建并返回一个实例对象,如果_new_只调用一次,就会得到一个对象.继承自object的新式类才有new这一魔术方法
#  _new_是在一个对象实例化的时候所调用的地一个方法
#  _new_必须有一个参数cls,代表要实例化的类
#  _new_决定是否要使用该__init__方法 因为他可以调用其他类的构造方法或者直接返回别的实例对象来作为本类的实例
#  在__new__方法中 不能呢个调用自己的__new__方法
class Animal:
    __hobby = '打游戏'
    def __init__(self):
        self.color = '红色'
        self.age = 10
        print(self.color)
        pass
    #  在python中 如果不重新 __new__ 默认结构
    def __new__(cls, *args, **kwargs):
        return super().__new__(cls, *args, **kwargs)  # 两种方式
        # return object().__new__(cls, *args, **kwargs)
    pass


cat = Animal()  # 实例化的过程中会自动调用__new__去创建实例


