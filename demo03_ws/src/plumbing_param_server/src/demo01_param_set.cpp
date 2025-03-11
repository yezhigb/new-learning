#include "ros/ros.h"
/*
    需要实现参数的新增和修改
    需求：首先设置机器人的共享参数，类型、半径（0.15m）（假设为圆形机器人）
         再修改半径（0.2m）
    实现：通过两套API实现（API为“应用程序编程接口”）
        ros::NodeHandle
            setParam("键"，值)
        ros::param
            set("键"，值)
    修改：只需要继续调用 setParam 或 set 函数，保证键是已经存在的，那么值会覆盖
*/
int main(int argc, char *argv[])
{
    // 初始化ROS节点
    ros::init(argc,argv,"set_param_c");
    // 创建ROS节点句柄
    ros::NodeHandle nh;
    // 参数增---------------------------------------
    // 方案1：nh
    nh.setParam("type","XiaoHuang");
    nh.setParam("radius",0.15);
    // 方案2：ros::param
    ros::param::set("type_param","XiaoBai");
    ros::param::set("radius_param",0.15);
    // 参数改---------------------------------------
    // 方案1：nh
    nh.setParam("radius",0.2);
    // 方案2：ros::param
    ros::param::set("radius_param",0.25);

    return 0;
}
