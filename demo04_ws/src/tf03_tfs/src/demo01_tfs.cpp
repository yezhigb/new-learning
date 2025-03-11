#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "geometry_msgs/TransformStamped.h"

/*
    订阅方实现：
        1.计算son1与son2的相对关系
        2.计算son1中的某个坐标点在son2中的坐标值
    流程：
        1.包含头文件
        2.编码、初始化、NodeHandle
        3.创建订阅对象
        4.编写解析逻辑
        5.spinOnce()
*/

int main(int argc, char *argv[])
{
    // 2.编码、初始化、NodeHandle
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"tfs_sub");
    ros::NodeHandle nh;
    
    // 3.创建订阅对象
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener sub(buffer);

    // 4.编写解析逻辑

    //创建坐标点
    geometry_msgs::PointStamped psAtSon1;

    psAtSon1.header.stamp = ros::Time::now();
    psAtSon1.header.frame_id = "son1";
    psAtSon1.point.x = 1.0;
    psAtSon1.point.y = 2.0;
    psAtSon1.point.z = 3.0;

    ros::Rate rate(10);
    while (ros::ok())
    {
        //核心
        try
        {
            //1.计算son1与son2的相对关系
            /*
                buffer.lookuoTransform 函数的参数含义

                A 相对于 B 的坐标系关系

                参数1：目标坐标系 B
                参数2，源坐标系   A
                参数3：ros::Time(0) 取间隔最短的两个坐标关系帧，来计算相对关系
                返回值：geometry_msgs::TransformStamped 源相对于目标坐标系的相对关系
            */

            geometry_msgs::TransformStamped Son1ToSon2 = buffer.lookupTransform("son2","son1",ros::Time(0));   
            ROS_INFO("son1 相对于 son2 的信息：父级：%s,子级:%s,偏移量(%.2f,%.2f,%.2f)",
                    Son1ToSon2.header.frame_id.c_str(),   // son2
                    Son1ToSon2.child_frame_id.c_str(),     // son1
                    Son1ToSon2.transform.translation.x,
                    Son1ToSon2.transform.translation.y,
                    Son1ToSon2.transform.translation.z
                    );

            // 2.计算son1中的某个坐标点在son2中的坐标值
            geometry_msgs::PointStamped psAtSon2 = buffer.transform(psAtSon1,"son2");
            ROS_INFO("坐标点在 Son2 中的值(%.2f,%.2f,%.2f)",
                    psAtSon2.point.x,
                    psAtSon2.point.y,
                    psAtSon2.point.z
                    );
        }
        catch(const std::exception& e)
        {
            ROS_INFO("错误提示：%s",e.what());
        }
        

        rate.sleep();
        ros::spinOnce();
    }
    
    // 5.spinOnce()
    return 0;
}
