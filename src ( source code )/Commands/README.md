# Setup:
#### Updating package:
```bash
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

#### Adding on-startup functionality
```bash
crontab -e
@reboot python3 /home/mindcraft/Desktop/buzzer.py >> /home/mindcraft/Desktop/buzzer_startup.log 2>&1
```
