# Python里数量词默认是贪婪的，总是尝试匹配尽可能多的字符，非贪婪模式则相反
# 在"*","?","+","{m,n}"后面加上？，使贪婪变成非贪婪

# 贪婪模式 默认的匹配规则(默认)
# 在满足条件的情况尽可能多的去匹配到数据
import re
rs = re.match('\d{6,9}','111122223333')
print(rs.group())

content = 'aacbacbc'
# pattern = re.compile('a.*b')
pattern = re.compile('a.*?b') # 非贪婪模式
result = pattern.search(content)
print(result)
print(result.group())

# 非贪婪模式
# 在满足条件下尽可能（少）的去匹配数据
rs1 = re.match('\d{6,9}?','111122223333')
print(rs1.group())