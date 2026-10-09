cmake_minimum_required(VERSION 3.8)
project(rei_l0c_batterymonitor)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# 1. battery_node fordítása
add_executable(battery_node src/battery_node.cpp)
ament_target_dependencies(battery_node rclcpp std_msgs)

# 2. battery_alarm_node fordítása
add_executable(battery_alarm_node src/battery_alarm_node.cpp)
ament_target_dependencies(battery_alarm_node rclcpp std_msgs)

# Futtatható fájlok telepítése
install(TARGETS
  battery_node
  battery_alarm_node
  DESTINATION lib/${PROJECT_NAME}
)

# Launch mappa telepítése
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()