# Ubuntu20.04安装ROS2 Foxy
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