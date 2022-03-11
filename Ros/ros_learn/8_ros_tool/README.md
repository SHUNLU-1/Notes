# 一、 rqt_console工具的使用

在终端中运行ROS2节点时，节点的日志信息会在终端中显示出来，但是这种方式呈现的日志比较凌乱，所以ROS2提供了一个专门用于管理日志信息的可视化工具——rqt_console。今天我们就来看看这个工具是如何使用的。
## 1.启动
首先打开一个新的终端，使用如下指令即可启动rqt_console：  
```bash
ros2 run rqt_console rqt_console
```
![](https://www.guyuehome.com/Uploads/wp/2020/08/d87a031277ec3d6008-14-09-26-02.png)

在打开的窗口中，我们可以看到三个子窗口。最上边一个窗口会显示所有ROS2系统中的日志，是内容最多的，如果我们想做筛选，可以在中间的窗口中选择日志级别，此时中间窗口则会剔除无关级别的日志，如果我们想在日志中搜索某一字符串，那就可以在最下边的窗口中输入，确任后该窗口只显示包含此字符串的日志。中间和下边的窗口还可以添加更多筛选规则。   我们来启动小海龟仿真器试一试。  
ros2 run turtlesim turtlesim_node

## 2.在rqt_console中显示日志消息
为了产生日志信息，我们可以控制海龟撞到仿真器的边缘：  
```bash
ros2 topic pub -r 1 /turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0,y: 0.0,z: 0.0}}"
```
当海龟撞到边缘时，rqt_console中就会弹出很多警告信息：  

![](https://www.guyuehome.com/Uploads/wp/2020/08/6b705c2929f912db08-14-09-26-02.png)

## 3.日志级别
ROS2中的日志分成五个级别，级别自高到低分别是：  
+ Fatal：致命级，描述系统为了自我保护即将终止的消息
+ Error：错误级，描述非致命但是会阻碍程序运行的消息
+ Warn：警告级，描述不损坏功能运行但是预期之外的行为的消息
+ Info：信息级，描述系统正常运行时事件和状态消息
+ Debug：调试级，描述系统一步一步运行的详细消息
ROS2中默认开启的日志级别是Info，会自动显示info级别以上的所有日志，包括Info、Warn、Error、Fatal。   运行节点时，我们也可以修改允许发布的日志级别，比如我们只想显示Warn级别以上的日志，可以这样：  
```bash
ros2 run turtlesim turtlesim_node --ros-args --log-level WARN
```
这时启动的仿真器就只会向外发布Warn级别以上的日志了，Info和Debug级别的日志都是看不到的。   rqt_console工具可以帮助我们有效的查看机器人系统中的日志信息，提高调试、测试、开发的效率，快速找到你想要看到的日志。  

# 二、使用ros2 bag录制/回放数据

有的时候我们希望在别人已有的数据集上做开发，或者复现之前已经构建好的场景数据，这时候就可以用ROS2中的ros2 bag工具啦。   ros2 bag是一个命令行工具，可以实现对ROS2系统中话题数据的录制和回放，选定的数据会被打包放到一个数据库文件中，未来使用该工具即可按照时间轴回放所有话题数据。   在使用rosbag前，需要确认是否安装好了：
sudo apt-get install ros-<distro>-ros2bag ros-<distro>-rosbag2*
 
## 1.配置
还是以小海龟反仿真为例，我们尝试录制控制海龟运动的速度指令，并实现回放。  
```bash
ros2 run turtlesim turtlesim_node
ros2 run turtlesim turtle_teleop_key
```
接下来创建一个新的文件夹，未来保存数据库文件：  
```bash
mkdir bag_files
cd bag_files
```
## 2.选择一个话题
ros2 bag可以录制系统中发布的话题数据，所以我们先看下当前系统中有哪些话题：
```bash
ros2 topic list
```
![](https://www.guyuehome.com/Uploads/wp/2020/08/b401e4d6ebefca9f08-17-09-08-40.png)

我们已经知道， /turtle1/cmd_vel 话题是用来控制海龟运动的，如果监听该话题，并且通过键盘控制小海龟移动，就可以看到速度指令的消息啦：
```bash
ros2 topic echo /turtle1/cmd_vel
```
![](https://www.guyuehome.com/Uploads/wp/2020/08/765f0655e34ef70608-17-09-08-40.png)

## 3.ros2 bag录制话题数据
ros2 bag录制话题数据的命令是：
```bash
ros2 bag record <topic_name>
```
该命令会将数据保存在当前终端所在的路径下，所以最好先cd到刚才创建好的目录下，然后运行：
```bash
ros2 bag record /turtle1/cmd_vel
```
可以看到开始录制数据的日志提示：  

![](https://www.guyuehome.com/Uploads/wp/2020/08/8fb2142d36cf212d08-17-09-08-40.png)

现在ros2 bag已经开始在录制 /turtle1/cmd_vel 话题中的消息了，回到键盘控制的窗口，控制小海龟完成一些运动，怎么动没关系，重要的是要把这些移动的指令都录制下来。  

![](https://www.guyuehome.com/Uploads/wp/2020/08/c7a006f1a303530908-17-09-08-40.png)

完成录制后，在运行ros2 bag的终端中Ctrl+C即可停止录制，已经录制好的数据会保存在“ rosbag2_year_month_day-hour_minute_second”命名的文件中。   以上是录制一个话题数据的方法，如果我们想录制多个话题的消息呢？可以这样：
```bash
ros2 bag record -o subset /turtle1/cmd_vel /turtle1/pose
```
-o参数是用来设置数据库文件名的，此时文件名叫subset。多个话题名通过空格隔开就行，输入几个就会录制几个，录制时可以看到：  

![](https://www.guyuehome.com/Uploads/wp/2020/08/28e14ed649cff48908-17-09-08-40.png)

## 4.查看数据库文件
我们可以使用这个命令查看数据库文件的信息：
```bash
ros2 bag info <bag_file_name>
```
以刚才的subset文件为例，可以看到：  

![](https://www.guyuehome.com/Uploads/wp/2020/08/b7ac5a828353b3d508-17-09-08-40.png)

可以看到这里使用的是sqlite3 数据库保存了话题数据。  
## 5.ros2 bag回放数据
关闭之前运行的键盘控制节点，确保目前是没有任何节点发送海龟运行指令的，接下使用如下命令回放录制好的数据：
```bash
ros2 bag play subset
```
终端中会提示：

![](https://www.guyuehome.com/Uploads/wp/2020/08/222fe0efecc553d608-17-09-08-40.png)

小海龟仿真器中可以看到海龟按照之前控制的指令在运动。  

![](https://www.guyuehome.com/Uploads/wp/2020/08/660ff36214e0bbd508-17-09-08-40.png)

这就是ROS2中录制数据集的神器——ros2 bag，我们可以通过这种方式和别人分享自己的工作成果嘞！  

# 三、RVIZ2

## 1.RVIZ2是什么
RVIZ2是ROS2中的一个非常重要且常用的数据可视化工具。

那数据指的是什么数据？可视化又是怎么可视化的？RVIZ2又是如何实现不同数据的可视化的呢？

答案如下：

数据：各种调试机器人时常用的数据，比如：图像数据、三维点云数据、地图数据、TF数据，机器人模型数据等等
可视化：可视化就是让你直观的看到数据，比如说一个三维的点(100,100,100),通过RVIZ可以将其显示在空间中
如何做到不同数据的可视化：强大的插件，如果没有你的数据，你可以自己再写一个插件，即插即用，方便快捷


## 2.RVIZ2 基础配置
#### 2.1 全局配置

![](https://fishros.com/d2lros2/chapt6/6.4RVIZ2/imgs/6a8c3220a2c643e184269bddcc2eae2b.png)

+ Fixed Frame：所有帧参考的帧的名称，坐标都是相对的，这个就是告诉RVIZ你是相对谁的，一般是设置成map或者odom
+ Frame Rate：用于设置更新 3D 视图的最大频率。

## 2.2 网格
用于可视化通常与地板平面相关联的网格

![](https://fishros.com/d2lros2/chapt6/6.4RVIZ2/imgs/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA6bG86aaZUk9T,size_16,color_FFFFFF,t_70,g_se,x_16.png)

+ Reference frame：帧用作网格坐标参考（通常：）
+ Plane cell count: 单元格中网格的大小
+ Normal cell count：在沿垂直于叶栅平面的网格数（正常：0）
+ Cell size：每个网格单元的尺寸（以米为单位）
+ Plane：标识网格平面的两个轴

## 2.3 机器人模型
根据 URDF 模型的描述来可视化机器人的模型。

![2022-03-11_17-51.png](https://s2.loli.net/2022/03/11/lr3RLfwWI9Ht4CS.png)

+ Visual enabled: 启用/禁用模型的 3D 可视化
+ Description Source：机器人模型文件的来源，可以在File和Topic之间进行选择
+ Description Topic: 机器人模型文件所在的话题

## 2.4 TF

![](https://fishros.com/d2lros2/chapt6/6.4RVIZ2/imgs/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA6bG86aaZUk9T,size_20,color_FFFFFF,t_70,g_se,x_16.png)

+ Marker Scale: 将字和坐标系标识调整的小一些，使其更加可见且不那么混乱
+ Update interval：以秒为单位的TF广播更新时间
+ 最佳实践，勾选你想看的Frames，直观的看到两个坐标之间的关系

# Gazebo介绍

## 1.Gazebo VS Rviz2

RVIZ2是用来可视化数据的软件，核心要义是将数据展示出来（我们不生产数据只做数据的搬运工）。 而Gazebo是用于模拟真实环境生产数据的（我们不搬运数据只做数据的生产者）

所以Gazebo可以根据我们所提供的机器人模型文件，传感器配置参数，给机器人创造一个虚拟的环境，虚拟的电机和虚拟的传感器，并通过ROS/ROS2的相关功能包把传感器数据电机数据等发送出来（生产数据）。

## 2.Gazebo集成ROS2
Gazebo 是一个独立的应用程序，可以独立于 ROS 或 ROS2 使用。

Gazebo与ROS 版本的集成是通过一组叫做gazebo_ros_pkgs的包 完成的，gazebo_ros_pkgs将Gazebo和ROS2连接起来。

![](![2022-03-11_17-52.png](https://s2.loli.net/2022/03/11/eV2vE9R34rjInaA.png))


## 2.1 gazebo_ros_pkgs

gazebo_ros_pkgs不是一个包，是一堆包如下：

+ gazebo_dev：开发Gazebo插件可以用的API
+ gazebo_msgs：定义的ROS2和Gazebo之间的接口（Topic/Service/Action）
+ gazebo_ros：提供方便的 C++ 类和函数，可供其他插件使用，例如转换和测试实用程序。它还提供了一些通常有用的插件。gazebo_ros::Node
+ gazebo_plugins：一系列 Gazebo 插件，将传感器和其他功能暴露给 ROS2 例如: gazebo_ros_camera 发布ROS2图像 gazebo_ros_diff_drive 通过ROS2控制和获取两轮驱动机器人的接口 

ROS1的插件迁移到ROS2进度：https://github.com/ros-simulation/gazebo_ros_pkgs/wiki

![](https://fishros.com/d2lros2/chapt6/6.5Gazebo%E4%BB%8B%E7%BB%8D/imgs/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA6bG86aaZUk9T,size_20,color_FFFFFF,t_70,g_se,x_16.png)

3. 两轮差速小demo
3.1安装gazebo
因为安装ROS2不会默认安装gazebo，所以我们要手动安装,一行命令很简单，如果提示找不到先去更新下ROS2的源。
```bash
sudo apt install gazebo11
```
## 3.2 安装ROS2的两轮差速功能包
```bash
sudo apt install ros-foxy-gazebo-*
```
## 3.3 运行两轮差速demo
```bash
gazebo /opt/ros/foxy/share/gazebo_plugins/worlds/gazebo_ros_diff_drive_demo.world 
```
![](https://fishros.com/d2lros2/chapt6/6.5Gazebo%E4%BB%8B%E7%BB%8D/imgs/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA6bG86aaZUk9T,size_20,color_FFFFFF,t_70,g_se,x_16.png)


## 3.4 查看话题
通过下面的指令可看到话题和话题的类型，把目光放到这个话题/demo/cmd_demo,下面我们就通过这个话题来控制小车动起来。
```bash
ros2@ros2-TM1613R:~$ ros2 topic list -t
/clock [rosgraph_msgs/msg/Clock]
/demo/cmd_demo [geometry_msgs/msg/Twist]
/demo/odom_demo [nav_msgs/msg/Odometry]
/parameter_events [rcl_interfaces/msg/ParameterEvent]
/rosout [rcl_interfaces/msg/Log]
/tf [tf2_msgs/msg/TFMessage]
```
## 3.5 让小车前进
```bash
ros2 topic pub /demo/cmd_demo geometry_msgs/msg/Twist "{linear: {x: 0.2,y: 0,z: 0},angular: {x: 0,y: 0,z: 0}}"
```
![](https://fishros.com/d2lros2/chapt6/6.5Gazebo%E4%BB%8B%E7%BB%8D/imgs/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA6bG86aaZUk9T,size_20,color_FFFFFF,t_70,g_se,x_16.png)
