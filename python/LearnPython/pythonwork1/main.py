import random
# Qusetion 1。
'''
a = float(input('请输入你的身高:'))
b = int(input('请输入你的体重:'))
BMI = b /(a * a)
if BMI < 18.5:
    print('你的体重过轻')
    pass
elif 25 > BMI > 18.5:
    print('你的体重正常')
    pass
elif 28 > BMI > 25:
    print('你的体重过重')
    pass
elif 32 > BMI > 28:
    print('你的体重肥胖')
    pass
else:
    print('你的体重严重肥胖')
print('体重测试结束')
'''
# Qusetion 2。


'''
age = 21
item = 0
while True:
    while item < 3:
        a = int(input('猜猜我的年龄吧: 猜对了有奖励呦!'))
        if a == 21:
            print('恭喜你猜对了')
            break
        else:
            print('不好意思,猜错了')
            item += 1
        pass
    choose = input('你还想玩吗? Y or N')
    if choose == 'Y':
        item = 0
        continue
    else:
        break
print('下次在玩呦!')
'''


# 列表操作
list = [1, 2, 3, 4, 5, '你好']
print(len(list))
print(type(list))   # 输出类型
print(list[0])  # 输出第一个元素
print(list[1:3])    # 输出第二个开始到第三个元素
print(list[2:])  # 输出第三个到最后所有元素
print(list[::-1])  # 从右向左输出
list.append(['aaa', 'bbb'])  # 追加操作
list.append(888888)
print('追加之后', list)
list.insert(1, '插入的元素')  # 插入某一个元素操作
print('插入之后', list)
list.extend(['插入的列表'])  # 插入列表
print('插入列表之后', list)
print('*******修改列表*******')
print('修改之前', list)
list[2] = 123   # 修改第三个元素
print('修改之后', list)
print('*******删除列表********')
del list[1]  # 删除一个元素
del list[1:3]  # 删除多个元素
list.remove(1)  # 移除指定元素
list.pop(1)  # 移除指定项
print('删除之后', list)
print('********索引列表******')
print('索引之后', list)
# print('索引', list.index(3))  # 返回的是索引下标
print('索引之后', list)


# 元组操作 (不可变序列 创建之后不能做任何修改)
# 当元组只有一个元素时加上逗号
# tupleA = ()  # 空元组
tupleA = ('haha', 1, 2)
print('元组类型', type(tupleA))
print('打印元组', tupleA)
# 元组的查询
print('查询指定位置元组', tupleA[1:2])
print('倒序打印最后边元组', tupleA[-1])
print('倒序遍历打印元组', tupleA[::-1])
tupleB = tuple(range(20))
print('寻找元素出现的次数', tupleB.count(16))


# 字典操作   由键值对组成 和列表一样支持数据的添加,修改,和删除 没有下标的概念哦
# 创建字典
dictA = {}  # 空字典
dictA['name'] = '无一番'
dictA['age'] = '10'
dictA['pos'] = '演员'
print('打印字典长度', len(dictA))
print('打印字典对应键的值', dictA['name'])
dictA['name'] = '谢霆锋'
dictA['school'] = '香港大学'
print('打印字典所有键', dictA.keys())
print('打印字典所有的值', dictA.values())
print('打印字典所有键与值', dictA.keys(), dictA.values())
dictA.update({'地址': '中国澳门'})
# 删除
# del dictA['name']
dictA.pop('name')
print('删除字典之后', dictA)
# 排序
print('排列字典的键', sorted(dictA.items(), key=lambda d: d[0]))
# 共有方法操作 + * in
strA = list(range(10))
strB = list(range(11, 20))
print('合并列表', strA+strB)
