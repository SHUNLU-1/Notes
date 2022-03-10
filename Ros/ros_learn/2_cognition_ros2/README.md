# Configure Ros(小海龟仿真器基础使用)
## 1.安装海龟仿真器
```bash
sudo apt update
sudo apt install ros-foxy-turtlesim
```
如果你不确定是否安装成功，可以使用该命令检查：
```bash
ros2 pkg executables turtlesim
```
看到如下内容说明安装成功：

![](https://www.guyuehome.com/Uploads/wp/2020/08/993c2d0dbc1513a408-04-14-31-51.png)

## 2. 启动海龟仿真器

终端中输入如下命令启动海龟仿真器：
```bash
ros2 run turtlesim turtlesim_node
```
很快可以看到一个打开的仿真器界面，里边会随机使用一个ROS2的logo作为显示海龟的位置：

![](https://www.guyuehome.com/Uploads/wp/2020/08/4f90f61a25adb37e08-04-14-31-51.png)

终端中可以看到海龟的名字和在仿真器坐标系下的位置：

![](https://www.guyuehome.com/Uploads/wp/2020/08/970eaab5207f49b808-04-14-31-51.png)

接下来让海龟动起来，打开一个新的终端，输入如下命令：
```bash
ros2 run turtlesim turtle_teleop_key
```
然后根据终端中的提示点击键盘按键，即可控制小海龟运动啦，注意一定要让键盘控制节点在激活状态：  
![](https://www.guyuehome.com/Uploads/wp/2020/08/23a0b247dab463c008-04-14-31-51.png)

我们可以使用如下命令看看小海龟后台到底运行了哪些功能：
```bash
ros2 node list
ros2 topic list
ros2 service list
ros2 action list
```
![](https://www.guyuehome.com/Uploads/wp/2020/08/252e856ebd90607a08-04-14-31-51.png)

## 3、安装rqt工具
```bash
sudo apt update
sudo apt install ~nros-foxy-rqt*
```
默认已经安装   安装完成后使用如下命令运行：
rqt
第一次打开的界面是空的，选择Plugins > Services > Service Caller   这个插件是用来发布服务请求的，点击刷新按键之后，可以看到系统当前的所有服务。  
![](https://www.guyuehome.com/Uploads/wp/2020/08/c622cf8498b4151908-04-14-31-51.png)

选择/spawn服务，双击下边的数据项，填写新产生海龟的名字和位置，然后点击“Call”，即可发送服务请求。注意名字一定不能和已有的海龟名字一样，不然会有报错。  
![](https://www.guyuehome.com/Uploads/wp/2020/08/6edc85b856352a6e08-04-14-31-51.png)

很快就可以在海龟仿真器当中看到另外一只海龟啦！  
![](https://www.guyuehome.com/Uploads/wp/2020/08/87cabe17303291c508-04-14-31-51.png)

产生的不仅是一只新的海龟，还会有“turtle2”对应的话题、服务，可以说和turtle1是功能完全一样的两只海龟。   还可以尝试另外一个服务/set_pen，通过设置画笔，调整海龟轨迹的颜色。如下图所示，设置画笔的rgb值和宽度，点击“Call”之后，再运动海龟就可以看到全新的轨迹效果啦。  
![](https://www.guyuehome.com/Uploads/wp/2020/08/142ac61d88e8909708-04-14-31-51.png)

大家一定会有一个问题，第二只海龟如何运动呢？仿真器默认的键盘控制节点只能发布turtle1的话题，但是通过ROS的重映射（remapping）机制，可以实现对话题的重新命名。   在一个新的终端中输入如下指令：
```bash
ros2 run turtlesim turtle_teleop_key --ros-args --remap turtle1/cmd_vel:=turtle2/cmd_vel
```
这里就把turtle1/cmd_vel这个话题名更改为了turtle2/cmd_vel，现在该节点就可以控制turtle2啦，不信在该终端中点击键盘试一下。  
![](https://www.guyuehome.com/Uploads/wp/2020/08/eed7a26f34e537ce08-04-14-31-51.png)

[参考链接](https://index.ros.org/doc/ros2/Tutorials/Turtlesim/Introducing-Turtlesim/)










