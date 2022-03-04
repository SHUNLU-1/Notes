'''
def sum(a, b):
    sum = a + b
    print('值的和是:', sum)
    pass


#  函数的调用
sum(20, 15)


def getComputer(*args):
    print()
'''

#  写函数,接收n个数字,球这些参数数字的和
'''
def sumFunc(*args):
    #  处理接受的数据
    result = 0
    for item in args:
        result += item
        pass
    return result
    pass


rs = sumFunc(1, 2, 3, 4, 5)
print('rs1=%d' % rs)
'''

#  写函数 找出传入列表或元组技术为对应的元素,并返回一个新的列表
def process_Func(con):
    listA = []
    index = 1
    for i in con:
        if index % 2 == 1:
            listA.append(i)
            pass
        index += 1
    return listA
    pass
rs2 = process_Func([1, 2, 3, 4, 5, 6, 7])
rs3 = process_Func([1, 2, 3, 4, 5, 6, 7])
print(rs2)
print(rs3)
#  写函数 检查传入字典的每一个value的长度,如果大于2那么仅两个长度的内容保留,并且保留为调用

# 匿名函数
# lambda 参数1,参数2,参数3:表达式
# 只能封装简单的逻辑式
def num(a, b):
    c = a+b
    return c
d = lambda a, b: a+b
f = (lambda a, b: a+b)(3, 4)  # 直接调用
print('f的值{}'.format(f))
print('d的值{}'.format(d(1, 2)))
print('num的值{}'.format(num(1, 2)))

#  递归函数  在自己内部不调用其他函数,而是自己本身   必须有一个明确的结算条件
#  求阶乘(普通方法)
def jiecheng(n):
    result = 1
    for item in range(1, n+1):
        result *= item
    return result


print(jiecheng(10))
#  递归方式
def diguiJc(n):
    if n == 1:
        return 1
    else:
        return n*diguiJc(n-1)
    pass
print(diguiJc(10))

#  内置函数  python程序开发封装好的

#  数学运算的函数
#  abs (取绝对值)
print(abs(-1))
#  round(去近似值)
print(round(3.55))
#  pow() 求次方
print(pow(3, 3))
#  max 求最大值
listA = [1, 2, 3, 4]
print(max(listA))
# sum 求和
# eval() 执行表达式 返回表达式的值 可以执行函数
# a, b, c, = 1, 2, 3
# print(eval(a*b+c))

#  类型转换函数
#  bin()转化为二进制
print(bin(10))
#  hex转化为16进制
print(hex(10))
#  chr()数字转字符  将数值转化为ASCII码
print(chr(10))
#  元组转化为列表
tup = ()
li = list(tup)
print(type(li))
li.append('强制转化成功')
print('转化后{}'.format(li))
# dict()创建一个字典
dic = dict()
print(type(dic))
# bytes()转化字节数组
# print(bytes('我喜欢python'),)

# 序列操作函数
# all() 里面有一个元素为假全为假(0, 空, False) 类似and
print(all([]))
print(all(()))
print(all({}))
# any() 里面只要一个元素为真全为真  类似 or

#  sorted() 对所有可迭代对象进行排序
#  sorted() 与 sort区别
li = [1, 2, 3]
li.sort()  # list的排序方法 直接修改原始对象 只针对list
liNew = sorted(li)  # sorted对所有可迭代对象排序(list,str,dict) 返回一个新的list
print('排序之前{}'.format(li))
print('排序之后{}'.format(liNew))
# reverse 反序排列
liNewA = sorted(li, reverse=True)
print('降序需排序之后{}'.format(liNewA))
liNewB = sorted(li, reverse=False)
print('升序需排序之后{}'.format(liNewB))
# range()可以创建一个整数列表
# zip() 打包 压缩列表为一个新的列表 会把
lists1 = [1, 2, 3, 4]
lists2 = ['a', 'b', 'c', 'd']
print(list(zip(lists1, lists2)))  # (压缩两个参数)
# enumerate()  用一一个可遍历的数据对象 组成一个索引序列,同时标出数据和数据下标
# 一般用在for循环
listObj = ['a', 'b', 'c']
for index in enumerate(listObj):
    print(index)
    pass
for item, index in enumerate(listObj):
    print(index)
    pass
for index, item in enumerate(listObj, 5):
    print(index, item)
    pass
# 集合操作
# set集合 也是一种数据类型,是一个无序的集合 不支持索引与切片,是一个无序且不重复的容器
# 类似于字典 但没有key 没有value
# 创建集合
set1 = {1, 2, 3}
print(set1)
# 添加集合操作
set1.add('python')
print(set1)
# 清空
set1.clear()
print(set1)
# difference() 两个集合的差集 只要a中存在的
set2 = {1, 2, 3, 4}
set3 = {2, 3, 4, 5}
print(set2.difference(set3))
print(set2-set3)
# 交集操作
print('交集操作', set2.intersection(set3))
print(set2 & set3)
# 并集操作
print('并集操作', set2.union(set3))
print(set2 | set3)
# pop()就是从集合中拿出数据删除 随机拿出某一个元素
print(set2)
popA = set2.pop()
print('pop操作', popA)
# discard 移除指定元素
set4 = {1, 2, 3, 4, 5, 6}
print('discard操作', set4.discard(3), '操作后', set4)
# 更新集合
print('更新前set1=', set1)
print('更新前set2=', set2)
set1.update(set2)
print('更新后', set1)

# 求三组连续自然数的和 :求出1到10,20到35,和35到45的三个的和
def sumRange(m, n):
    return sum(range(m, n+1,1))
    pass
print('一到十', sumRange(1, 10))
print('20到35', sumRange(10, 35))
print('35到45', sumRange(35, 45))
# 100个和尚吃100个馒头,大和尚一人吃三个馒头,小和尚三人吃一个馒头问大小和尚多少人
def Personcount():
    for a in range(1, 100):
        if a*3+(100-a)*(1/3) == 100:
            return(a, 100-a)
        pass
rsObj = Personcount()
print('大和尚{}个人,小和尚{}个人' .format(rsObj[0], rsObj[1]))
# 指定一个列表,列表中有唯一一个出现一次的数字.找出'独一无二的数字'
# 方法一
li = [1, 2, 2, 3, 4, 5, 6, 3, 4, 5, 6]
set5 = set(li)
print(set5)
for i in set5:
    li.remove(i)
    pass
set6 = set(li)
for i in set5:
    if i not in set6:
        print('独一无二', i)
        pass
    pass
pass

