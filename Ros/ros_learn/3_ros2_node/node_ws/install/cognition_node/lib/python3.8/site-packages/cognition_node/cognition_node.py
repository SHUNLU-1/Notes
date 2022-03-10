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
    node = Node("node")  
    node.get_logger().info("hello everyone,welcome to cognition ros-node.")
    '''4.保持节点运行，检测是否收到退出指令（Ctrl+C）'''
    rclpy.spin(node) 
    '''5.关闭rclpy'''
    rclpy.shutdown() 



class WriterNode(Node):
    """
    创建一个作家节点，并在初始化时输出一个话
    """
    def __init__(self,name):
        super().__init__(name)
        self.get_logger().info("hello everyone,welcome to cognition ros-node.")


def main_oop(args=None):
    """
    ros2运行该节点的入口函数
    1. 导入库文件
    2. 初始化客户端库
    3. 新建节点
    4. spin循环节点
    5. 关闭客户端库
    """
    rclpy.init(args=args) 
    node = WriterNode("node")  
    rclpy.spin(node) 
    rclpy.shutdown() 
if __name__ == "__main__":
    main()
    #main_oop()