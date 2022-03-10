# 一、理解话题
大道至简，ROS2将复杂的机器人系统拆解成许多模块节点，而这些节点之间则是通过一个至关重要的通道完成数据交换的，这个通道就是“话题”。
![](https://www.guyuehome.com/Uploads/wp/2020/08/126444b0e548d78208-06-10-29-03.gif)
一个节点可以通过多个话题向外发布数据，也可以同时订阅多个其他节点发布的话题，相当于话题是一个多对多的订阅/发布模型。
![](https://www.guyuehome.com/Uploads/wp/2020/08/f2c987b3870cdf0808-06-10-29-03.gif)

### 1.启动小海龟仿真器
还是先来启动小海龟仿真器吧，相信你已经很熟练了：
```bash
ros2 run turtlesim turtlesim_node
ros2 run turtlesim turtle_teleop_key
```
没错，你现在应该可以用键盘控制小海龟移动啦。
### 2.rqt_graph
在ROS1中我们就极力推荐rqt_graph这个工具，可以从上帝视角看到整个系统的状态，ROS2中依然如此，我们还是使用这个工具来可视化显示节点和话题的连接关系。   在一个新的终端中，输入
```bash
rqt_graph
```
看到熟悉的界面，里边清晰的展示了ROS计算图的网络形态。 
![](https://www.guyuehome.com/Uploads/wp/2020/08/197e3a2e2eeb911d08-06-10-29-03.png)

先忽略图中的action，把鼠标放置到中间的话题上，可以立刻看到高亮效果，清晰的展示了该话题的发布者和订阅者。话题/turtle1/cmd_vel的发布者是teleop_turtle节点，而订阅者是turtlesim节点，这个话题中传输的数据就是我们按下键盘之后形成的速度指令。   在更加复杂的机器人系统中，rqt_graph工具可以帮助我们快速理清节点之间通过话题的牵连。  

### 3.ros2 topic list
当前系统中所有的话题如何查看呢，不如来试下这个命令：
```bash
ros2 topic list
```
不清楚这些话题传输的是什么数据，没问题，这个命令试一下：
```bash
ros2 topic list -t
```
这回我们不仅可以看到所有话题的列表，还可以清晰的看到每个话题传输的数据类型是什么。
### 4.ros2 topic echo
如果想看到节点之间的话题到底发了什么数据内容，可以这样：
```bash
ros2 topic echo <topic_name>
```
我们现在好奇键盘节点到底给小海龟发了什么，小海龟这么听话的动起来呢？
```bash
ros2 topic echo /turtle1/cmd_vel
```
输入之后可能暂时看不到任何内容，这是因为我们还没有发布数据，在运行键盘控制节点的终端中点击键盘，很快就可以看到数据啦：  
![](https://www.guyuehome.com/Uploads/wp/2020/08/b65141d3a66119e808-06-10-29-04.png)
原来键盘控制节点将点击的键盘按键变成了线速度和角速度，通过话题发送给海龟仿真器，海龟才动起来的。  
### 5.ros2 topic info
类似查看节点的详细信息一样，我们也可以用如下命令查看话题的详细信息：
```bash
ros2 topic info /turtle1/cmd_vel
```
就可以看到详细信息啦：  
![](https://www.guyuehome.com/Uploads/wp/2020/08/36e015f6026aecb608-06-10-29-04.png)

### 6.ros2 interface show
节点之间要想成功建立数据传输，必须发布和订阅同样数据类型的消息，发布者发布的是速度指令，订阅者想订阅位置信息可是行不通的。如何查看话题的数据类型呢？使用刚才说的这个命令就可以啦：
```bash
ros2 topic list -t
```
可以看到， cmd_vel 话题的消息类型是：**geometry_msgs/msg/Twist**
熟悉ROS1的小伙伴应该并不陌生，这就是在ROS中常用的标准速度指令，以上内容表示在geometry_msgs包的msg中有一个数据类型Twist。   这个数据类型的具体数据结构什么样的，继续通过如下指令看一下：
```bash
ros2 interface show geometry_msgs/msg/Twist
```
![](https://www.guyuehome.com/Uploads/wp/2020/08/21cde1cdc05a388008-06-10-29-04.png)
原来Twist中包含了两个三维向量，分别表示线速度和角速度。  

### 7.ros2 topic pub
现在我们了解了消息的结构，有没有可能直接通过命令行来发布一个话题消息呢？当然是可以的。
```bash
ros2 topic pub <topic_name> <msg_type> '<args>'
```
这里的 '<args>'就是具体的消息内容啦，我们需要使用YAML的语法来描述，比如要发布速度指令Twist:   --once表示这个消息只发布一次就退出。   终端中会出现如下提示：  
![](https://www.guyuehome.com/Uploads/wp/2020/08/449d8196f2568d0408-06-10-29-04.png)

小海龟也会动起来啦：
![](https://www.guyuehome.com/Uploads/wp/2020/08/9ae60bfa3f369f4808-06-10-29-04.png)

如果希望小海龟一直运动，那就得以某个频率持续发布：
```bash
ros2 topic pub --rate 1 /turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.8}}"
```
--rate参数就表示频率啦，单位是hz  
![](https://www.guyuehome.com/Uploads/wp/2020/08/4010c76cf62021c508-06-10-29-04.png)

### 8.ros2 topic hz
如果我们想查看某一个话题的发布频率，依然可以通过命令行来实现：
```bash
ros2 topic hz /turtle1/pose
```
很快就可以看到turtlesim节点发布pose话题的频率啦：  




