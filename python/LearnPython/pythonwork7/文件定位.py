# 文件定位 tell()
# 文件定位是指当前文件指针读取到的位置,光标位置.在读写文件的过程中,如果想知道当前文件的位置,可以使用tell()来获取
# 返回当前指针所在的位置
# 对于中文来讲 每次读取到一个汉字 就相当与读取了两个字符
# with open('/home/ubuntu/PycharmProjects/LearnPython/pythonwork7/1.txt', 'r') as f:
#     print(f.read(1))
#     print(f.tell())
#     print(f.read(1))
#     print(f.tell())

# truncate 可以对源文件进行截取操作
# with open('/home/ubuntu/PycharmProjects/LearnPython/pythonwork7/1.txt', 'r') as f:
#     print(f.read())
#     # 保留前十五个字符
#     f.truncate(1)
#     print(f.read())

# seek()如果在操作文件爱你过程中,需要定位到其他位置进行操作 用seek()
# seek(offset,from)有两个参数,offset 偏移量单位字节,负数是往回偏移,正数是往前偏移,from位置:0表示文件开头,1表示当前位置,2表示文件末尾
