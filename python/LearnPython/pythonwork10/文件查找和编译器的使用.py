"""
文件查找
updatedb 刷新索引
which 用于查找并显示给定命令的绝对路径（依据环境变量查找）（只能查到到可执行文件）
echo $PATH 查看环境变量
whereis 查找命令的绝对路径 （只能用于程序的搜素）（依据环境变量查找）
locate 查找文件与目录（快速）在数据库中寻找
find 在一个目录及子目录下搜素文件
find -name 按名字查找 -size 按照文件大小 -user 按文件所属 -type 按照文件类型

grep 强大的搜索命令 可以使用正则表达式搜索文本
-E 选项使用正则表达式 grep +""(搜索内容)+路径
管道符 |
输出重定向 > 将输出定向到文件 新建文件加入
tr
>> 追加操作

文件打包
tar -cvf 打包文件
tar -xvf 解压（-C 指定文件夹）
gzip  完成打包压缩  .gz(为后缀)
tar -zxvf 解压
bzip2  .bz2（为后缀）
tar -jxvf （解压）
"""

