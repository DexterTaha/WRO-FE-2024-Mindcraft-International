<p align="center">
    <img src="https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/c49080620d08a28a2c56fb28aea237c9f2fbfd57/images/Steering.png" alt="Steering" width="400">
    <br>
</p>

<p style="font-size: 12px;">
The steering system is powered by a 25T steering arm connected to the front axle, which acts as a joint rotating around a horizontal axis. This arm converts the rotational motion from the motor into angular motion for steering. It functions like a lever, translating torque into angular movement according to the equation:

&nbsp;&nbsp;&nbsp;&nbsp;**θ = T / r**

Where:
- **θ** is the angle of rotation,
- **T** is the torque applied, and
- **r** is the length of the arm.

The front wheels rotate around a horizontal axis based on the angle of the 25T arm, enabling the robot to turn. The wheel's angle is determined by the axial rotation of the arm, as described by the equation:

&nbsp;&nbsp;&nbsp;&nbsp;**θ_wheel = (L / r) * θ_25T**

Where:
- **L** is the length of the steering linkage.

Given that the **steering rack** has a fixed dimension of **109.15 mm**, the wheel diameter is **68 mm**, the thickness of each wheel is **27 mm**, and the **distance between the wheels is 133 mm**, the maximum turning radius is constrained by these dimensions. The angle required for the robot to turn is calculated based on these fixed dimensions to ensure accurate steering control. By setting these parameters, dynamic simulation optimizes the robot's steering performance within the specified constraints, ensuring both precision and efficiency in turning maneuvers.
</p>
