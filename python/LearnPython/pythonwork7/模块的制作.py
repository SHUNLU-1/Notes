# 模块的定义
# 在python中 一个.py文件就是一个模块 作用:可以是我们有逻辑的去组织哦我们的python代码
# 以库的形式去封装功能  不同模块中可以定义不同的变量名 但是每个模块中的变量名的作用域只能在本模块中使用

# __all__--------->在使用from  xxx   import *使用时会被导入
__all__ = ['add', 'diff']

def add(x,y):
    '''
    普通的函数
    :param x:
    :param y:
    :return:
    '''
    return x+y

def diff(x, y):
    return x-y

# 测试

if __name__=='__main__':
    res = add(2,4)
    print('模块测试1:', res)
    print('模块测试2: %d' % res)
    print('模块测试3: {}'.format(res))
    print('模块__name__: %s' % __name__)
