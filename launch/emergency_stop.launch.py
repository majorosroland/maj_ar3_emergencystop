from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='maj_ar3_emergencystop',
            executable='emergency_stop_publisher',
            name='emergency_stop_publisher',
            output='screen'
        ),
        Node(
            package='maj_ar3_emergencystop',
            executable='emergency_stop_subscriber',
            name='emergency_stop_subscriber',
            output='screen'
        ),
    ])
