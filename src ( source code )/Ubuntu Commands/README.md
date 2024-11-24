### Preparing the ROS2 startup script:
1. Create a startup script:
```bash
touch startup.sh
```
2. Modify the content:
```bash
#!/bin/bash

# Source ROS 2 and workspace environment
source /opt/ros/humble/setup.bash
source ~/ros2_ws/install/setup.bash

# Start RViz in the background
ros2 launch sllidar_ros2 view_sllidar_c1_launch.py &

# Wait for RViz to initialize
sleep 5

# Start Wall Follower Node
cd ~/ros2_ws
ros2 run wall_follower wall_follower
```

