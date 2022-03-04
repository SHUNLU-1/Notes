# | 匹配左右任意一个表达式
# （ab）将括号中的字符作为一个分组
#  \num 引用分组num匹配到的字符串
# （？P）分组取别名
# （？P=name）引用别名为name分组匹配到的字符串


# | 匹配左右任意一个表达式
# 实际上是一个或的关系  （从左往右）
# import re
# string = 'wywsqpeng8888'
# ret = re.match('(wywsqpeng|wywsqpeng8888)',string)
# print(ret.group())
# import re
# string = 'wywsqpeng8888'
# ret = re.match('(wywsqpeng8888|wywsqpeng)',string)
# print(ret.group())

# （ab）将括号中的字符作为一个分组 (分组匹配)
# 匹配电话号码
import re
Phonenumble = '0355-34512683'
# res = re.match('([0-9]*)-(\d*)',Phonenumble)
res = re.match('([^-]*)-(\d*)', Phonenumble)
print(res.group(0))
print(res.group(1))
print(res.group(2))

#  \num 引用分组num匹配到的字符串
htmlTag = '<html><h1>测试数据</h1></html>'
res = re.match(r'<(.+)><(.+)>(.+)</\2></\1>', htmlTag)
print(res.group(1))
print(res.group(2))
print(res.group(3))

# （？P）分组取别名
# 别名的使用
data = '<div><h1>www.baidu.com</h1></div>'
# res = re.match(r'<(\w*)><(\w*)>.*</\w*></\w*>', data)
res = re.match(r'<(?P<name1>\w*)><(?P<name2>\w*)>(.*)</(?P=name2)></(?P=name1)>', data)
print(res.group())
print(res.group(1))
print(res.group(2))
print(res.group(3))

