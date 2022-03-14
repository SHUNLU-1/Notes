# argv 返回命令行参数是一个列表
# argparse模块 可以轻松编写用户友好的命令行界面 定义了所需要的参数
import sys
import argparse
# 创建一个解析器对象
parse = argparse.ArgumentParser(prog='my program')

# 添加必选参数
parse.add_argument('name', type=str, help=('你自己的名字'))
parse.add_argument('age', type=str, help=('你自己的年龄'))
# 添加可选参数
parse.add_argument('-s', '--sex', action='append', type=str, help=('你自己的性别'))
# 限定范围

# 添加位置参数[必选参数]
parse.add_argument('name', type=str, help='你自己的名字')
parse.add_argument('age', type=str, help='你自己的年龄')

# 限定一个范围
parse.add_argument('-s', '--sex', default='', type=str, help=('你自己的性别'))
print(parse.print_help())

result = parse.parse_args() # 开始解析参数
print(result)