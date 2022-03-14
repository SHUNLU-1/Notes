# python里面一切东西皆是对象,他们的核心就是一个结构体:PyObject
# 优点 简单 实时性 一旦没有引用就直接被释放 不想其他机器语言需要等待时机 处理回收时间分摊了平时
# 缺点 维护引用计数会消耗资源  循环引用 导致内存泄露

# import sys
# #
# # a = []
# # print(sys.getrefcount(a)) # 被引用两次
# # b = a
# # print(sys.getrefcount(a)) # 被引用三次

# 循环数据结构以及引用计数
# 标记清楚机制 分代收集
import gc
import os
import sys
import psutil
def showMemSize(tag):
    pid = os.getgid()
    p = psutil.Process(pid)
    info = p.menory_full_info()
    menory = info.uss/1024/1024
    print('{}menory used:{}MB'.format(tag, menory))
    pass

# 验证循环引用的函数的情况
def func():
    showMemSize('初始化')
    a =[i for i in range(100000)]
    b =[i for i in range(100000)]
    b.append(a)
    a.append(b)
    showMemSize('创建列表之后')
    pass
func()
gc.collect() # 手动释放资源

