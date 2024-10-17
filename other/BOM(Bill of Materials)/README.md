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
                <th>Code</th>
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
                <td>0x00</td>
                <td>NVIDIA Jetson Nano 4GB</td>
                <td><a href="https://developer.nvidia.com/embedded/dlc/jetson-nano-developer-kit">Datasheet</a></td>
                <td><a href="https://docs.nvidia.com/jetson/archives/r32.4/Jetson_Nano_Developer_Kit_Users_Guide.pdf">Setup</a></td>
                <td><a href="https://developer.nvidia.com/embedded/learn/jetson-nano-3d-models">3D Model</a></td>
                <td>Main computing unit</td>
                <td><img src="https://developer.nvidia.com/blog/wp-content/uploads/2019/03/Jetson-Nano_3QTR-Front_Left-1920px.png" alt="Jetson Nano"></td>
            </tr>
            <tr>
                <td>0x01</td>
                <td>Arduino NANO</td>
                <td><a href="https://store.arduino.cc/products/arduino-nano">Datasheet</a></td>
                <td><a href="https://docs.arduino.cc/hardware/nano">Setup</a></td>
                <td><a href="https://grabcad.com/library/arduino-nano-v3-2">3D Model</a></td>
                <td>Microcontroller</td>
                <td><img src="https://store-cdn.arduino.cc/uni/catalog/product/cache/1/image/700x395/603d8cba50f48b1e7eaaad94a0c9412d/a/b/abx00055_featured.png" alt="Arduino Nano"></td>
            </tr>
            <tr>
                <td>0x02</td>
                <td>LIDAR</td>
                <td><a href="https://www.slamtec.com/en/LIDAR">Datasheet</a></td>
                <td><a href="https://github.com/Slamtec/RPLIDAR_SDK">Setup</a></td>
                <td><a href="https://github.com/Slamtec/RPLIDAR_SDK/tree/master/examples">3D Model</a></td>
                <td>Laser Range Sensor</td>
                <td><img src="https://d229kd5ey79jzj.cloudfront.net/3157/images/3157_1_M.png?20240815085137" alt="LIDAR"></td>
            </tr>
            <tr>
                <td>0x03</td>
                <td>Distance Sensor VL53L1X</td>
                <td><a href="https://www.st.com/resource/en/datasheet/vl53l1x.pdf">Datasheet</a></td>
                <td><a href="https://www.st.com/en/imaging-and-photonics-solutions/vl53l1x.html">Setup</a></td>
                <td><a href="https://www.thingiverse.com/thing:3014864">3D Model</a></td>
                <td>Time-of-Flight Distance Sensor</td>
                <td><img src="https://holybro.com/cdn/shop/products/19004_1_1080x.jpg?v=1681882471" alt="VL53L1X"></td>
            </tr>
            <tr>
                <td>0x04</td>
                <td>GYROSCOPE Sensor MPU6050</td>
                <td><a href="https://www.invensense.com/products/motion-tracking/6-axis/mpu-6050/">Datasheet</a></td>
                <td><a href="https://components101.com/sensors/mpu6050-accelerometer-gyroscope-module">Setup</a></td>
                <td><a href="https://www.tinkercad.com/things/9SZjBC0iDtF">3D Model</a></td>
                <td>6-axis Gyroscope and Accelerometer</td>
                <td><img src="https://microcell.ma/wp-content/uploads/2024/02/ori-module-6-dof-sen-mpu6050-31492.jpg" alt="MPU6050"></td>
            </tr>
            <tr>
                <td>0x05</td>
                <td>Camera</td>
                <td><a href="https://www.raspberrypi.org/documentation/hardware/camera/">Datasheet</a></td>
                <td><a href="https://www.raspberrypi.org/documentation/hardware/camera/README.md">Setup</a></td>
                <td><a href="https://www.thingiverse.com/thing:2970128">3D Model</a></td>
                <td>Camera module</td>
                <td><img src="https://www.raspberrypi.org/documentation/hardware/camera/raspberry-pi-camera-module-v2.png" alt="Camera"></td>
            </tr>
            <!-- Continue the same structure for the remaining components -->
        </tbody>
    </table>
</body>
</html>
