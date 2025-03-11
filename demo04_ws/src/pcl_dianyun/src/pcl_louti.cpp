#include <ros/ros.h>
#include <pcl/io/obj_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>  // For pcl to PointCloud2 conversion
#include <fstream>  // 用于文件写入

// 发布点云数据的回调函数
void publishPointCloud(ros::Publisher &pub) {
    // 加载 .obj 文件路径
    const std::string obj_file_path = "/home/yezhi_gb/demo04_ws/2.obj";  // 可以通过参数传入

    // 创建一个 PointCloud 对象来存储点云数据
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    // 加载 .obj 文件中的点云数据
    if (pcl::io::loadOBJFile(obj_file_path, *cloud) == -1) {
        ROS_ERROR("Couldn't read file %s", obj_file_path.c_str());
        return;
    }

    // 输出点云的大小和一些点的数据
    ROS_INFO("Loaded %zu points from the OBJ file.", cloud->points.size());

    // 将点云数据导出到 CSV 文件
    std::ofstream file("/home/yezhi_gb/demo04_ws/point_cloud_data.csv");
    if (file.is_open()) {
        // 写入 CSV 文件头
        file << "X,Y,Z\n";

        // 遍历每个点并写入文件
        for (const auto& point : cloud->points) {
            file << point.x << "," << point.y << "," << point.z << "\n";
        }

        ROS_INFO("Point cloud data exported to point_cloud_data.csv");
        file.close();
    } else {
        ROS_ERROR("Could not open file for writing.");
    }

    // 将 PointCloud 转换为 PointCloud2 格式
    sensor_msgs::PointCloud2 cloud_msg;
    pcl::toROSMsg(*cloud, cloud_msg);
    cloud_msg.header.stamp = ros::Time::now();
    cloud_msg.header.frame_id = "map";  // 请根据实际情况修改为正确的坐标系

    // 发布点云数据
    pub.publish(cloud_msg);
}

int main(int argc, char** argv) {
    // 初始化 ROS
    ros::init(argc, argv, "pcl_louti");
    ros::NodeHandle nh;

    // 创建发布者
    ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2>("point_cloud_topic", 1);

    // 设置循环发布频率
    ros::Rate loop_rate(1);  // 每秒发布一次

    // 发布点云数据
    while (ros::ok()) {
        publishPointCloud(pcl_pub);
        ros::spinOnce();  // 处理回调
        loop_rate.sleep();  // 按照频率休眠
    }

    return 0;
}
