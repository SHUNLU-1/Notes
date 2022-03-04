# re.compile方法
# compile 将正则表达式模式编译成一个正则表达式对象
# 可以吧一个字符串编译成字节码
# 优点： 在使用正则表达式进行match操作是，python会将字符串转化为正则式表达式
# 而如果使用compile则至于要完成一次转换即可，以后在需要使用的话 无需重新操作
import re
# 创建正则表达式模式对象
# reobj = re.compile('\d{4}')
# # 开始去使用模式对象reobj
# rs = reobj.match('1235678')
# print(rs.group())

# re.search 方法
# 在全文中匹配一次 匹配到就返回
# data = '我爱伟大的祖国'
# res = re.search('我爱', data)
# print(res)
# print(res.group())

# re.findall() 查询字符串莫个正则表达式全部未重复出现的情况 返回是一个符合正则表达式的结构列表
# data = '华为是华人的骄傲，华侨'
# res = re.findall('华.', data)
# print(res)
# res1 = re.search('华.', data)
# print(res1)
# # 改造一下使用 compilere
# reobj = re.compile('华.') #
# print(reobj.search(data))
# print(reobj.findall(data))

# re.sub 实现目标的搜索和查找 将匹配到的数据进行替换
dataS = 'Python is very good'
dataB = 'python 是非常受欢迎的语言'
# 字符集的范围 +号 代表前导字符模式出现1次为止
pattern = '[a-zA-Z]+'
res = re.sub(pattern, 'C#', dataB)
resn = re.subn(pattern, 'Java', dataB)
print(res)
print(resn)
# re.sub 实现目标的搜索和查找 将匹配到的数据进行替换 还返回被替换的数量

# re.split 实现分割字符串
data = '百度，腾讯，阿里，华为'
rs = re.split('，',data)
print(rs)
print(type(rs))
print(rs[1])