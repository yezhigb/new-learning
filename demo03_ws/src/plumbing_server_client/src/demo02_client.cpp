#include "ros/ros.h"
#include "plumbing_server_client/AddInts.h"
/*
    客户端：提交两个整数，并处理响应结果
        1.包含头文件；
        2.初始化 ROS 节点；
        3.创建节点句柄；
        4.创建一个客户端对象；
        5.提交请求并处理响应；
        6.spin()。（客户端中没有回调函数，此处可有可无）
    实现参数的动态提交：
        1.格式：rosrun 包名 节点名称 12 34
        2.节点执行时，需要获取命令中的参数，并组织进 request
*/
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    // 优化实现，获取命令中的参数
    if(argc != 3)
    {
        ROS_INFO("提交的参数个数有误");
        return 1;
    }
    
    // 2.初始化 ROS 节点；
    ros::init(argc,argv,"YongHu");
    // 3.创建节点句柄；
    ros::NodeHandle nh;
    // 4.创建一个客户端对象；
    ros::ServiceClient client = nh.serviceClient<plumbing_server_client::AddInts>("addInts");
    // 5.提交请求并处理响应；
    plumbing_server_client::AddInts ai;
    // 5-1.组织请求
    ai.request.num1 = atoi(argv[1]);
    ai.request.num2 = atoi(argv[2]);
    // 5-2处理响应
    client.waitForExistence();
    bool flag = client.call(ai);
    if (flag)
    {
        ROS_INFO("响应成功！");
        // 获取结果
        ROS_INFO("响应结果 = %d",ai.response.sum);
    }
    else
    {
        ROS_INFO("处理失败....");
    }
    
    return 0;
}
