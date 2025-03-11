#include "ros/ros.h"
/*
    演示参数删除：
    实现：通过两套API实现（API为“应用程序编程接口”）
        ros::NodeHandle
            deleteParam("键")
        ros::param
            del("键")
*/
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    // 初始化ROS节点
    ros::init(argc,argv,"del_param_c");
    // 创建节点句柄
    ros::NodeHandle nh;
    // ros::NodeHandle------------------------------------------------------------
    bool flag1 = nh.deleteParam("radius");
    if(flag1)
    {
        ROS_INFO("删除成功！");
    }
    else
    {
        ROS_INFO("删除失败！");
    }

    // ros::param------------------------------------------------------------------
    bool flag2 = ros::param::del("radius_param");
    if(flag2)
    {
        ROS_INFO("radius_param 删除成功！");
    }
    else
    {
        ROS_INFO("radius_param 删除失败！");
    }

    return 0;
}
