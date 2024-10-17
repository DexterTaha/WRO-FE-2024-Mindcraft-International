<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Bill of Materials</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
        }
        h1 {
            text-align: center;
        }
        table {
            width: 100%;
            border-collapse: collapse;
            margin: 20px 0;
        }
        th, td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: center;
        }
        th {
            background-color: #f2f2f2;
        }
        img {
            max-width: 100px;
            height: auto;
        }
    </style>
</head>
<body>
    <h1>Bill of Materials</h1>
    <table>
        <thead>
            <tr>
                <th>Quantity</th>
                <th>Name</th>
                <th>Datasheet</th>
                <th>Setup</th>
                <th>3D Model</th>
                <th>Description</th>
                <th>Image</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td>1</td>
                <td>NVIDIA Jetson Nano</td>
                <td><a href="https://developer.nvidia.com/embedded/dlc/jetson-nano-developer-kit">Datasheet</a></td>
                <td><a href="https://docs.nvidia.com/jetson/archives/r32.4/Jetson_Nano_Developer_Kit_Users_Guide.pdf">Setup</a></td>
                <td><a href="https://developer.nvidia.com/embedded/learn/jetson-nano-3d-models">3D Model</a></td>
                <td>Main computer (Hub)</td>
                <td><img src="https://developer.nvidia.com/blog/wp-content/uploads/2019/03/Jetson-Nano_3QTR-Front_Left-1920px.png" alt="JETSON NANO"></td>
            </tr>
            <tr>
                <td>1</td>
                <td>Arduino NANO</td>
                <td><a href="https://store.arduino.cc/products/arduino-nano">Datasheet</a></td>
                <td><a href="https://store.arduino.cc/products/arduino-nano">Setup</a></td>
                <td><a href="https://grabcad.com/library/arduino-nano-10">3D Model</a></td>
                <td>Microcontroller board</td>
                <td><img src="https://store-usa.arduino.cc/usa/images/products/ABX00087_iso_both.jpg" alt="Arduino NANO"></td>
            </tr>
            <tr>
                <td>1</td>
                <td>LIDAR (RPLIDAR C1)</td>
                <td><a href="https://www.slamtec.com/en/SLAMTEC-RPLIDAR">Datasheet</a></td>
                <td><a href="https://github.com/Slamtec/RPLIDAR_SDK">Setup</a></td>
                <td><a href="https://grabcad.com/library/slamtec-rplidar-1">3D Model</a></td>
                <td>Distance sensor</td>
                <td><img src="https://d229kd5ey79jzj.cloudfront.net/3157/images/3157_1_M.png?20240815085137" alt="LIDAR"></td>
            </tr>
            <tr>
                <td>4</td>
                <td>Distance Sensor (VL53L1X)</td>
                <td><a href="https://www.st.com/resource/en/datasheet/vl53l1x.pdf">Datasheet</a></td>
                <td><a href="https://www.st.com/en/imaging-and-photonics-solutions/vl53l1x.html">Setup</a></td>
                <td><a href="https://grabcad.com/library/vl53l1x">3D Model</a></td>
                <td>Time-of-Flight distance sensor</td>
                <td><img src="https://holybro.com/cdn/shop/products/19004_1_1080x.jpg?v=1681882471" alt="VL53L1X"></td>
            </tr>
            <tr>
                <td>1</td>
                <td>Gyroscope Sensor (MPU6050)</td>
                <td><a href="https://invensense.tdk.com/products/motion-tracking/6-axis/mpu-6050/">Datasheet</a></td>
                <td><a href="https://invensense.tdk.com/developers/arduino-library/">Setup</a></td>
                <td><a href="https://grabcad.com/library/mpu6050">3D Model</a></td>
                <td>6-axis motion tracking device</td>
                <td><img src="https://microcell.ma/wp-content/uploads/2024/02/ori-module-6-dof-sen-mpu6050-31492.jpg" alt="MPU6050"></td>
            </tr>
            <tr>
                <td>1</td>
                <td>Camera Module</td>
                <td><a href="https://www.arducam.com/raspberry-pi-camera/">Datasheet</a></td>
                <td><a href="https://www.arducam.com/raspberry-pi-camera/">Setup</a></td>
                <td><a href="https://grabcad.com/library/arducam-raspberry-pi-camera">3D Model</a></td>
                <td>1080p Camera for Vision Processing</td>
                <td><img src="https://www.arducam.com/wp-content/uploads/2020/02/arducam-ov5647-mini-camera.jpg" alt="Camera Module"></td>
            </tr>
            <tr>
                <td>2</td>
                <td>DC Brushed Motor with encoder</td>
                <td><a href="https://www.pololu.com/product/1447">Datasheet</a></td>
                <td><a href="https://www.pololu.com/docs/0J15">Setup</a></td>
                <td><a href="https://grabcad.com/library/pololu-37d-mm-metal-geared-dc-motor-with-encoder-1">3D Model</a></td>
                <td>DC motor with encoder for accurate control</td>
                <td><img src="https://www.pololu.com/file/download/37D.jpg?file_id=0J8083" alt="DC Motor"></td>
            </tr>
            <tr>
                <td>2</td>
                <td>Servo Motor (Metal Gear Box 180°)</td>
                <td><a href="https://www.servocity.com/servos/metal-gear-servos/">Datasheet</a></td>
                <td><a href="https://www.servocity.com/servos/metal-gear-servos/">Setup</a></td>
                <td><a href="https://grabcad.com/library/servo-motor-1">3D Model</a></td>
                <td>Metal gear servo for precise control</td>
                <td><img src="https://shop4makers.com/wp-content/uploads/2021/09/servo-motor.jpg" alt="Servo Motor"></td>
            </tr>
        </tbody>
    </table>
</body>
</html>
