#include "ros/ros.h"
/*
    需求1：演示时间相关操作（获取当前时刻 + 设置指定时刻）
    实现：
        1.准备操作（头文件、节点初始化、NodeHandle创建...）
        2.获取当前时刻
        3.设置指定时刻

    需求2：程序执行中停顿4.5秒
    实现：
        1.创建持续时间对象
        2.休眠操作

    需求3：已知程序开始运行的时刻和程序运行的时间，求运行结束的时刻
    实现：
        1.获取开始执行的时刻
        2.模拟运行时间（N秒）
        3.计算结束时刻 = 开始 + 持续时间
    
    需求4：每隔1秒钟，在控制台输出一段文本
    实现：
        策略一：ros::Rate(),参数设置为1
        策略二：定时器

*/

//回调函数
void cb(const ros::TimerEvent& event)
{
    ROS_INFO("------------");
    ROS_INFO("函数被调用的时刻：%.2f",event.current_real.toSec());//event.current_real返回值为ros::Time类型
}

int main(int argc, char *argv[])
{
    // 1.准备操作（头文件、节点初始化、NodeHandle创建...）
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"hello_time");
    ros::NodeHandle nh;//注意：必须有这一步，否则会导致时间API调用失败（再NodeHandle会初始化时间操作）
    
    // 2.获取当前时刻
    //now 函数会将当前时刻封装并返回
    //当前时刻：now 被调用执行的那一刻
    //参考系：1970年01月01日 00：00：00（东八区是08:00:00） 
    ros::Time right_now = ros::Time::now();
    //toSec 函数将逝去时间转换成秒数，返回值为double类型（浮点）
    ROS_INFO("当前时刻：%.2f",right_now.toSec());
    //另一种获取方法，sec字段  right_now.sec ，返回值为整型
    ROS_INFO("当前时刻：%d",right_now.sec);

    // 3.设置指定时刻(构造函数)
    ros::Time t1(20,312345678);  //距离参考系20秒，312345678纳秒
    //另一种方法
    ros::Time t2(100.35);  //浮点类型，直接秒数
    ROS_INFO("t1 = %.2f",t1.toSec());
    ROS_INFO("t2 = %.2f",t2.toSec());

    //------------------------------------------------------------------
    
    ROS_INFO("-------------------持续时间------------------------");
    ros::Time start = ros::Time::now();
    ROS_INFO("开始休眠:%.2f",start.toSec());

    //核心
    ros::Duration du(4.5);  //ros::Duration可以接收整型和浮点类型的数据
    du.sleep();//休眠

    ros::Time end = ros::Time::now();
    ROS_INFO("休眠结束:%.2f",end.toSec());

    //------------------------------------------------------------------

    ROS_INFO("-------------------时间运算------------------------");
    //时刻与持续时间运算
    // 1.获取开始执行的时刻
    ros::Time begin = ros::Time::now();
    // 2.模拟运行时间（N秒）
    ros::Duration du1(5);
    // 3.计算结束时刻 = 开始 + 持续时间
    ros::Time stop = begin + du1;  //也可以减“-” 
    ROS_INFO("开始时刻：%.2f",begin.toSec());
    ROS_INFO("结束时刻：%.2f",stop.toSec());

    //时刻与时刻运算
    //ros::Time sum = begin + stop; //不可以相加
    ros::Duration du2 = begin - stop; //可以相减，值为Duration类型
    ROS_INFO("时刻相减:%.2f",du2.toSec());

    //持续时间与持续时间的运算
    ros::Duration du3 = du1 + du2; //0
    ros::Duration du4 = du1 - du2; //10
    ROS_INFO("du1 + du2 = %.2f",du3.toSec());
    ROS_INFO("du1 - du2 = %.2f",du4.toSec());

    //------------------------------------------------------------------

    ROS_INFO("-------------------定时器------------------------");

    /*
        ros::Timer createTimer(ros::Duration period   //时间间隔 --- 1s
                const ros::TimerCallback &callback   //回调函数 --- 封装业务
                bool oneshot = false                 //定时器是否是一次性的 --- true-->隔1s后执行一次回调函数，只执行一次
                                                                        --- false-->每隔1s执行一次回调函数（循环执行）
                bool autostart = true)               //定时器是否自动启动
    */
   
    // ros::Timer timer = nh.createTimer(ros::Duration(1),cb);
    // ros::Timer timer = nh.createTimer(ros::Duration(1),cb,true);
    ros::Timer timer = nh.createTimer(ros::Duration(1),cb,false,false);
    timer.start();//手动启动（执行到此函数后启动）

    ros::spin(); //需要回旋
    return 0;
}
