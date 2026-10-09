from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='rei_l0c_batterymonitor',
            executable='battery_node',
            name='battery_node',
            output='screen'
        ),
        Node(
            package='rei_l0c_batterymonitor',
            executable='battery_alarm_node',
            name='battery_alarm_node',
            output='screen'
        )
    ])