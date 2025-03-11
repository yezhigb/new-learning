#include "ros/ros.h"
#include "turtlesim/Spawn.h"

/*
    需求：是向服务端发送请求，生成一只新乌龟
        话题：/spawn
        消息：turtlesin/Spawn

    1.包含头文件;
    2.初始化ROS节点;
    3.创建节点句柄;
    4.创建客户端对象；
    5.组织数据并发送；
    6.处理响应（客户端是可控的，不需要回调函数）

*/

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    // 2.初始化ROS节点;
    ros::init(argc,argv,"service_call");
    // 3.创建节点句柄;
    ros::NodeHandle nh;
    // 4.创建客户端对象；
    ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn"); 
    // 5.组织数据并发送；
    // 5-1.组织请求数据；
    turtlesim::Spawn spawn;
    spawn.request.x = 1.0;
    spawn.request.y = 4.0;
    spawn.request.theta = 1.57;
    spawn.request.name = "turtle2";
    // 5-2.发送请求
    // 判断服务器状态
    // 第一种：rosservice::client::waitForService("/spawn");
    // 第二种：client.waitForExistence(); 
    client.waitForExistence();  
    bool flag = client.call(spawn);  //flag用来接收响应状态,响应结果也会被设置进spawn对象
    // 6.处理响应
    if (flag)
    {
        ROS_INFO("乌龟生成成功，新乌龟叫:%s",spawn.response.name.c_str());
    }
    else
    {
        ROS_INFO("请求失败！！！");
    }

    return 0;
}
