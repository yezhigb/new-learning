#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"

/*
    发布方：需要订阅乌龟的位姿信息，转换成相对于世界坐标系（窗体）的坐标关系，并发布
    准备：
        1.话题：/turtle1/pose
               用 rostopic list 获取 ---> /turtle1/pose
               用 rostopic info /turtle1/pose 获取具体信息
        2.消息：turtlesim/Pose 
               用 rosmsg info turtlesim/Pose 获取消息格式

    流程：
        1.包含头文件
        2.设置编码、初始化、NodeHandle
        3.创建订阅对象，订阅 /turtle1/pose
        4.回调函数处理订阅的消息：把订阅到的位姿信息转换成坐标相对关系并发布（关注）
        5.spin()
*/
void doPose(const turtlesim::Pose::ConstPtr& pose){
    //获取位姿信息，转换成坐标系相对关系（核心），并发布
    // a.创建发布对象
    static tf2_ros::TransformBroadcaster pub;  //静态，防止每循环一次都要生成一个新的 pub
    
    // b.组织被发布的数据
    geometry_msgs::TransformStamped ts;
    ts.header.frame_id = "world";
    ts.header.stamp = ros::Time::now();
    ts.child_frame_id = "turtle1";
    //坐标系偏移量
    ts.transform.translation.x = pose->x;
    ts.transform.translation.y = pose->y;
    ts.transform.translation.z = 0;
    //坐标系四元数
    /*
        位姿信息中没有四元数，但是有个偏航角度，又已知乌龟是 2D 的，没有翻滚与俯仰角度
        所以可以得出乌龟的欧拉角： 0 0 theta
    */
    tf2::Quaternion qtn;
    qtn.setRPY(0,0,pose->theta);

    ts.transform.rotation.x = qtn.getX();
    ts.transform.rotation.y = qtn.getY();
    ts.transform.rotation.z = qtn.getZ();
    ts.transform.rotation.w = qtn.getW();

    // c.发布
    pub.sendTransform(ts);
}

int main(int argc, char *argv[])
{
    // 2.设置编码、初始化、NodeHandle
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"dynamic_pub");
    ros::NodeHandle nh;

    // 3.创建订阅对象，订阅 /turtle1/pose
    ros::Subscriber sub = nh.subscribe("turtle1/pose",100,doPose);

    // 4.回调函数处理订阅的消息：把订阅到的位姿信息转换成坐标相对关系并发布（关注）
    // 5.spin()
    ros::spin();

    return 0;
}
