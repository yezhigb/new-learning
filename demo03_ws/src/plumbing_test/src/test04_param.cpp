#include "ros/ros.h"

/*
    需求:修改参数服务器中 turtlesim 背景色相关参数
    1.初始化ROS节点
    2.不一定需要创建节点句柄（和后续API有关）
    3.修改参数

*/

int main(int argc, char *argv[])
{
    // 1.初始化ROS节点
    ros::init(argc,argv,"change_bgColor");
    // 2.不一定需要创建节点句柄（和后续API有关）
    // ros::NodeHandle nh("turtlesim");  
    //                  //turtlesim为命名空间，此处创建节点句柄与之前不同
    // nh.setParam("background_r",255);  //由于上一行中会直接调用命名空间，所以此处不需要加turtlesim
    // nh.setParam("background_g",255);
    // nh.setParam("background_b",255);

    ros::NodeHandle nh;
    nh.setParam("/turtlesim/background_r",255);
    nh.setParam("/turtlesim/background_g",0);
    nh.setParam("/turtlesim/background_b",0);

    // 3.修改参数
    // 如果调用 ros::param,不需要创建节点句柄
    // ros::param ::set("/turtlesim/background_r",255);
    // ros::param ::set("/turtlesim/background_g",0);
    // ros::param ::set("/turtlesim/background_b",0);

    return 0;
}
