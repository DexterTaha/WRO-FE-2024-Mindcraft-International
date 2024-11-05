<p align="center">
    <img src="https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/c49080620d08a28a2c56fb28aea237c9f2fbfd57/images/Steering.png" alt="Steering" width="400">
    <br>
</p>

### Ackermann Steering Structure and Calculation

The Ackermann steering geometry is designed to ensure that, during a turn, the inner wheel rotates at a greater angle than the outer wheel. This difference in steering angles allows the wheels to follow curved paths with a common turning center, minimizing tire friction and wear. The turning radius, **R**, is the distance from the center of the rear axle to the turning center and defines the path that the robot follows during a turn.

The steering angles for the inner and outer wheels are calculated as follows:

&nbsp;&nbsp;&nbsp;&nbsp;**Inner wheel angle (a₁):**  
&nbsp;&nbsp;&nbsp;&nbsp;\\( a_1 = \tan^{-1} \left( \frac{L}{R - \frac{T}{2}} \right) \\)

&nbsp;&nbsp;&nbsp;&nbsp;**Outer wheel angle (a₂):**  
&nbsp;&nbsp;&nbsp;&nbsp;\\( a_2 = \tan^{-1} \left( \frac{L}{R + \frac{T}{2}} \right) \\)

Where:
- **L** is the wheelbase (distance between the front and rear axles), set to **109.15 mm**.
- **T** is the track width (distance between the two front wheels), set to **133 mm**.
- **R** is the desired turning radius, set to **500 mm** (50 cm).

Using these values, we calculate the required angles to achieve the minimum turning radius of 50 cm:

- **Inner wheel angle (a₁):** 14.13°
- **Outer wheel angle (a₂):** 10.91°

### Range of Steering Angles

To ensure optimal turning capability, the steering system should be capable of adjusting between these angles, providing a range of approximately **10.91° to 14.13°**. This range allows for precise control of the robot's turning behavior within the specified turning radius, optimizing maneuverability and stability.

<p align="center">
    <img src="/mnt/data/image.png" alt="Ackermann Steering Structure Pendulum Suspension" width="600">
</p>
