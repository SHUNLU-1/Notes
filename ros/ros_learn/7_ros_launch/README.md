# 创建一个launch文件

 
```python
# 导入库
from launch import LaunchDescription
from launch_ros.actions import Node

# 定义函数名称为：generate_launch_description
def generate_launch_description():


    # 创建Actions.Node对象li_node，标明李四所在位置
    li4_node = Node(
        package="village_li",
        executable="li4_node",
        output='screen',  #四个可选项 
        parameters=[{'write_timer_period': 1}]
        )
    # 创建Actions.Node对象wang2_node，标明王二所在位置
    wang2_node = Node(
        package="village_wang",
        executable="wang2_node",
        parameters=[{'novel_price': 2}]
        )

    # 创建另外一个命名空间下的，创建Actions.Node对象li_node，标明李四所在位置
    li4_node2 = Node(
        package="village_li",
        namespace="mirror_town",
        executable="li4_node",
        parameters=[{'write_timer_period': 2}]
    )
    # 创建另外一个命名空间下的，Actions.Node对象wang2_node，标明王二所在位置
    wang2_node2 = Node(
        package="village_wang",
        namespace="mirror_town",
        executable="wang2_node",
        parameters=[{'novel_price': 1}]
    )

    # 创建LaunchDescription对象launch_description,用于描述launch文件
    launch_description = LaunchDescription([li4_node,wang2_node,wang2_node2,li4_node2])
    # 返回让ROS2根据launch描述执行节点
    return launch_description
```

+ 类似python程序一样，一上来就得引用需要的模块。
```python
from launch import LaunchDescription
from launch_ros.actions import Node
```
+ 接下来是launch文件起始的描述，在 LaunchDescription 中描述了节点的启动。  
```python
def generate_launch_description():
   return LaunchDescription([


   ])
```
+ 这是节点的描述，可以看到除了命名空间之外，其他的内容都是一样的，package表示节点所在的功能包，executable表示要运行的可执行文件名，name表示启动后的节点名。    
```python
# 创建Actions.Node对象li_node，标明李四所在位置
li4_node = Node(
    package="village_li",
    executable="li4_node",
    output='screen',  #四个可选项 
    parameters=[{'write_timer_period': 1}]
    )
```    