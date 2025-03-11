#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"   //订阅数据
#include "tf2_ros/buffer.h"    //保存（缓存）数据
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

/*
    订阅方：订阅发布的坐标系相对关系，传入一个坐标点，调用tf实现转换

    流程：
        1.包含头文件
        2.编码、初始化、NodeHandle（必须）
        3.创建订阅对象 ---> 订阅坐标系相对关系
        4.组织一个坐标点数据
        5.转换算法，需要调用tf内置实现
        6.输出转换结果

*/

int main(int argc, char *argv[])
{
    // 2.编码、初始化、NodeHandle（必须）
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"static_sub");
    ros::NodeHandle nh;

    // 3.创建订阅对象 ---> 订阅坐标系相对关系
    // 3-1 创建一个 buffer 缓存
    tf2_ros::Buffer buffer;
    // 3-2 再创建监听对象（监听对象可以将订阅的数据存入 buffer ）
    tf2_ros::TransformListener listener(buffer);

    // 4.组织一个坐标点数据
    geometry_msgs::PointStamped ps;
    //参考的坐标系需要修改
    ps.header.frame_id = "turtle1";
    //时间戳需要修改,否则会抛异常
    ps.header.stamp = ros::Time(0.0);
    ps.point.x = 2.0;
    ps.point.y = 3.0;
    ps.point.z = 5.0;

    //方案1：添加休眠（等订阅到坐标系相对关系再开始转化）
    ros::Duration(2).sleep();

    // 5.转换算法，需要调用TF内置实现
    ros::Rate rate(10);
    while (ros::ok())
    {
        //核心代码实现 --- 将 ps 转换成相对于 base_link 的坐标点
        geometry_msgs::PointStamped ps_out;
        /*
            调用了 buffer 的转换函数 transform
            参数1：被转换坐标点
            参数2：目标坐标系
            返回值：输出的坐标点

            PS1：调用时必须包含头文件 tf2_geometry_msgs/tf2_geometry_msgs.h
            PS2:运行时存在的问题：抛出一个异常 base_link 不存在
                原因：订阅数据是一个耗时操作，可能在调用 transform 转换函数时，坐标系的
                	 相对关系还没有订阅到，因此出现异常
                解决：
                    方案1：在调用转换函数前，执行休眠
                    方案2：进行异常处理(捕捉异常，然后循环，直到没有异常)(建议)
        */
        
        ps_out = buffer.transform(ps,"world");

        // 6.输出转换结果
        ROS_INFO("转换后的坐标值：（%.2f,%.2f,%.2f),参考的坐标系：%s",
                    ps_out.point.x,
                    ps_out.point.y,
                    ps_out.point.z,
                    ps_out.header.frame_id.c_str());
        rate.sleep();
        ros::spinOnce();
    }

    return 0;
}