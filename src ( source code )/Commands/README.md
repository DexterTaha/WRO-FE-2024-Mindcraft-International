# Setup:
#### Updating package:
```ubuntu
sudo apt-get update
```

#### Upgrading package:
```bash
sudo apt-get upgrade
```

#### Navigating to a specific file:
```bash
cd path/to/your/file
```
#### Going back:
```bash
cd ..
```

#### Creating a new folder:
```bash
mkdir new_folder
```

#### Creating a new file:
```bash
touch file.py
```

#### Editing a file:
```bash
vi file.py
```
#### Remove a file:
```bash
rm file.py
```
#### Running a python code:
```bash
python file.py
```
#### Stop a python code:
```bash
Ctrl + C
```

# Libraries installation:
#### Installing python3:
```bash
sudo apt install python3
```
#### Installing pip3:
```bash
sudo apt install python3-pip
```
#### Installing Pyserial package:
```bash
sudo pip3 install pyserial
```
#### Installing rplidar package:
```bash
sudo pip3 install rplidar
```
#### Install matplotlib and numpy:
```bash
sudo pip3 install matplotlib
sudo pip3 install numpy

//these packages are already on the libraries folder
```
#### Install opencv via apt:
```bash
sudo apt install python3-opencv
sudo apt install libopencv-dev python3-opencv
```

#### Adding on-start run functionality
```bash
sudo touch /etc/systemd/system/mything.service
```
##### Edit the code:
```bash
// edit the mything.service edit and add this code:
[Unit]
Description=Run Buzzer Script
After=network.target

[Service]
ExecStart=/usr/bin/python3 /home/mindcraft/Desktop/buzzer.py
Restart=always
User=mindcraft
Group=mindcraft

[Install]
WantedBy=multi-user.target
```
##### Start the service:
```bash
sudo systemctl enable mything.service
```
```bash
sudo systemctl start mything.service
```
##### View the service status:
```bash
sudo systemctl status mything.service
```

