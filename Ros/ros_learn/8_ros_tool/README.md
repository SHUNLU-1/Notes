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
2.选择一个话题
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

3.ros2 bag录制话题数据
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

4.查看数据库文件
我们可以使用这个命令查看数据库文件的信息：
```bash
ros2 bag info <bag_file_name>
```
以刚才的subset文件为例，可以看到：  

![](https://www.guyuehome.com/Uploads/wp/2020/08/b7ac5a828353b3d508-17-09-08-40.png)

可以看到这里使用的是sqlite3 数据库保存了话题数据。  
5.ros2 bag回放数据
关闭之前运行的键盘控制节点，确保目前是没有任何节点发送海龟运行指令的，接下使用如下命令回放录制好的数据：
```bash
ros2 bag play subset
```
终端中会提示：

![](https://www.guyuehome.com/Uploads/wp/2020/08/222fe0efecc553d608-17-09-08-40.png)

小海龟仿真器中可以看到海龟按照之前控制的指令在运动。  

![](https://www.guyuehome.com/Uploads/wp/2020/08/660ff36214e0bbd508-17-09-08-40.png)

这就是ROS2中录制数据集的神器——ros2 bag，我们可以通过这种方式和别人分享自己的工作成果嘞！  


