# 析构方法的概述
# 当一个对象被删除 被销毁的时候 __del()__
# 程序结束自动销毁
class Animal:
    def __init__(self,name):
        self.name = name
        print('构造类建好了')
        pass

    def __del__(self):
        # 主要应用是来操作 对象的释放 一定被释放 类就不能清理
        print('这是析构方法')
        print('%s 这个对象被清理了 内存空间也释放了' % self.name)
        pass

cat = Animal('小花猫')
input('程序等待中欧......')
