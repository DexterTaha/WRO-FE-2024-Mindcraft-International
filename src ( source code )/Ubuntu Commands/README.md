### Basic Ubuntu Commands:
Create a file:
```bash
touch file.py
```
Navigate to a folder:
```bash
cd folder
```
Run a python script:
```bash
python3 file.py
```


---

### Preparing the ROS2 startup script
#### Setup
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
3. Make the script executable:
```
chmod +x /home/mindcraft/start_ros2.sh
```
#### Making the script executable
1. Edit Contrab:
```bash
crontab -e
```
2. Add the following line:
```bash
@reboot /bin/bash /home/mindcraft/start_ros2.sh > /home/mindcraft/start_ros2.log 2>&1
```
#### Testing the setup
1. Reboot the system:
```bash
sudo reboot
```
2. Check the Log File After Reboot:
```bash
cat /home/mindcraft/start_ros2.log
```
