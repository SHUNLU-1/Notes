# 一、ROS2接口介绍
## 1、什么是接口
接口其实是一种规范
```c++
std_msgs/msg/String
std_msgs/msg/UInt32
```
##### 使用接口对做机器人有什么好处呢？

当机器人进行导航时，需要激光雷达的扫描数据，假如没有统一接口，每次更换一个种类的雷达，都需要重新做程序适配。
于是ROS2中定义了一个统一的接口叫做sensor_msgs/msg/LaserScan,现在几乎每个雷达的厂家都会编写程序将自己雷达的数据变成sensor_msgs/msg/LaserScan格式，提供给用户使用。
如果雷达的例子不好理解，大家可以把雷达换成手机充电器，USB接口是不是也是一种规范，所有的厂家都按照这种接口进行充电器和连接线的生产。

## 2.ROS2接口介绍

使用ros2 interface package sensor_msgs命令可以查看某一个接口包下所有的接口
```bash
ros2 interface package sensor_msgs
```
```bash
sensor_msgs/msg/JointState  #机器人关节数据
sensor_msgs/msg/Temperature #温度数据
sensor_msgs/msg/JoyFeedbackArray 
sensor_msgs/msg/Joy
sensor_msgs/msg/PointCloud2 #点云
sensor_msgs/msg/MultiEchoLaserScan 
sensor_msgs/msg/NavSatStatus 
sensor_msgs/msg/CameraInfo #相机信息
sensor_msgs/msg/Illuminance 
sensor_msgs/msg/MagneticField
sensor_msgs/srv/SetCameraInfo
sensor_msgs/msg/LaserEcho 
sensor_msgs/msg/RegionOfInterest
sensor_msgs/msg/PointCloud #点云
sensor_msgs/msg/Range #范围
sensor_msgs/msg/RelativeHumidity
sensor_msgs/msg/FluidPressure
sensor_msgs/msg/BatteryState
sensor_msgs/msg/Imu #加速度传感器
sensor_msgs/msg/Image #图像
sensor_msgs/msg/PointField
sensor_msgs/msg/JoyFeedback
sensor_msgs/msg/LaserScan #雷达数据
sensor_msgs/msg/MultiDOFJointState #多自由度关节数据
sensor_msgs/msg/TimeReference 
sensor_msgs/msg/CompressedImage #压缩图像
sensor_msgs/msg/NavSatFix 
sensor_msgs/msg/ChannelFloat32
```

## 3.ROS2自定义接口

ROS2提供了四种通信方式：

+ 话题-Topics
+ 服务-Services
+ 动作-Action
+ 参数-Parameters
除了参数之外，话题、服务和动作(Action)都支持自定义接口，每一种通信方式所适用的场景各不相同，所定义的接口也被分为话题接口、服务接口、动作接口三种。
这三种接口定义起来有什么不一样的地方呢？
+ 话题接口格式：xxx.msg
```c
int64 num
```
+ 服务接口格式：xxx.srv
```c
int64 a
int64 b
---
int64 sum
```
+ 动作接口格式：xxx.action
```c
int32 order
---
int32[] sequence
---
int32[] partial_sequence
```
我们只是简单的写了一下变量类型和名称，我们在程序里面怎么调用呢？其实这里有一个转换的过程：将msg、srv、action文件转换为Python和C++的头文件。
![2022-03-10_18-02.png](https://s2.loli.net/2022/03/10/mlMh5HsxNJzZP2n.png)
通过ROS2的IDL模块 产生了头文件，有了头文件，我们就可以在程序里导入并使用这个消息模块。

## 4.ROS2接口常用CLI命令

### 4.1查看接口列表（当前环境下）
```bash
ros2 interface list
```
![](https://fishros.com/d2lros2/chapt4/4.5ROS2%E9%80%9A%E4%BF%A1%E6%8E%A5%E5%8F%A3%E4%BB%8B%E7%BB%8D/imgs/image-20210809161530132.png)

### 4.2查看所有接口包

```bash
ros2 interface packages 
```
![](https://fishros.com/d2lros2/chapt4/4.5ROS2%E9%80%9A%E4%BF%A1%E6%8E%A5%E5%8F%A3%E4%BB%8B%E7%BB%8D/imgs/image-20210809161135322.png)

### 4.3查看某一个包下的所有接口

```bash
ros2 interface package std_msgs
```
![](https://fishros.com/d2lros2/chapt4/4.5ROS2%E9%80%9A%E4%BF%A1%E6%8E%A5%E5%8F%A3%E4%BB%8B%E7%BB%8D/imgs/image-20210809161840684.png)

### 4.4查看某一个接口详细的内容
```bash
ros2 interface show std_msgs/msg/String
```
![](https://fishros.com/d2lros2/chapt4/4.5ROS2%E9%80%9A%E4%BF%A1%E6%8E%A5%E5%8F%A3%E4%BB%8B%E7%BB%8D/imgs/image-20210809161933104.png)

### 4.5 输出某一个接口所有属性
```bash
ros2 interface proto sensor_msgs/msg/Image
```
![](https://fishros.com/d2lros2/chapt4/4.5ROS2%E9%80%9A%E4%BF%A1%E6%8E%A5%E5%8F%A3%E4%BB%8B%E7%BB%8D/imgs/image-20210809162247422.png)

# 二、自定义话题接口

## 1.如何自定义话题接口
话题是一种单向通信的接口，同一个话题只能由发布者将数据传递给订阅者，所以定义话题接口也只需要定义发布者所要发布的类型即可。在实际的工程当中，为了减少功能包互相之间的依赖，通常会将接口定义在一个独立的功能包中。有了功能包之后，我们就可以新建话题接口了，新建方法如下：

+ 新建msg文件夹，并在文件夹下新建xxx.msg
+ 在xxx.msg下编写消息内容并保存
+ 在CmakeLists.txt添加依赖和msg文件目录
+ 在package.xml中添加xxx.msg所需的依赖
+ 编译功能包即可生成python与c++头文件

## 2.开始动手
### 2.1新建工作空间
在town_ws的src文件夹下，运行下面的指令，即可完成village_interfaces功能包的创建。(注意，这里包的编译类型我们使用ament_cmake方式。)
```bash
ros2 pkg create village_interfaces --build-type ament_cmake 
```
![](https://fishros.com/d2lros2/chapt4/4.6ROS2%E8%87%AA%E5%AE%9A%E4%B9%89%E8%AF%9D%E9%A2%98%E6%8E%A5%E5%8F%A3/imgs/image-20210808134100725.png)

### 2.2 新建msg文件夹和Novel.msg(小说消息)
进入village_interfaces下，运行下面的命令：
```bash
cd village_interfaces && mkdir msg && touch Novel.msg 
```

### 2.3编写Novel.msg内容

我们的目的是给李四的小说每一章增加一张图片，原来李四写小说是对外发布一个std_msgs/msg/String字符串类型的数据。
而发布图片的格式，我们需要采用ros自带的传感器消息接口中的图片sensor_msgs/msg/Image数据类型，所以我们新的消息文件的内容就是将两者合并，在ROS2中可以写做这样：
```c
# 标准消息接口std_msgs下的String类型
std_msgs/String content
# 图像消息，调用sensor_msgs下的Image类型
sensor_msgs/Image image
```
这种组合结构图如下：

![2022-03-10_18-16.png](https://s2.loli.net/2022/03/10/1lZqr5w3PbEyuXx.png)

这个图一共三层，第一层是消息定义层，第二层是ROS2已有的std_msgs,sensor_msgs，其组成关系是由下一层组合成上一层。
最下面一层string、uint8、uint32是ROS2中的原始数据类型，原始数据类型有下面几种，ROS2中所有的接口都是由这些原始数据类型组成。
```c
bool
byte
char
float32,float64
int8,uint8
int16,uint16
int32,uint32
int64,uint64
string
```
#### 2.3.1 另一种写法
除了上面一种写法外，还有一种编写方式，那就是采用ROS2的原始类型来组合。 其实很简单，我们不使用std_msgs/String 而是直接使用最下面一层的string。

结构图就变成了这样子：
![2022-03-10_18-19.png](https://s2.loli.net/2022/03/10/r9EWmRZGdXyIBLw.png)

文件内容也变成了这样子：
```c
# 直接使用ROS2原始的数据类型
string content
# 图像消息，调用sensor_msgs下的Image类型
sensor_msgs/Image image
```
#### 2.3.2 说明
std_msgs/String是由基础数据类型string组成的，其实可以通过下面的指令来查看
```bash
ros2 interface show std_msgs/msg/String
```
结果如下：
```c
string data
```
原来std_msgs的String就是包含一个叫变量名为data的string类型变量，
```python
from std_msgs.msg import String
msg = String()
msg.data = '第%d回：潋滟湖 %d 次偶遇胡艳娘' % (self.i,self.i)
# msg 是 std_msgs.msg.String() 的对象
# msg.data data是string类型的对象，其定义是string data
```
#### 2.3.3 两种写法选哪一种
选择第二种，所以最后我们的Novel.msg文件内容如下：
```c
# 直接使用ROS2原始的数据类型
string content
# 图像消息，调用sensor_msgs下的Image类型
sensor_msgs/Image image
```
### 2.4 修改CMakeLists.txt
完成了代码的编写还不够，我们还需要在CMakeLists.txt中告诉编译器，你要给我把Novel.msg转换成Python库和C++的头文件。
大家直接添加下面的代码到CMakeLists.txt即可。

```c
#添加对sensor_msgs的
find_package(sensor_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
#添加消息文件和依赖
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Novel.msg"
   DEPENDENCIES sensor_msgs
 )
```
### 2.5 修改package.xml
修改village_interfaces目录下的package.xml，添加下面三行代码，为工程添加一下所需的依赖。
```xml
<depend>sensor_msgs</depend>
<build_depend>rosidl_default_generators</build_depend>
<exec_depend>rosidl_default_runtime</exec_depend>
<member_of_group>rosidl_interface_packages</member_of_group>
```
### 2.6 编译
```bash
colcon build --packages-select village_interfaces
```
### 2.7 验证
```bash
source install/setup.bash 
ros2 interface package village_interfaces  #查看包下所有接口
ros2 interface show village_interfaces/msg/Novel #查看内容
ros2 interface proto village_interfaces/msg/Novel #显示属性
```















