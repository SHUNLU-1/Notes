#  单例模式 是一种常用的软件设计模式 目地 :确保一个类只有一个实例存在
#  创建一个单例模式 (基于__new__去实现)(推荐的一种)
class Animal(object):
    '''
    hasattr(object, name) hasattr() 函数用于判断对象是否包含对应的属性。
    object -- 对象。
    name -- 字符串，属性名。
    return
    如果对象有该属性返回 True，否则返回 False。
    '''
    def __new__(cls, *args, **kwargs):
        # cls._instance = cls.__new__()  # 不能使用自身的_new_去调用
        if not hasattr(cls, '_instance'):  # 如果未创建就开始创建
           cls._instance = super().__new__(cls, *args, **kwargs)
        return cls._instance


class Cat(Animal):
    pass


animal = Animal()
print(id(animal))
animal1 = Animal()
print(id(animal1))

animal2 = Cat()
print(id(animal2))
animal3 = Cat()
print(id(animal3))
