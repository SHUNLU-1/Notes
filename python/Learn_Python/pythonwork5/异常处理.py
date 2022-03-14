# 错误与异常处理
# try.....except语句
# import
try:
    b = 1
    print(b)  # 要检查捕获的代码
    li = [1, 2, 3, 4]
    print(li[10])
except NameError as msg:
    # 捕获到错误 才会在这里执行
    print(msg)
    pass
except IndexError as msg:
    # 捕获到错误 才会在这里执行
    print(msg)
    pass
except Exception as msg:
    # 捕获所有异常
    # 再次尽量去处理异常
    print(msg)
print('陈中伟是傻逼')

# try-except-else语句
try:
    a = 1
    print(a)
    pass
except Exception as msg:
    print(msg)
    pass
else:
    print('么有错误')
# finally 不管有没有错误都会执行

try:
    b = 1
    print(b)
    pass
except Exception as msg:
    print(msg)
    pass
else:
    print('么有错误')
    pass
finally:
    print('释放文件资源,数据库连接的资源等')
    print('不管有没有错误都去执行')

#  自定义异常


class NumErro(Exception):
    def __str__(self):
        return '你这个输入错误'
    pass


try:

    num = input('请输入一个数%d')

    def test_num(num):
        if num > 10:
            raise NumErro
        pass
    pass
except NumErro as msg:
    print(msg)

