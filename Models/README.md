# WRO Future Engineers Robot - Models

This section covers the **CAD modeling and manufacturing process** behind the development of our robot for the **WRO Future Engineers competition**. We detail the tools, design choices, and manufacturing techniques that helped bring our vision to life, along with key decisions that strengthened the project.

## Table of Contents

1. [Introduction](#introduction)
2. [Design Considerations Before CAD Modeling](#design-considerations-before-cad-modeling)
   - [Key Requirements](#key-requirements)
3. [Initial Robot Design and Iterations](#initial-robot-design-and-iterations)
   - [Challenges and Lessons Learned](#challenges-and-lessons-learned)
4. [3D CAD Modeling - Onshape](#3d-cad-modeling---onshape)
5. [3D Printing](#3d-printing)
6. [Robot Assembly and Systems](#robot-assembly-and-systems)
7. [Robot Parts Details](#robot-parts-details)
8. [Conclusion](#conclusion)

---

## Introduction

Our WRO Future Engineers robot project is designed to compete in the **World Robot Olympiad (WRO)**, representing **Morocco**. The robot must navigate challenging courses while maintaining speed, stability, and efficiency. Our team focused on developing a compact, reliable design that integrates modular parts, allowing for easy repairs and modifications.

This document walks through our entire design journey, from defining requirements and initial prototypes to final assembly and testing. We leveraged **Onshape** for CAD modeling and **3D printing** for manufacturing, balancing quality and flexibility to achieve a robust competition-ready robot.

## Design Considerations Before CAD Modeling

Our design process began with setting clear requirements to ensure the robot met competition standards while maximizing efficiency and performance.

### Key Requirements

- **Compact Size**: The robot must fit within a **20cm cube** for optimal maneuverability.
- **Turning Radius**: Ability to turn within a **40cm outside circle** for navigating tight spaces.
- **Stability and Low Center of Gravity**: Ensures smooth movement and prevents tipping.
- **Equal Weight Distribution**: Enhances handling and prevents unbalanced movement.
- **High Traction**: Ensures friction on wheels for better control.
- **Modular Assembly**: All parts should be assembled with **screws**, **nuts**, and **zip ties** for ease of modification.
- **Lightweight Design**: Reduces energy consumption and improves speed.
- **Differential System**: Smooth and easy turning.
- **Battery and Component Safety**: Battery placed safely to prevent damage and ensure easy access for maintenance.
- **Ease of Reassembly**: Parts designed to assemble in only **one way** to avoid mistakes.
- **Readily Available Parts**: Ensures parts are accessible to other teams for replication.

## Initial Robot Design and Iterations

We went through several iterations to optimize the robot’s design for functionality and performance.

### National Competition: LEGO Robot

Our initial prototype was built with **LEGO components**, but it had limitations:
- **Oversized and Slow**: Exceeded size requirements and lacked speed.
- **Obstacle Navigation Issues**: Couldn’t complete the **obstacle challenge and parking**.
- **Structural Limitations**: LEGO components lacked the sturdiness needed for competitive use.

*Image of LEGO Robot Used in National Competition:*

![LEGO Robot](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/main/images/LEGO_Robot_National.png)

### First Version: Oversized DIY Robot

For the international stage, we built a **DIY robot**, but it faced new issues:
- **Size and Weight Problems**: The robot didn’t fit within the 20cm cube and was too heavy.
- **Poor Maneuverability**: Larger structure hindered effective course navigation.

*Image of First DIY Robot Version:*

![First DIY Robot](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/main/images/First_DIY_Robot.png)

### Second Version: Lack of Differential System

Our second DIY iteration introduced a more compact design, but:
- **No Differential System**: Made turning difficult and required a **150cm turning radius**.
- **Drifting**: The lack of control made precise movements challenging.

*Image of Second DIY Robot Version:*

![Second DIY Robot](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/main/images/Second_DIY_Robot.png)

### Third Version: Final Optimized Robot

For our final version, we incorporated a **differential system** and switched to **Raspberry Pi 4 Model B** for:

- **Improved Compatibility and Weight Reduction**: Lighter and more efficient.
- **Compact and Stable**: Fits within the 20cm cube with a low center of gravity.
- **Enhanced Maneuverability**: Turns efficiently within a **40cm outside circle**.
- **Safe, Modular Assembly**: Assembled with screws and zip ties, allowing easy repairs and modifications.

*Image of Third DIY Robot Version:*

![Third DIY Robot](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/main/images/Third_DIY_Robot.png)

### Challenges and Lessons Learned

Each iteration taught us valuable lessons:
- **Prototyping with Readily Available Components**: Building with accessible materials helped in easy adjustments and redesigns.
- **Importance of Stability and Size**: Compactness and a low center of gravity are essential for performance on competitive courses.
- **Differential Systems Matter**: Efficient turning systems are critical in competitive environments.

## 3D CAD Modeling - Onshape

We used **Onshape** as our primary CAD tool, chosen for its cloud-based, collaborative features and accessibility.

### Why We Chose Onshape

- **Real-Time Collaboration**: Multiple users can work on the design, ensuring fast feedback and iteration.
- **Browser-Based**: No high-end hardware needed, enabling team access from any device.
- **Educational Access**: Onshape’s free plan for educational use provided all the necessary tools.
- **Version Control and Iteration**: Enabled easy tracking of design changes.

*Learn more about Onshape here: [Onshape Website](https://www.onshape.com/)*

## 3D Printing

We chose **3D printing** as our primary manufacturing method due to its flexibility and efficiency.

### Why We Chose 3D Printing

- **Complex Geometries**: 3D printing allows for intricate designs that other methods can't achieve.
- **Quick Prototyping**: Enabled rapid iterations and testing of parts.
- **Cost-Effective**: Reduced waste and cost compared to CNC engraving.

### Printer of Choice: Creality K1 Max

We used the **Creality K1 Max** for its:
- **Large Build Volume**: Capable of printing large components in one go.
- **High Precision and Speed**: Ensured accurate parts and faster turnaround times.

*Learn more about the Creality K1 Max here: [Creality K1 Max Printer](https://www.creality.com/products/creality-k1-max-3d-printer)*

## Robot Assembly and Systems

|                   | Robot                                                         |
|-------------------|---------------------------------------------------------------|
| Robot Dimensions  | ![Robot Dimensions](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/main/Models/Drawing%20Dimensions%20Robot.png) |
| Robot Assembly    | ![Robot Assembly](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/main/Models/Drawing%20Parts%20Robot.png) |
| Robot View        | ![Robot View](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/main/Models/Drawing%20Views%20Robot.png) |

### Power System

|                   | Power System                                                 |
|-------------------|--------------------------------------------------------------|
| Power System Assembly | ![Power System Assembly](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/main/Models/Drawing%20Assembly%20Power%20Animation.png) |
| Power System View     | ![Power System View](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/main/Models/Drawing%20Assembly%20Power.png) |

### Steering System

|                   | Steering System                                              |
|-------------------|--------------------------------------------------------------|
| Steering System Assembly | ![Steering System Assembly](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/main/Models/Drawing%20Assembly%20Steering%20Animation.png) |
| Steering System View     | ![Steering System View](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/main/Models/Drawing%20Assembly%20Steering.png) |

## Robot Parts Details

| Part Name                           | Image                                                                                     | 3D File Link                                                                                       |
|-------------------------------------|-------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------|
| 0x00- Robot Base                    | ![Robot Base](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/main/images/Images%20Isometric/0x00-Isometric%20Robot%20Base.png) | [Part Details](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/tree/main/Models/Parts/0x00-Robot%20Base) |
| 0x01- Second Layer                  | ![Second Layer](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/main/images/Images%20Isometric/0x01-Isometric%20Second%20Layer.png) | [Part Details](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/tree/main/Models/Parts/0x01-Second%20Layer) |

*[Further parts listed similarly]*

## Conclusion

Our **WRO Future Engineers robot project** combines thoughtful design, precise CAD modeling with **Onshape**, and efficient manufacturing via **3D printing** with the **Creality K1 Max**. These tools enabled our team to design, iterate, and build a robust robot ready to compete on the global stage.

Thank you for following our journey as we strive to represent **Morocco** in the **World Robot Olympiad**!

For more details, check our [Project Link](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International).
