# 理解节点（Node）

和ROS1一样，ROS2中的各项资源也是通过计算图（“ ROS (2) graph”）联系到一起的。计算图是一个由各种ROS2元素组成的网络，共同完成数据的传输，其中每一个完成具体功能的模块称之为“节点”（Node），例如控制车轮速度、获取雷达数据等，节点之间通过话题（Topic）、服务（Service）、动作（Actions）或者参数（Parameter）实现数据的收发。  
![](https://www.guyuehome.com/Uploads/wp/2020/08/93cd772c65f6390f08-05-14-01-53.gif)
一个完整的机器人系统就是由多个节点组成的，每个节点各司其职，完成自己的工作。在ROS2中，每一个可执行程序（C++、Python）可以包含1个或者多个节点，这是与ROS1中不同的。   
## 1.ros2 run
```bash
ros2 run turtlesim turtlesim_node
```  
很快就可以看到显示有小海龟的界面啦。  
![](https://www.guyuehome.com/Uploads/wp/2020/08/67a063395c45c77a08-05-14-01-53.png)

但是大家需要注意，这里的turtlesim_node只是可执行文件的名字，并不是节点名，想要知道节点叫什么，我们需要运行如下命令。

## 2.ros2 node list
ros2 node list可以显示当前系统中运行的所有节点名称，相当于ROS1中的rosnode list，在很多我们需要调试的时候，这个命令还是很有用的。   启动海龟仿真器之后，打开一个终端输入如下指令：
```bash
ros2 node list
```  
很快就可以看到当前系统中有一个节点在运行：
![](https://www.guyuehome.com/Uploads/wp/2020/08/3d34c44327d13c5d08-05-14-01-53.png)

重新打开一个终端，我们再来启动键盘控制节点：
```bash
ros2 run turtlesim turtle_teleop_key
```
不出意外，重新运行ros2 node list之后，我们可以发现多了一个正在运行的节点： 
![](https://www.guyuehome.com/Uploads/wp/2020/08/5ad06c14e204c9d208-05-14-01-53.png)

## 2.1 重映射（Remapping）
又要提到重映射啦，ROS中的重映射机制可以帮助我们重定义节点的属性，比如节点名称、话题名称、服务名称等。比如我们想修改看到的节点名turtlesim，那就可以这样：
```bash
ros2 run turtlesim turtlesim_node --ros-args --remap __node:=my_turtle
```
此时，虽然你又打开了一个小海龟的仿真界面，但是和之前的仿真窗口并没有任何冲突，重新看下节点列表ros2 node list：  
![](https://www.guyuehome.com/Uploads/wp/2020/08/ffa4a92716e37e0608-05-14-01-53.png)
没错，之所以没有冲突，就是因为新启动的仿真节点叫做“my_turtle”,并不是默认的“turtlesim”。   大家需要记住这里remapping的基本方法，后边还会有更多种实现的方式。  

## 3.ros2 node info

我们还是不满足于仅仅看到节点的名字，如果想要了解节点的更多信息，那就得用这个命令了：
```bash
ros2 node info <node_name>
```
比如我想了解刚启动的my_turtle节点的更多信息：
```bash
ros2 node info /my_turtle
```
一下可以看到节点的很多信息，包括订阅者、发布者、服务、动作等等。 
![](https://www.guyuehome.com/Uploads/wp/2020/08/227e08c9dce0a06d08-05-14-01-53.png)
我们也可以用同样的方式查看任何节点的详细信息。   总结一下，节点是ROS系统中的基本元素，主要完成机器人系统中某项具体的任务。  

## 4、创建一个python功能包
### 4.1、创建工作空间
```bash
mkdir -p cognition_node/src
cd cognition_node/src
```
### 4.2、创建一个功能包

我们先讲一下如何创建一个名字叫做 cognition_node(python)版本的功能包。

```bash
ros2 pkg create cognition_node --build-type ament_python --dependencies rclpy
```
+ pkg create 是创建包的意思
+ --build-type 用来指定该包的编译类型，一共有三个可选项ament_python、ament_cmake、**cmake如果build-type什么都不写，ros2会默认类型为ament_cmake.**
+ --dependencies 指的是这个功能包的依赖，这里给了一个ros2的python客户端接口rclpy
### 4.3、创建节点文件

接下来我们开始编写一个python节点，首先在__init__.py同级别目录下创建一个叫做cognition_node.py的文件(在vscode中右击新建就行)。
编写ROS2节点的一般步骤

+ 1.导入库文件
+ 2.初始化客户端库
+ 3.新建节点
+ 4.spin循环节点
+ 5.关闭客户端库

```python
"""1. 导入库文件"""
import rclpy
from rclpy.node import Node

def main(args=None):
    """
    ros2运行该节点的入口函数
    编写ROS2节点的一般步骤
    1. 导入库文件
    2. 初始化客户端库
    3. 新建节点对象
    4. spin循环节点
    5. 关闭客户端库
    """
    '''2.初始化rclpy'''
    rclpy.init(args=args) 
    '''3.新建一个节点'''
    node = Node("li4")  
    node.get_logger().info("hello everyone,welcome to cognition ros-node.")
    '''4.保持节点运行，检测是否收到退出指令（Ctrl+C）'''
    rclpy.spin(node) 
    '''5.关闭rclpy'''
    rclpy.shutdown() 
```

接着修改 [setup.py]()

```bash
entry_points={
    'console_scripts': [
        "node = cognition_node.cognition_node:main"
    ],
},
```
编译运行节点
```bash
colcon build
```
source环境
```bash
source install/setup.bash
```
运行节点
```bash
ros2 run cognition_node node
```
## 4、创建一个c++功能包

创建c++功能包
```bash
ros2 pkg create village_wang --build-type ament_cmake --dependencies rclcpp
```
创建节点：在cognition_node_c++/src下新建cognition_node_c++.cpp
