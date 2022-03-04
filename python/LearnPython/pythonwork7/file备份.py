# 文件的备份
import os
# def copyFile():
#     # 接受用户输入的文件名
#     old_file = input('请输入你要备份的文件名:')
#     file_list = old_file.split('.')
#     # 构造新的文件名.加上备份的后缀
#     new_file = file_list[0] + '_备份.'+file_list[1]
#     # 打开需要备份的文件
#     old_f = open(old_file, 'r')
#     # 以写的模式去打开新文件,不存在则创建
#     new_f = open(new_file, 'w')
#     # 将内容文件读取出来
#     content = old_f.read()
#     # 将文件内容读取出来
#     new_f.write(content)
#     # 将读取的内容写入到备份文件
#     old_f.close()
#     new_f.close()
#
#
# copyFile()

# 大文件读写备份
def copyFile():
    # 接受用户输入的文件名
    old_file = input('请输入你要备份的文件名:')
    file_list = old_file.split('.')
    # 构造新的文件名.加上备份的后缀
    new_file = file_list[0] + '_备份.' + file_list[1]
    # 将读取的内容写入到备份文件
    pass
    try:
        # 监视要处理的逻辑
        with open(old_file, 'r') as old_f, open(new_file, 'w')as new_f:
            # 一次性读取1024个字符
            while True:
                content = old_f.read(1024)
                new_f.write(content)
                if len(content) < 1024:
                    break
            pass
        pass
    except Exception as msg:
        print(msg)
        pass
    old_f.close()
    new_f.close()


copyFile()
