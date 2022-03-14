import re
mypath = ''
print(mypath)
print(re.match('c:\\\\a.txt','c:\\a.txt').group()) # 加双斜杠
print(re.match(r'c:\\a.txt','c:\\a.txt').group()) # 加r 表示原生字符串

# ^ 匹配字符串的开头
# result = re.match('^P*','Python is language')
result = re.match('^P\w{5}','Python is language')
if result:
    print(result.group())
# $ 匹配字符串的结尾
# 匹配邮箱的结尾
result = re.match('[\w]{5,15}@[\w]{2,3}.com$','accountwywsq@qq.com')
if result:
    print(result.group())
