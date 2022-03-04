#  __slots__限制class实例能动态添加属性
#  可以节约内存空间
class Student(object):
    __slots__ = ('name', 'age')
    def __str__(self):
        return '{}....{}'.format(self.name, self.age)
    pass

xw = Student()
xw.name = '小王'
xw.age = 20
print(xw)
# print(xw.__dict__)  # 所有可用的属性都在__dict__中存储 不足就是内存空间大
