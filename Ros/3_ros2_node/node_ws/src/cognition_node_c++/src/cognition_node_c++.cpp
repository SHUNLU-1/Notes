#include "rclcpp/rclcpp.hpp"
int main(int argc,char **argv)
{
    rclcpp::init(argc, argv);
    /*产生一个Wang2的节点*/
    auto node = std::make_shared<rclcpp::Node>("cognition_node_c++");
    // 打印一句自我介绍
    RCLCPP_INFO(node->get_logger(), "大家好，我是c++.");
    /* 运行节点，并检测退出信号*/
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
