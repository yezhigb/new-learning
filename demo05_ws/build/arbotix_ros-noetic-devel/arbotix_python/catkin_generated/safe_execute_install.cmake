execute_process(COMMAND "/home/yezhi_gb/demo05_ws/build/arbotix_ros-noetic-devel/arbotix_python/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/yezhi_gb/demo05_ws/build/arbotix_ros-noetic-devel/arbotix_python/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
