# 多态:对于不同的子类有不同的形式表现
# 要想实现多态 必须有两个前提 1, 继承:多态必须发生在父类与子类之间 2,重写:子类重写父类方法
# 多态有什么用 增加程序的灵活性和扩展性
class Animal:
    '''
    父类 动物类
    '''
    def say_who(self):
        print('我是一个动物')
        pass
    pass
class Duck(Animal):
    '''
    鸭子类 {子类}派生类
    '''
    def say_who(self):
        ''''
        在这里重写父类方法
        '''
        print('我是一个漂亮的鸭子')
    pass
class Dog(Animal):
    '''
    小狗类 {子类}派生类
    '''

    def say_who(self):
        ''''
        在这里重写父类方法
        '''
        print('我是一个会说话的小狗')
    pass
class Cat(Animal):
    '''
    小猫类 {子类}派生类
    '''

    def say_who(self):
        ''''
        在这里重写父类方法
        '''
        print('我是一个喵喵的小猫')
    pass
# 动态语言的鸭子类型 动态类型的一种风格 在这种风格中,一个对象有效语义,不是有继承自特定的类或实现特定的接口,而是有当前方法和属性的集合决定
# 只要是同一个方法都能去调用
# 不注重鸭子类型 注重怎样去使用
def commonInoke(obj):
    '''
    统一调用方法
    :obj:
    :return:
    '''
    obj.say_who()

# duck1 = Duck()
# duck1.say_who()
# dog1 = Dog()
# dog1.say_who()
# cat1 = Cat()
# cat1.say_who()

listObj = [Dog(), Duck(), Cat()]
for item in listObj:
    '''
    循环去调用函数
    '''
    commonInoke(item)
    pass
