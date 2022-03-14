# 概述
# 又称规则表达达式 通过被用来检索，替换符合某个模式（规则）的文本

# re 模块
# re.match  尝试从字符串的起始位置 匹配一个规则 匹配成功就返回match对象 否则就返回None 可以使用group（）获取匹配成功的字符串
# re.match(pattern,string,flags=0) pattern:匹配的正则表达式 string：要匹配的字符串 flags：标志位 匹配的方法
# import re
# str='Python'
# # 从一个字符串起始位置去匹配（精确匹配）
# res = re.match('P',str)
#
# print(type(res))
# # group（num）匹配对象函数来获取匹配表达式 如果有多个匹配结果 那么会以元组的形式存放
# print(res.groups())
# print(res.group())

import re
str='Python is the best language in the world'
# 标志位用法
# re.I ：使匹配对大小写不敏感
# re.L : 对本地化识别匹配
# re.M ：多行匹配
# re.S ：使.匹配包括换行在内的所有字符
# re.U ：根据Unicode字符集解析字符
# re.X ：该标志位通过给予你更灵活的格式以便于你将正则表达式写的更加易于理解
res = re.match('P', str, re.I)
if res:
    print('匹配成功')
    print(res)
    print(type(res))
    print(res.groups())
    print(res.group())
else:
    print(res)
    print('匹配失败')
# []中括号的使用 匹配规则 ： 匹配中括号的任意一个字符
