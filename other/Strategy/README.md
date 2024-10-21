
# Robot Strategy for WRO Future Engineers

In this competition, our robot needs to figure out where to go and how to avoid obstacles using **sensors** like LiDAR and a camera. Here’s how it works:

---

## 1. **Understanding the Zones**

- There are special shapes on the board: two **X-shapes** and four **T-shapes**. These are called **Zones**.
- Our robot uses **4 sensors** to find out where these Zones are.
- After that, the robot locates itself based on these zones and gets ready to move!

---

## 2. **Looking for Obstacles**

- There are **24 possible places** where obstacles could be. We call them **P1, P2, P3, … up to P24**.
- The robot **pretends** these obstacles are there and checks their actual location using a **LiDAR sensor** (like a robot eye!).
- Then it uses a **camera** to figure out the color of the obstacles:
  - **Red** = Dangerous
  - **Green** = Safe
  - **None** = No obstacle

---

## 3. **Storing the Information**

- Each place, like P1, P2, etc., gets a value:
  - If there’s **no obstacle**, the value is **0**.
  - If there’s a **Green obstacle**, the value is **1**.
  - If there’s a **Red obstacle**, the value is **2**.
  
For example:
