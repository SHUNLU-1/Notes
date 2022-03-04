import os
import shutil
# 重命名
# os.rename('1.txt', 'test.txt')

# 删除一个文件(前提是必须有)
# os.remove('1.txt')

# 在当前位置创建一个文件夹 只能一级一级去建立 不能多级建立
# os.mkdir('')

# 创建多级目录
# os.makedirs('')

# 删除一个文件夹(只能删除空目录)
# os.rmdir('')

# 删除非空目录(shutil中的rmtree) 多级删除
# shutil.rmtree('')

# 获取当前的目录
# print(os.getcwd())

# 路径的拼接
# os.path.join(os.getcwd(), 'a')

# 获取python中的目录列表  (打印一级目录)  老版写法
listRs = os.listdir('')
for dirname in listRs:
    print(dirname)
# 现代版写法
# 去释放资源
with os.scandir('') as entries:
    for entry in entries:
        print(entry.name)
# 另一种写法
rs = os.scandir('')
print(rs)

#
basePath = ''
for entry in os.listdir(basePath):
    if os.path.isfile(os.path.join(basePath, entry)):
        print(entry)