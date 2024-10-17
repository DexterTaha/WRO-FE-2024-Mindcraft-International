<!DOCTYPE html>
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
                <td>DTOF RPLIDAR C1</td>
                <td><a href="https://www.slamtec.com/en/SLAMTEC-RPLIDAR">Datasheet</a></td>
                <td><a href="https://github.com/Slamtec/RPLIDAR_SDK">Setup</a></td>
                <td><a href="https://github.com/Slamtec/RPLIDAR_SDK/tree/master/examples">3D Model</a></td>
                <td>Distance sensor</td>
                <td><img src="https://d229kd5ey79jzj.cloudfront.net/3157/images/3157_1_M.png?20240815085137" alt="RPLICAR C1"></td>
            </tr>
            <tr>
                <td>1</td>
                <td>Filament - Nylon Fibre</td>
                <td><a href="https://www.3dware.ma/produit/esun-fibre-de-carbone-haute-temperature-naturel-filament-1-75mm-1kg/">Datasheet</a></td>
                <td>N/A</td>
                <td>N/A</td>
                <td>Nylon Fibre</td>
                <td><img src="https://www.3dware.ma/image/cache/catalog/Filaments/Nylon/filament-nylon-carbone-1-75mm-1kg-300x300.png" alt="Nylon Filament"></td>
            </tr>
            <tr>
                <td>1</td>
                <td>Filament - Flexible TPU</td>
                <td><a href="https://www.3dware.ma/produit/filament-3d-fila-flexible-tpu-blanc-1-75mm-1kg/">Datasheet</a></td>
                <td>N/A</td>
                <td>N/A</td>
                <td>Flexible TPU</td>
                <td><img src="https://www.3dware.ma/image/cache/catalog/Filaments/TPU/filament-tpu-1-75mm-1kg-300x300.png" alt="TPU Filament"></td>
            </tr>
            <tr>
                <td>3</td>
                <td>Batterie - Lipo 3S 2200mah 11.1V 50C</td>
                <td><a href="https://shop4makers.com/produit/batterie-lipo-3s-2200mah-11-1v-50c-xt60/">Datasheet</a></td>
                <td>N/A</td>
                <td>N/A</td>
                <td>3S Lipo Battery</td>
                <td><img src="https://shop4makers.com/wp-content/uploads/2021/09/lipo-3s-battery.jpg" alt="Lipo Battery"></td>
            </tr>
            <tr>
                <td>1</td>
                <td>Chargeur - IMAX B6AC V2</td>
                <td><a href="https://shop4makers.com/produit/chargeur-imax-b6ac-v2/">Datasheet</a></td>
                <td>N/A</td>
                <td>N/A</td>
                <td>Battery Charger</td>
                <td><img src="https://shop4makers.com/wp-content/uploads/2021/09/imax-b6ac-v2.jpg" alt="Charger"></td>
            </tr>
            <tr>
                <td>1</td>
                <td>Buzzer</td>
                <td><a href="https://shop4makers.com/produit/buzzer-alarme-batterie-lipo/">Datasheet</a></td>
                <td>N/A</td>
                <td>N/A</td>
                <td>Lipo Battery Alarm Buzzer</td>
                <td><img src="https://shop4makers.com/wp-content/uploads/2021/09/buzzer.jpg" alt="Buzzer"></td>
            </tr>
            <tr>
                <td>1</td>
                <td>Servo Driver</td>
                <td><a href="https://shop4makers.com/produit/controleur-de-servomoteurs-pwm-16-canaux/">Datasheet</a></td>
                <td>N/A</td>
                <td>N/A</td>
                <td>16 Channel Servo Controller</td>
                <td><img src="https://shop4makers.com/wp-content/uploads/2021/09/servo-driver.jpg" alt="Servo Driver"></td>
            </tr>
            <tr>
                <td>1</td>
                <td>Servo Tester</td>
                <td><a href="https://shop4makers.com/produit/testeur-de-servomoteur-et-desc/">Datasheet</a></td>
                <td>N/A</td>
                <td>N/A</td>
                <td>Servo Motor Tester</td>
                <td><img src="https://shop4makers.com/wp-content/uploads/2021/09/servo-tester.jpg" alt="Servo Tester"></td>
            </tr>
            <tr>
                <td>2</td>
                <td>Servo Motor</td>
                <td><a href="https://shop4makers.com/produit/servomoteur-mg995-maroc/">Datasheet</a></td>
                <td>N/A</td>
                <td>N/A</td>
                <td>Metal Gear Box 180°</td>
                <td><img src="https://shop4makers.com/wp-content/uploads/2021/09/servo-motor.jpg" alt="Servo Motor"></td>
            </tr>
            <tr>
                <td>2</td>
                <td>Servobras</td>
                <td><a href="https://shop4makers.com/produit/servobras-aluminium-25-t-m3/">Datasheet</a></td>
                <td>N/A</td>
                <td>N/A</td>
                <td>Servo Arms</td>
                <td><img src="https://shop4makers.com/wp-content/uploads/2021/09/servo-arm.jpg" alt="Servo Arm"></td>
            </tr>
            <tr>
                <td>1</td>
                <td>Screen - OLED</td>
                <td><a href="https://shop4makers.com/produit/afficheur-oled-0-96-i2c/">Datasheet</a></td>
                <td>N/A</td>
                <td>N/A</td>
                <td>OLED Display</td>
                <td><img src="https://shop4makers.com/wp-content/uploads/2021/09/oled-screen.jpg" alt="OLED Screen"></td>
            </tr>
            <tr>
                <td>1</td>
                <td>ARDU
