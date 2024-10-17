<body>
    <h1>Bill of Materials</h1>
    <style>
        /* Styling for table images */
        table img {
            width: 100px; /* Set a fixed width */
            height: 500px; /* Set a fixed height */
            object-fit: cover; /* Ensure images cover the specified dimensions */
        }
        table {
            width: 100%; /* Set table to full width */
            border-collapse: collapse; /* Collapse borders */
        }
        th, td {
            border: 1px solid #ddd; /* Add border to cells */
            padding: 8px; /* Add padding to cells */
            text-align: left; /* Align text to the left */
        }
        th {
            background-color: #f2f2f2; /* Background color for table header */
        }
    </style>
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
                <td data-label="Code">0x00</td>
                <td data-label="Name">NVIDIA Jetson Nano 4GB</td>
                <td data-label="Datasheet"><a href="https://developer.nvidia.com/embedded/dlc/jetson-nano-developer-kit">Datasheet</a></td>
                <td data-label="Setup"><a href="https://docs.nvidia.com/jetson/archives/r32.4/Jetson_Nano_Developer_Kit_Users_Guide.pdf">Setup</a></td>
                <td data-label="3D Model"><a href="https://developer.nvidia.com/embedded/learn/jetson-nano-3d-models">3D Model</a></td>
                <td data-label="Description">Main computing unit</td>
                <td data-label="Image"><img src="https://developer.nvidia.com/blog/wp-content/uploads/2019/03/Jetson-Nano_3QTR-Front_Left-1920px.png" alt="Jetson Nano"></td>
            </tr>
            <tr>
                <td data-label="Code">0x01</td>
                <td data-label="Name">Arduino NANO</td>
                <td data-label="Datasheet"><a href="https://store.arduino.cc/products/arduino-nano">Datasheet</a></td>
                <td data-label="Setup"><a href="https://docs.arduino.cc/hardware/nano">Setup</a></td>
                <td data-label="3D Model"><a href="https://grabcad.com/library/arduino-nano-v3-2">3D Model</a></td>
                <td data-label="Description">Microcontroller</td>
                <td data-label="Image"><img src="https://lh4.googleusercontent.com/proxy/9zUFLqlsIkmYlalhS33rOtFl7yIgIaflCP0bLvCnSY1_cTr9I2BGU8tNpbRsU8mRALt-mlRAmGV4EHakpUJJkDzJ6GSH5bEnfxY" alt="Arduino Nano"></td>
            </tr>
            <tr>
                <td data-label="Code">0x02</td>
                <td data-label="Name">LIDAR</td>
                <td data-label="Datasheet"><a href="https://www.slamtec.com/en/LIDAR">Datasheet</a></td>
                <td data-label="Setup"><a href="https://github.com/Slamtec/RPLIDAR_SDK">Setup</a></td>
                <td data-label="3D Model"><a href="https://github.com/Slamtec/RPLIDAR_SDK/tree/master/examples">3D Model</a></td>
                <td data-label="Description">Laser Range Sensor</td>
                <td data-label="Image"><img src="https://d229kd5ey79jzj.cloudfront.net/3157/images/3157_1_M.png?20240815085137" alt="LIDAR"></td>
            </tr>
            <tr>
                <td data-label="Code">0x03</td>
                <td data-label="Name">Distance Sensor VL53L1X</td>
                <td data-label="Datasheet"><a href="https://www.st.com/resource/en/datasheet/vl53l1x.pdf">Datasheet</a></td>
                <td data-label="Setup"><a href="https://www.st.com/en/imaging-and-photonics-solutions/vl53l1x.html">Setup</a></td>
                <td data-label="3D Model"><a href="https://www.thingiverse.com/thing:3014864">3D Model</a></td>
                <td data-label="Description">Time-of-Flight Distance Sensor</td>
                <td data-label="Image"><img src="https://holybro.com/cdn/shop/products/19004_1_1080x.jpg?v=1681882471" alt="VL53L1X"></td>
            </tr>
            <tr>
                <td data-label="Code">0x04</td>
                <td data-label="Name">GYROSCOPE Sensor MPU6050</td>
                <td data-label="Datasheet"><a href="https://www.invensense.com/products/motion-tracking/6-axis/mpu-6050/">Datasheet</a></td>
                <td data-label="Setup"><a href="https://components101.com/sensors/mpu6050-accelerometer-gyroscope-module">Setup</a></td>
                <td data-label="3D Model"><a href="https://www.tinkercad.com/things/9SZjBC0iDtF">3D Model</a></td>
                <td data-label="Description">6-axis Gyroscope and Accelerometer</td>
                <td data-label="Image"><img src="https://robo.com.cy/cdn/shop/products/mpu6050.png?v=1574351993&width=686" alt="MPU6050"></td>
            </tr>
            <tr>
                <td data-label="Code">0x05</td>
                <td data-label="Name">Camera</td>
                <td data-label="Datasheet"><a href="https://www.raspberrypi.org/documentation/hardware/camera/">Datasheet</a></td>
                <td data-label="Setup"><a href="https://www.raspberrypi.org/documentation/hardware/camera/README.md">Setup</a></td>
                <td data-label="3D Model"><a href="https://www.thingiverse.com/thing:2970128">3D Model</a></td>
                <td data-label="Description">Camera module</td>
                <td data-label="Image"><img src="https://w7.pngwing.com/pngs/1/412/png-transparent-camera-module-raspberry-pi-camera-serial-interface-camera-interface-camera-electronics-electronic-device-microcontroller.png" alt="Camera"></td>
            </tr>
            <tr>
                <td data-label="Code">0x06</td>
                <td data-label="Name">DC Brushed Motor with Encoder</td>
                <td data-label="Datasheet"><a href="https://www.pololu.com/file/0J551/25D_metal_gear_motor_with_encoder.pdf">Datasheet</a></td>
                <td data-label="Setup"><a href="https://www.pololu.com/product/1119">Setup</a></td>
                <td data-label="3D Model"><a href="https://www.tinkercad.com/things/hvT5XxH2gMv">3D Model</a></td>
                <td data-label="Description">Motor for movement with encoder feedback</td>
                <td data-label="Image"><img src="https://cdn.sparkfun.com/assets/parts/1/0/0/3/2/15235-25D_Metal_Gear_Motor_with_Encoder_-_12V.jpg" alt="DC Motor with Encoder"></td>
            </tr>
            <tr>
                <td data-label="Code">0x07</td>
                <td data-label="Name">Wheels</td>
                <td data-label="Datasheet"><a href="https://www.robotshop.com/en/motor-wheels.html">Datasheet</a></td>
                <td data-label="Setup"><a href="https://www.robotshop.com/en/wheel-and-tread.html">Setup</a></td>
                <td data-label="3D Model"><a href="https://www.thingiverse.com/thing:1864586">3D Model</a></td>
                <td data-label="Description">Wheels for robot movement</td>
                <td data-label="Image"><img src="https://cdn.sparkfun.com/assets/parts/1/5/5/6/1/14535-19899-wheels-15-50mm-rubber_03.jpg" alt="Wheels"></td>
            </tr>
            <tr>
                <td data-label="Code">0x08</td>
                <td data-label="Name">Chassis</td>
                <td data-label="Datasheet"><a href="https://www.robotshop.com/en/chassis.html">Datasheet</a></td>
                <td data-label="Setup"><a href="https://www.robotshop.com/en/chassis.html">Setup</a></td>
                <td data-label="3D Model"><a href="https://www.tinkercad.com/learn/projects/create-a-robot-chassis">3D Model</a></td>
                <td data-label="Description">Chassis for assembling components</td>
                <td data-label="Image"><img src="https://www.trossenrobotics.com/p/robot-chassis.jpg" alt="Chassis"></td>
            </tr>
        </tbody>
    </table>
</body>
