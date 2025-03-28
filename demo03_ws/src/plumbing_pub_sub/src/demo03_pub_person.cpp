#include "ros/ros.h"
#include "plumbing_pub_sub/Person.h"
/*
    发布方：发布人的消息
        1.包含头文件；
            #include "plumbing_pub_sub/Person.h"  （生成的中间文件）
        2.初始化 ROS 节点；
        3.创建节点句柄；
        4.创建发布者对象；
        5.编写发布逻辑，发布数据。
*/
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ROS_INFO("这是消息的发布方");
    // 2.初始化 ROS 节点；
    ros::init(argc,argv,"BanZhuRen");
    // 3.创建节点句柄；
    ros::NodeHandle nh;
    // 4.创建发布者对象；
    ros::Publisher pub = nh.advertise<plumbing_pub_sub::Person>("Chat",10);
    // 5.编写发布逻辑，发布数据。
    // 5-1.创建被发布的数据
    plumbing_pub_sub::Person person;
    person.name = "张三";
    person.age = 1;
    person.height = 1.73;
    // 5-2.设置发布频率
    ros::Rate rate(1);
    // 5-3.循环发布数据
    while (ros::ok())
    {
        //修改数据
        person.age += 1;  //此处是从2岁开始的
        // 核心：数据发布
        pub.publish(person);
        ROS_INFO("发布的消息：姓名：%s,年龄：%d,身高：%.2f",person.name.c_str(),person.age,person.height);
        // 休眠
        rate.sleep();
        // 建议（调用回调函数）
        ros::spinOnce();
    }

    return 0;
}
