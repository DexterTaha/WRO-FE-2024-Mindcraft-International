# Future Engineers Map Randomizer and Score Calculator

This project provides an interactive web-based tool for the WRO Future Engineers competition. It combines a map randomizer and a score calculator, allowing participants to simulate various configurations of map elements and assess their robot's performance effectively.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Creating the Project](#creating-the-project)
  - [Step 1: Setting Up the HTML Structure](#step-1-setting-up-the-html-structure)
  - [Step 2: Styling the Application](#step-2-styling-the-application)
  - [Step 3: Adding JavaScript Logic](#step-3-adding-javascript-logic)
    - [Drawing the Map](#drawing-the-map)
    - [Randomization Logic](#randomization-logic)
    - [Chrono Functionality](#chrono-functionality)
  - [Step 4: Testing the Application](#step-4-testing-the-application)
- [Code Explanation](#code-explanation)
  - [HTML (index.html)](#html-indexhtml)
  - [CSS (style.css)](#css-stylescss)
  - [JavaScript (script.js)](#javascript-scriptjs)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Map Randomizer**: Automatically generates randomized layouts for obstacles and scoring zones.
  
- **Score Calculator**: Quickly calculates scores based on robot interactions with the map elements.

- **Chrono Timer**: Tracks the time taken for the robot to complete the course.

- **Responsive Design**: Built using HTML, CSS, and JavaScript.

- **User-Friendly Interface**: Intuitive design for easy navigation.

## Getting Started

### Prerequisites

To run this project, ensure you have a modern web browser installed, such as:

- Google Chrome
- Mozilla Firefox
- Apple Safari
- Microsoft Edge

### Installation

1. **Download the Repository**: Clone or download the repository to your local machine.
   
   ```bash
   git clone https://github.com/YOUR_USERNAME/WRO-FE-2024-Mindcraft-International.git
   ```

2 - **Open the Project**: Navigate to the project folder and open the `index.html` file in your web browser.

## Creating the Project
### Step 1: Setting Up the HTML Structure
1. **Create an index.html File**: Start by creating an HTML file. This will be the main structure of your web application.
2. **Add Basic HTML Structure**: Inside the `index.html`, include the basic HTML template and a title for your application. Use the following template:

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <title>Future Engineers Map Randomizer</title>
</head>
<body>
    <h1>Future Engineers Map Randomizer & Score Calculator</h1>
    <button id="randomizeBtn">Randomize Map</button>
    <div id="mapDisplay"></div>
    
    <h2>Score Calculation</h2>
    <label for="obstaclesAvoided">Obstacles Avoided:</label>
    <input type="number" id="obstaclesAvoided" placeholder="Enter number">
    <label for="pointsFromZones">Points from Scoring Zones:</label>
    <input type="number" id="pointsFromZones" placeholder="Enter points">
    <button id="calculateBtn">Calculate Score</button>
    <p id="result"></p>

    <h2>Chrono</h2>
    <button id="startChrono">Start Timer</button>
    <button id="stopChrono">Stop Timer</button>
    <p id="chronoDisplay">Time: 0s</p>
    
    <script src="script.js"></script>
</body>
</html>
```

### Step 2: Styling the Application
1. **Create a style.css File**: Create a CSS file in the project folder. This will control the visual appearance of your application.
2. **Add Basic Styles**: Use the following CSS code to provide basic styling for your layout. Customize as needed:

```css
body {
    font-family: Arial, sans-serif;
    text-align: center;
    background-color: #f4f4f4;
}

h1 {
    color: #333;
}

button {
    padding: 10px 15px;
    font-size: 16px;
    margin: 10px;
    cursor: pointer;
}

input {
    padding: 5px;
    margin: 10px;
    width: 50px;
}
```

### Step 3: Adding JavaScript Logic
1. **Create a script.js File**: Create a JavaScript file in your project folder. This will contain the logic for randomization, map drawing, and timer functionality.
2. **Add Event Listeners**: Use the following code to handle user interactions such as randomizing the map, calculating the score, and starting/stopping the timer:

```javascript
let timerInterval;
let seconds = 0;

document.getElementById('randomizeBtn').addEventListener('click', function() {
    const mapDisplay = document.getElementById('mapDisplay');
    const randomMap = generateRandomMap();
    mapDisplay.innerHTML = randomMap;
});

document.getElementById('calculateBtn').addEventListener('click', function() {
    const obstaclesAvoided = document.getElementById('obstaclesAvoided').value;
    const pointsFromZones = document.getElementById('pointsFromZones').value;
    
    const totalScore = calculateScore(obstaclesAvoided, pointsFromZones);
    document.getElementById('result').innerText = `Total Score: ${totalScore}`;
});

document.getElementById('startChrono').addEventListener('click', function() {
    startTimer();
});

document.getElementById('stopChrono').addEventListener('click', function() {
    stopTimer();
});

function generateRandomMap() {
    const obstacles = ['Wall', 'Pit', 'Ramp'];
    const scoringZones = ['Zone A', 'Zone B', 'Zone C'];
    let mapLayout = '';

    for (let i = 0; i < 5; i++) {
        const randomObstacle = obstacles[Math.floor(Math.random() * obstacles.length)];
        const randomZone = scoringZones[Math.floor(Math.random() * scoringZones.length)];
        mapLayout += `<div>${randomObstacle} | ${randomZone}</div>`;
    }

    return mapLayout;
}

function calculateScore(obstacles, points) {
    const pointsForObstacles = 10; // Example points for each obstacle avoided
    return parseInt(points) + (pointsForObstacles * parseInt(obstacles));
}

function startTimer() {
    timerInterval = setInterval(() => {
        seconds++;
        document.getElementById('chronoDisplay').innerText = `Time: ${seconds}s`;
    }, 1000);
}

function stopTimer() {
    clearInterval(timerInterval);
}
```

#### Drawing the Map
In the `generateRandomMap()` function, we create a simple representation of the map by randomly selecting obstacles and scoring zones. The function constructs a string that includes random combinations of these elements, which is then displayed in the `mapDisplay` div.
#### Randomization Logic
The randomization works by selecting a random item from arrays of predefined obstacles and scoring zones. The code uses `Math.random()` and `Math.floor()` to ensure that a valid index is chosen each time a random element is requested.
#### Chrono Functionality
The chrono (timer) functionality is implemented with two main functions: `startTimer()` and `stopTimer()`. The `startTimer()` function sets an interval that increments a seconds counter every second, updating the display accordingly. The `stopTimer()` function clears this interval, effectively stopping the timer.

### Step 4: Testing the Application
1. **Open the Application**: After setting up the files, open `index.html` in your web browser to see the application in action.
2. **Interact with the Application**: Click the "Randomize Map" button to generate a new map layout, enter data in the input fields, calculate the score, and start/stop the timer to ensure everything works as expected.

## Code Explanation
## HTML (index.html)
The HTML file contains the basic structure for the application. It includes buttons for randomizing the map, calculating the score, and managing the timer, as well as input fields for user interaction.
## CSS (style.css)
The CSS file provides styles for the application. You can adjust colors, fonts, and layout to customize the appearance further.
## JavaScript (script.js)
The JavaScript file handles the logic for randomization, score calculation, and timer functionality. It listens for user actions and performs the corresponding operations, updating the displayed results.
---

## Website Preview
![website preview](https://github.com/DexterTaha/WRO-FE-2024-Mindcraft-International/blob/0fd944c4e0d555fc80da8dd42af44a5308ee50ac/images/randomizer_page.jpeg)








