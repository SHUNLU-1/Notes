# 8. 理解参数（Parameter）

参数也是ROS2中很重要的一个概念，主要作用是对节点功能的配置，在ROS2中，每个节点都有自己的参数，这些参数可以用整型数、浮点数、布尔型数、字符串和列表来描述。   依然是以小海龟仿真器为例，看看里边有哪些参数。  
## 1.启动小海龟仿真器
熟悉的两行命令：
```bash
ros2 run turtlesim turtlesim_node
ros2 run turtlesim turtle_teleop_key
```
## 2.查看系统中的参数列表
来看看当前运行的系统中，有哪些参数：
```bash
ros2 param list
```
终端中可以看到，以每个节点名为命名空间，每个节点都有一些参数：  

![](https://www.guyuehome.com/Uploads/wp/2020/08/47b06d490349139a08-11-15-37-46.png)

比如turtlesim节点中有三个rgb参数，可以用来设置海龟仿真器的背景颜色。  
## 3.获取参数值
在以上列表中，如果我们想查看某个参数的值，就可以这样来操作：
```bash
ros2 param get <node_name> <parameter_name>
```  
比如看下背景颜色中的g值：
```bash
ros2 param get /turtlesim background_g
```
可以看到如下反馈，是一个整型数：  

![](https://www.guyuehome.com/Uploads/wp/2020/08/84bb1416fbbbc28708-11-15-37-46.png)

## 4.设置参数值
除了查看参数值之外，还可以通过命令行设置某一个参数的值：
```bash
ros2 param set <node_name> <parameter_name> <value>
```
比如修改仿真器背景色中的r值为150：
```bash
ros2 param set /turtlesim background_r 150
```
终端中会看到设置成功的日志，仿真器的背景也很快变色了：  

![](https://www.guyuehome.com/Uploads/wp/2020/08/cb2fd1afdd85897808-11-15-37-46.png)

![](https://www.guyuehome.com/Uploads/wp/2020/08/1ea9015fb5f15f9108-11-15-37-46.png)

这种方式只能修改一次参数值，下次重新启动就失效了，如果要下次继续生效，就得保存参数了。  

## 5.保存参数
我们可以使用dump命令来保存节点所有的参数到文件中：
```bash
ros2 param dump <node_name>
```
比如保存turtlesim节点的参数：
```bash
ros2 param dump /turtlesim
```
终端中可以看到保存成功的提示：  

![](https://www.guyuehome.com/Uploads/wp/2020/08/0d4c0d7dbb44415d08-11-15-37-46.png)

很快就可以在你运行终端的路径下看到保存好的文件啦，打开之后的内容如下：  

![](https://www.guyuehome.com/Uploads/wp/2020/08/c17c6c893189b4f808-11-15-37-46.png)

## 6.加载参数文件
保存好的参数文件可以在下次启动时加载使用：
```bash
ros2 run <package_name> <executable_name> --ros-args --params-file <file_name>
```
关掉已经在运行的海龟仿真器，重新启动来加载在启动海龟仿真器时，前边的命令不变，但是后边需要加上ros-args和--params-file配置：
```bash
ros2 run turtlesim turtlesim_node --ros-args --params-file ./turtlesim.yaml
```
海龟仿真器又启动啦，这回背景是不是变成了之前修改的颜色。   这就是ROS2中的参数，我们可以通过命令行get或set参数值，还可以利用文件保存和加载参数。  

# 二、理解动作（Action）

之前介绍到的话题和服务是ROS中最重要的两种底层通信机制，但也并不是说能解决所有应用层的问题，举一个例子，如果要让机械臂抓取一个物体，我们不仅要发出指令，还需要获取机械臂的实时反馈，如果直接用话题和服务也可以实现，不过一下得上好几个，有点麻烦。   所以针对类似的场景，ROS推出了一个应用级的通信机制——动作（action），主要结局需要运行一段时间的机器人任务。action也并不是一个全新的机制，而是由底层的三个话题和服务组成：一个任务目标（Goal，服务），一个执行结果（Result，服务），周期数据反馈（Feedback，话题）。   action是可抢占式的，由于需要执行一段时间，比如执行过程中你不想跑了，那可以随时发送取消指令，动作终止，如果执行过程中发送一个新的action目标，则会直接中断上一个目标开始执行最新的任务目标。   总体上来讲，action是一个客户端/服务器的通信模型，客户端发送一个任务目标，服务器端根据收到的目标执行并周期反馈状态，执行完成后反馈一个执行结果。  

![](https://www.guyuehome.com/Uploads/wp/2020/08/2e0d5c184fe4001108-11-17-09-18.gif)

依然是以小海龟仿真器为例来进一步理解action的概念。  
## 1.启动小海龟仿真器
```bash
ros2 run turtlesim turtlesim_node
ros2 run turtlesim turtle_teleop_key
``` 
## 2.使用action
在启动键盘控制节点的终端中，可以看到如下日志提示：  

![](https://www.guyuehome.com/Uploads/wp/2020/08/a52cffd2e4f695ee08-11-17-09-18.png)

之前我们都是使用键盘的上下左右按键发布话题指令来控制小海龟移动的，以上第二行信息提示的指令，则是通过action来控制海龟转动到指定方向的。   按键 G|B|V|C|D|E|R|T 都是围绕“F”的，以“F”为中心，对应方向的按键就表示控制小海龟的转动到的方向，比如按下“E”，小海龟就会转动到朝向左上方。   仔细观察小海龟仿真器，每当按下以上一个按键，相当于从客户端发送了一个action的任务目标，海龟仿真器后台运行的服务器端接收到之后就会开始执行，执行完成后反馈给客户端类似下边的结果：

![](https://www.guyuehome.com/Uploads/wp/2020/08/9507c218027e95ce08-11-17-09-18.png)

“F”按键就是用来发送action终止指令的。假设你先按下了“C”，小海龟开始执行action，此时按下“F”，两个终端中都会看到：

![](https://www.guyuehome.com/Uploads/wp/2020/08/1ca3de757c17829e08-11-17-09-18.png)

再来试试先按下“D”，在完成action前按下“G”，这时终端中会提示：  

![](https://www.guyuehome.com/Uploads/wp/2020/08/70e777c1e8d41ae308-11-17-09-18.png)

没错，action是抢占式的，后一个action的执行直接中断了前一个action的执行。  

## 3.查看节点信息
我们来看下海龟仿真器节点有哪些action：
```bash
ros2 node info /turtlesim
```
![](https://www.guyuehome.com/Uploads/wp/2020/08/710fd713f4087a9608-11-17-09-18.png)

从反馈的信息列表中，我们可以看到所有仿真器中的订阅者、发布者、服务、动作服务器和客户端。   Action Servers 中可以看到有一个动作服务器 /turtle1/rotate_absolute。   再来看看键盘控制节点的信息：
```bash
ros2 node info /teleop_turtle
```
![](https://www.guyuehome.com/Uploads/wp/2020/08/7d63de0b87f049c708-11-17-09-18.png)

在Action Clients中有同名的动作客户端/turtle1/rotate_absolute。   可见，键盘控制节点发送action目标，海龟仿真器执行action并反馈，action名为/turtle1/rotate_absolute。  

## 4.查看action列表
action也可以类似话题服务一样查看：
```bash
ros2 action list
```
在海龟仿真器系统中，可以看到：  

![](https://www.guyuehome.com/Uploads/wp/2020/08/c6f441571987c5de08-11-17-09-18.png)

如果想要看到更详细的action数据类型，需要加入-t参数：
```bash
ros2 action list -t
```
看到的信息就是这样啦：  

![](https://www.guyuehome.com/Uploads/wp/2020/08/e61fc83d13fa9dae08-11-17-09-18.png)

这里的 turtlesim/action/RotateAbsolute 就是action的数据类型，当我们通过终端发送action指令时，这个数据类型就可以知道我们如何发送具体的数据了。  

## 5.查看action的信息
从list列表中看到的action可以用如下命令查看详情：
```bash
ros2 action info /turtle1/rotate_absolute
```
看到的结果如下：  

![](https://www.guyuehome.com/Uploads/wp/2020/08/da1a38a7e71ada7b08-11-17-09-18.png)

这里可以看到提供该action的服务器和客户端的数量。  

## 6.查看action数据类型
如果我们想发送一个action的目标goal，就需要知道action的具体数据类型和数据结构，刚才我们已经看到/turtle1/rotate_absolute的数据类型是turtlesim/action/RotateAbsolute ，那这个数据类型的具体数据结构是什么样的呢？可以这样看到：
```bash
ros2 interface show turtlesim/action/RotateAbsolute.action
```
![](https://www.guyuehome.com/Uploads/wp/2020/08/58327d86e2a8719308-11-17-09-18.png)

有点像service的数据结构，只不过有两个“---”将数据分成了三段，第一段描述客户端发送的请求目标，第二段描述的是action执行完成后的反馈结果，第三段描述的是action执行过程中的周期反馈。 

## 7.命令行发送action目标
终于可以发布action目标了，了解下命令行下发送goal的格式：
```bash
ros2 action send_goal <action_name> <action_type> <values>
```
<values>同样是YAML格式描述的数据。发送一个试试：
```bash
ros2 action send_goal /turtle1/rotate_absolute turtlesim/action/RotateAbsolute "{theta: 1.57}"
```
小海龟开始转动啦，终端中会显示：  

![](https://www.guyuehome.com/Uploads/wp/2020/08/624a26f3714bfb0e08-11-17-09-18.png)

从以上信息我们可以看到，每一个action目标都有一个唯一的ID。   如果先要看到action中的周期反馈，以上命令还需要加一个--feedback参数：
```bash
ros2 action send_goal /turtle1/rotate_absolute turtlesim/action/RotateAbsolute "{theta: -1.57}" --feedback
```
这时的终端信息是这样的： 

![](https://www.guyuehome.com/Uploads/wp/2020/08/3ccf8221bf268abd08-11-17-09-18.png)

在action执行完成前，终端中会不断周期刷新类似反馈信息。  










