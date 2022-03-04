import re
# 1 , 'Save your heart for someone who cares' 请使用正则将文本中的‘s’换成‘S’，请用Python代码完成匹配替换
data = 'Save your heart for someone who cares'
res = re.sub('s','S',data)
res1 = re.subn('s','S',data)
print(res1)
print(res)
# 2,'<span>三生三世，十里桃花</span><span>九州海上牧云记</span><span>莫斯科行动</span>'请用正则表达式将其中内容读取出来
data1 = '<span>三生三世，十里桃花</span><span>九州海上牧云记</span><span>莫斯科行动</span>'
res2 = re.compile(r'<span>(.*)</span><span>(.*)</span><span>(.*)</span>')
result = res2.findall(data1)
print(result)