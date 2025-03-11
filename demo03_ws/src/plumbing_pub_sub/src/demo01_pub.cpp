#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
/*
    发布方实现：
        1.包含头文件；
            ROS 中文本类型 --->std_msgs/String.h
        2.初始化 ROS 节点；
        3.创建节点句柄；
        4.创建发布者对象；
        5.编写发布逻辑并发布数据。
*/ 
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    // 2.初始化 ROS 节点；
    ros::init(argc,argv,"erGouZi");
    // 3.创建节点句柄；
    ros::NodeHandle nh;
    // 4.创建发布者对象；
/*
    作用：创建发布者对象

    模板：被发布的消息的对象

    参数：
        1.话题名称  topic
        2.队列长度  queue_size
        3.latch（可选）   bool值，默认为false。
            如果设置为true，会保存发布方的最后一条消息，并且新的订阅对象连接到发布方时，发布方会将这条消息
            发送给订阅者(如果设置为false，则最后一条消息不保存，当消息发布完成后若有新的订阅者连接，则不会
            给新的订阅者发消息)
    使用：
        latch 设置为 true 的作用
            应用场景：当机器人导航时，需要获得静态地图信息(此信息长时间不变)
                方案一：使用固定频率发送地图数据（eg：10Hz），可以满足要求但效率偏低(因为信息是不变的)
                方案二：可以将地图发布对象的 latch 设置为true，并且发布方只发送一次数据，每当订阅者连接
                时，将地图数据发送给订阅者（只发送一次），这样可以提高数据的发送效率
        
        */

    ros::Publisher pub = nh.advertise<std_msgs::String>("fang",10,true) ;
    // 5.编写发布逻辑并发布数据。
    // 要求发布方以10HZ(每秒10次)的频率发布文本消息，并在文本后添加编号
    // 先创建被发布的消息
    std_msgs::String msg;
    // 设置发布频率
    ros::Rate rate(10);
    // 设置编号
    int count = 0;
    // 编写循环，循环中发布数据
    while (ros::ok())
    {
        count++;
        // 实现字符串拼接数字
        std::stringstream ss;
        ss << "hello --->" << count;
        // msg.data = "hello";
        msg.data = ss.str();
        if (count <= 10)
        {
            pub.publish(msg);
            // 添加日志：
            ROS_INFO("发布的数据是：%s",ss.str().c_str());
        }
        
        rate.sleep();
        ros::spinOnce(); //官方建议，处理回调函数
        ROS_INFO("一轮回调执行完毕.....");
    }
    

    return 0;
}
