# 文件打开与关闭 读写 保存
# 打开文件
# 使用open函数打开文件
# 默认的编码是中文编码gbk
# fileOpj = open('/home/ubuntu/PycharmProjects/LearnPython/pythonwork7/Test.txt', 'w',encoding='utf-8')
# # 开始操作 读或写
# fileOpj.write('haha')
# fileOpj.close()

# 以二进制个是去写入
# fileOpj = open('/home/ubuntu/PycharmProjects/LearnPython/pythonwork7/Test.txt', 'wb')
# fileOpj.write('大海'.encode('utf-8'))

# 文件的读取
# fileOpj = open('/home/ubuntu/PycharmProjects/LearnPython/pythonwork7/Test.txt', 'r')
# # 读几个
# f = fileOpj.read(1)
# # 读一行
# fl = fileOpj.readline()
# print(f)
# print(fl)
# # 记得关闭 要不内存溢出
# fileOpj.close()

# with上下文管理对象
# 优点 自动释放打开关联的对象
# with open('/home/ubuntu/PycharmProjects/LearnPython/pythonwork7/Test.txt', 'r') as f:
#     print(f.read())
