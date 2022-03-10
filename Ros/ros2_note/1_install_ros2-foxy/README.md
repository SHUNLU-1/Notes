# 一、Ubuntu20.04安装ROS2 Foxy
[可以参考官方教程](https://index.ros.org/doc/ros2/Installation/Foxy/Linux-Install-Debians/)
## 1. 更换国内源
```bash
vi /etc/apt/sources.list
```
>deb http://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse
>deb-src http://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse
>deb http://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse
>deb-src http://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse
>deb http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse
>deb-src http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse
>deb http://mirrors.aliyun.com/ubuntu/ focal-proposed main restricted universe multiverse
>deb-src http://mirrors.aliyun.com/ubuntu/ focal-proposed main restricted universe multiverse
>deb http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse
>deb-src http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse

```bash
sudo apt-get update
sudo apt-get upgrade
```
## 2. 设置编码
```bash
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8
```
## 3.设置软件源
```bash
sudo apt update && sudo apt install curl gnupg2 lsb-release
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
 
sudo sh -c 'echo "deb [arch=$(dpkg --print-architecture)] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" > /etc/apt/sources.list.d/ros2-latest.list'
```
## 4.安装ROS2
```bash
sudo apt update
sudo apt install ros-foxy-desktop
```
## 5.设置环境变量
```bash
source /opt/ros/foxy/setup.bash
```
## 6.安装自动补全工具
```bash
sudo apt install python3-argcomplete
```
+ 跑几个例程测试一下：   先运行一个talker：
```bash
source /opt/ros/foxy/setup.bash
ros2 run demo_nodes_cpp talker
```
+ 再运行一个Listener
```bash
source /opt/ros/foxy/setup.bash
ros2 run demo_nodes_py listener
```
![](https://www.guyuehome.com/Uploads/wp/2020/08/621d2d003bc8070108-03-11-28-00.png)

ROS2的RWM默认使用的DDS是Fast RTPS，Cyclone DDS默认也安装好了，还可以这样安装RTI Connext：
```bash
sudo apt update
sudo apt install ros-foxy-rmw-connext-cpp # for RTI Connext (requires license agreement)
```
安装之后通过环境变量即可切换DDS：
RMW_IMPLEMENTATION=rmw_connext_cpp
 
如果哪一天不喜欢了，还可以这样删除：
```bash
sudo apt remove ros-foxy-* && sudo apt autoremove
```

# 二、Ubuntu20.04 安装 ROS1 Noetic
[可以参考官方教程](http://wiki.ros.org/noetic/Installation/Ubuntu)

## 2.1、设置你的sources.list
```bash
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
```
## 2.2、Set up your keys
```bash
sudo apt install curl # if you haven't already installed curl
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
```
## 2.3、Installation
+ Desktop-Full Install: (Recommended) : Everything in Desktop plus 2D/3D simulators and 2D/3D perception packages
```bash
sudo apt install ros-noetic-desktop-full
```
+ Desktop Install: Everything in ROS-Base plus tools like rqt and rviz
```bash
sudo apt install ros-noetic-desktop
```
+ ROS-Base: (Bare Bones) ROS packaging, build, and communication libraries. No GUI tools.
```bash
sudo apt install ros-noetic-ros-base
```
## 2.4、Environment setup
```bash
source /opt/ros/noetic/setup.bash
```
## 2.5、Dependencies for building packages

Up to now you have installed what you need to run the core ROS packages. To create and manage your own ROS workspaces, there are various tools and requirements that are distributed separately. For example, rosinstall is a frequently used command-line tool that enables you to easily download many source trees for ROS packages with one command.
To install this tool and other dependencies for building ROS packages, run:
```bash
sudo apt install python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential
```

Before you can use many ROS tools, you will need to initialize rosdep. rosdep enables you to easily install system dependencies for source you want to compile and is required to run some core components in ROS. If you have not yet installed rosdep, do so as follows.
```bash
sudo apt install python3-rosdep
```

With the following, you can initialize rosdep.
```bash
sudo rosdep init
rosdep update
```

# 三、ros1和ros2共存配置环境变量

```bash
sudo gedit ~/.bashrc
```
打开.bashrc文本文件后在末尾加上如下代码，完成环境变量设置。
```bash
#source /opt/ros/noetic/setup.bash
echo "ros noetic(1) or ros2 foxy(2)?"
read edition
if [ "$edition" -eq "1" ];then
  source /opt/ros/noetic/setup.bash
else
  source /opt/ros/foxy/setup.bash
fi
```