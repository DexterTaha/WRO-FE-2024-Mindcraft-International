ctx = canvas.getContext('2d');

canvas.width = 3100;
canvas.height = 3100;
ctx.scale(10,10);

const redPillar = 'rgba(238,39,55,1)';
const greenPillar = 'rgba(68,214,44,1)';
const orangeLine = 'rgba(255,102,0,1)';
const blueLine = 'rgba(0,51,255,1)';
var resetField = function(){
    canvas.width = 3100;
    canvas.height = 3100;
    ctx.scale(10,10);
    ctx.clearRect(0, 0, 310, 310);
    ctx.fillStyle = 'rgba(255, 255, 255, 1)';
    ctx.fillRect(0, 0, 310, 310);
    ctx.translate(155,155);
    for (let i = 0; i < 4; i++) {
        ctx.translate(50, 50);
        ctx.rotate(Math.PI/6);
        ctx.fillStyle = orangeLine;
        ctx.fillRect(-3, -1.5, 120, 3);
        ctx.rotate(Math.PI/6);
        ctx.fillStyle = blueLine;
        ctx.fillRect(-3, -1.5, 120, 3);
        ctx.rotate(-Math.PI/3);
        ctx.translate(-50, -50);
        ctx.rotate(-Math.PI/2);
    }
    ctx.translate(-155,-155);
    ctx.fillStyle = 'rgba(0,0,0,1)';
    ctx.fillRect(0,0,310,5);
    ctx.fillRect(305,0,5,310);
    ctx.fillRect(0,305,310,5);
    ctx.fillRect(0,0,5,310);
    ctx.fillRect(105,105,100,100);
    for(var i = 0;i < 4;i++){
        drawPillarCircle(105,45);
        drawPillarCircle(105,65);
        drawPillarCircle(155,45);
        drawPillarCircle(155,65);
        drawPillarCircle(205,45);
        drawPillarCircle(205,65);
        ctx.translate(155,155);
        ctx.rotate(0.5 * Math.PI);
        ctx.translate(-155,-155);
    }
    ctx.fillStyle = 'rgba(0, 0, 0, 0.3)';
    ctx.fillRect(104.5, 44.5, 101, 1);
    ctx.fillRect(104.5, 64.5, 101, 1);
    ctx.fillRect(0, 104.5, 310, 1);
    ctx.fillRect(0, 154.5, 310, 1);
    ctx.fillRect(0, 204.5, 310, 1);
    ctx.fillRect(104.5, 244.5, 101, 1);
    ctx.fillRect(104.5, 264.5, 101, 1);
    ctx.translate(155,155);
    ctx.rotate(0.5*Math.PI);
    ctx.translate(-155,-155);
    ctx.fillRect(104.5, 44.5, 101, 1);
    ctx.fillRect(104.5, 64.5, 101, 1);
    ctx.fillRect(0, 104.5, 310, 1);
    ctx.fillRect(0, 154.5, 310, 1);
    ctx.fillRect(0, 204.5, 310, 1);
    ctx.fillRect(104.5, 244.5, 101, 1);
    ctx.fillRect(104.5, 264.5, 101, 1);
}
var drawPillarCircle = function(x,y){
    ctx.fillStyle = 'rgba(0,0,0,0.3)';
    ctx.strokeStyle = 'rgba(0,0,0,0.3)';
    ctx.fillRect(x - 1,y - 1,2,2);
    ctx.beginPath();
    ctx.arc(x,y,4,0,2 * Math.PI);
    ctx.stroke();
}
var drawStartingPosition = function(rotations,position,direction){
    ctx.fillStyle = 'rgba(255,255,0,0.5)';
    ctx.translate(155,155);
    ctx.rotate(0.5 * Math.PI * rotations);
    if(position === 0){
        ctx.fillRect(-50,-150,50,40);
        if(direction === 0){
            ctx.fillStyle = 'rgba(0,255,255,0.5)';
            ctx.fillRect(-50,-150,10,40);
        }
        else{
            ctx.fillStyle = 'rgba(0,255,255,0.5)';
            ctx.fillRect(-10,-150,10,40);
        }
    }
    else if(position === 1){
        ctx.fillRect(0,-150,50,40);
        if(direction === 0){
            ctx.fillStyle = 'rgba(0,255,255,0.5)';
            ctx.fillRect(0,-150,10,40);
        }
        else{
            ctx.fillStyle = 'rgba(0,255,255,0.5)';
            ctx.fillRect(40,-150,10,40);
        }
    }
    else if(position === 2){
        ctx.fillRect(-50,-110,50,20);
        if(direction === 0){
            ctx.fillStyle = 'rgba(0,255,255,0.5)';
            ctx.fillRect(-50,-110,10,20);
        }
        else{
            ctx.fillStyle = 'rgba(0,255,255,0.5)';
            ctx.fillRect(-10,-110,10,20);
        }
    }
    else if(position === 3){
        ctx.fillRect(0,-110,50,20);
        if(direction === 0){
            ctx.fillStyle = 'rgba(0,255,255,0.5)';
            ctx.fillRect(0,-110,10,20);
        }
        else{
            ctx.fillStyle = 'rgba(0,255,255,0.5)';
            ctx.fillRect(40,-110,10,20);
        }
    }
    else if(position === 4){
        ctx.fillRect(-50,-90,50,40);
        if(direction === 0){
            ctx.fillStyle = 'rgba(0,255,255,0.5)';
            ctx.fillRect(-50,-90,10,40);
        }
        else{
            ctx.fillStyle = 'rgba(0,255,255,0.5)';
            ctx.fillRect(-10,-90,10,40);
        }
    }
    else if(position === 5){
        ctx.fillRect(0,-90,50,40);
        if(direction === 0){
            ctx.fillStyle = 'rgba(0,255,255,0.5)';
            ctx.fillRect(0,-90,10,40);
        }
        else{
            ctx.fillStyle = 'rgba(0,255,255,0.5)';
            ctx.fillRect(40,-90,10,40);
        }
    }
    ctx.rotate(-0.5 * Math.PI * rotations);
    ctx.translate(-155,-155);
}
var drawPillar = function(color,rotations,position){
    ctx.fillStyle = color;
    ctx.translate(155,155);
    ctx.rotate(0.5 * Math.PI * rotations);
    if(position === 0){
        ctx.fillRect(-52.5,-112.5,5,5);
    }
    else if(position === 1){
        ctx.fillRect(-2.5,-112.5,5,5);
    }
    else if(position === 2){
        ctx.fillRect(47.5,-112.5,5,5);
    }
    else if(position === 3){
        ctx.fillRect(-52.5,-92.5,5,5);
    }
    else if(position === 4){
        ctx.fillRect(-2.5,-92.5,5,5);
    }
    else if(position === 5){
        ctx.fillRect(47.5,-92.5,5,5);
    }
    ctx.rotate(-0.5 * Math.PI * rotations);
    ctx.translate(-155,-155);
}

resetField();

randomiseWithoutPillars.onclick = function(){
    resetField();
    startX = 0;
    startY = 0;
    endX = 0;
    endY = 0;
    if(Math.random() < 0.5){
        startX = 105;
    }
    else{
        startX = 65;
    }
    if(Math.random() < 0.5){
        startY = 105;
    }
    else{
        startY = 65;
    }
    if(Math.random() < 0.5){
        endX = 205;
    }
    else{
        endX = 245;
    }
    if(Math.random() < 0.5){
        endY = 205;
    }
    else{
        endY = 245;
    }
    ctx.fillStyle = 'rgba(0,0,0,1)';
    ctx.fillRect(startX,startY,endX - startX,endY - startY);
    startingLocation = Math.floor(Math.random() * 4);
    if(startingLocation === 0){
        if(startY === 105){
            startingPosition = Math.floor(Math.random() * 6);
            drawStartingPosition(0,startingPosition,Math.floor(Math.random() * 2));
        }
        else{
            startingPosition = Math.floor(Math.random() * 4);
            drawStartingPosition(0,startingPosition,Math.floor(Math.random() * 2));
        }
    }
    else if(startingLocation === 1){
        if(endX === 205){
            startingPosition = Math.floor(Math.random() * 6);
            drawStartingPosition(1,startingPosition,Math.floor(Math.random() * 2));
        }
        else{
            startingPosition = Math.floor(Math.random() * 4);
            drawStartingPosition(1,startingPosition,Math.floor(Math.random() * 2));
        }
    }
    else if(startingLocation === 2){
        if(endY === 205){
            startingPosition = Math.floor(Math.random() * 6);
            drawStartingPosition(2,startingPosition,Math.floor(Math.random() * 2));
        }
        else{
            startingPosition = Math.floor(Math.random() * 4);
            drawStartingPosition(2,startingPosition,Math.floor(Math.random() * 2));
        }
    }
    else if(startingLocation === 3){
        if(startX === 105){
            startingPosition = Math.floor(Math.random() * 6);
            drawStartingPosition(3,startingPosition,Math.floor(Math.random() * 2));
        }
        else{
            startingPosition = Math.floor(Math.random() * 4);
            drawStartingPosition(3,startingPosition,Math.floor(Math.random() * 2));
        }
    }
}
randomiseWithPillars.onclick = function(){
    resetField();
    let straightSection = Math.floor(Math.random() * 4);
    let sections = [
        [[1,5]],
        [[0,5]],
        [[1,4]],
        [[0,4]],
        [[1,3]],
        [[0,3]],
        [[1,2]],
        [[0,2]],
        [[1,1]],
        [[0,1]],
        [[1,0]],
        [[0,0]],

        [[1,2],[1,3]],
        [[1,2],[0,3]],
        [[0,2],[1,3]],
        [[1,2],[0,3]],
        [[0,2],[1,3]],
        [[0,2],[0,3]],
        
        [[1,0],[1,5]],
        [[1,0],[0,5]],
        [[0,0],[1,5]],
        [[1,0],[0,5]],
        [[0,0],[1,5]],
        [[0,0],[0,5]],
        
        [[1,3],[1,5]],
        [[1,3],[0,5]],
        [[0,3],[1,5]],
        [[1,3],[0,5]],
        [[0,3],[1,5]],
        [[0,3],[0,5]],
        
        [[1,0],[1,2]],
        [[1,0],[0,2]],
        [[0,0],[1,2]],
        [[1,0],[0,2]],
        [[0,0],[1,2]],
        [[0,0],[0,2]],
    ];
    let pillarLocations = [
        "",
        "",
        "",
        "",
    ];
    let drawLocations = [];
    if(Math.random() < 0.5){
        drawLocations.push([redPillar,straightSection,1]);
        sections.splice(9,1);
    }
    else{
        drawLocations.push([greenPillar,straightSection,1]);
        sections.splice(8,1);
    }
    pillarLocations[straightSection] = "center";
    for(var i = straightSection + 1;i < straightSection + 4;i++){
        let randomSection = Math.floor(Math.random() * sections.length);
        let numberOfPillars = 0;
        var position = 0;
        for(var j in sections[randomSection]){
            position = sections[randomSection][j][1];
            if(sections[randomSection][j][0] === 0){
                drawLocations.push([redPillar,i,sections[randomSection][j][1]]);
            }
            else{
                drawLocations.push([greenPillar,i,sections[randomSection][j][1]]);
            }
            numberOfPillars += 1;
        }
        if(numberOfPillars === 2){
            pillarLocations[i % 4] = "both";
        }
        else{
            if(position === 0 || position === 3){
                pillarLocations[i % 4] = "right";
            }
            if(position === 1 || position === 4){
                pillarLocations[i % 4] = "center";
            }
            if(position === 2 || position === 5){
                pillarLocations[i % 4] = "left";
            }
        }
        sections.splice(randomSection,1);
    }
    let startingLocation = Math.floor(Math.random() * 4);
    if(pillarLocations[startingLocation] === "both"){
        if(Math.random() < 0.5){
            drawStartingPosition(startingLocation,2,1);
        }
        else{
            drawStartingPosition(startingLocation,3,0);
        }
    }
    if(pillarLocations[startingLocation] === "left"){
        startingPosition = Math.floor(Math.random() * 3);
        if(startingPosition === 0){
            drawStartingPosition(startingLocation,2,1);
        }
        else if(startingPosition === 1){
            drawStartingPosition(startingLocation,3,1);
        }
        else{
            drawStartingPosition(startingLocation,3,0);
        }
    }
    if(pillarLocations[startingLocation] === "center"){
        startingPosition = Math.floor(Math.random() * 2);
        if(startingPosition === 0){
            drawStartingPosition(startingLocation,2,0);
        }
        else{
            drawStartingPosition(startingLocation,3,1);
        }
    }
    if(pillarLocations[startingLocation] === "right"){
        startingPosition = Math.floor(Math.random() * 3);
        if(startingPosition === 0){
            drawStartingPosition(startingLocation,2,1);
        }
        else if(startingPosition === 1){
            drawStartingPosition(startingLocation,2,0);
        }
        else{
            drawStartingPosition(startingLocation,3,0);
        }
    }
    for (let location of drawLocations) {
        drawPillar(location[0], location[1], location[2]);
    }
}

reset.onclick = resetField;

window.onresize = function() {
    if (window.innerWidth > 3000) {
        document.getElementById('rickastley').style.display = 'block';
    } else {
        document.getElementById('rickastley').style.display = 'none';
    }
}





document.getElementById("section").addEventListener("change", updateRedPartialOptions);

function updateRedPartialOptions() {
    let section = parseInt(document.getElementById("section").value);
    let laps = document.getElementById("laps");

}

document.getElementById("finishSection").addEventListener("change", updateRedPartialOptionse);

function updateRedPartialOptionse() {
    let finishSection = parseInt(document.getElementById("finishSection").value);
    let movedSigns = document.getElementById("movedSigns");
}

document.getElementById("direction").addEventListener("change", updatecableCompleteOptions);

function updatecableCompleteOptions() {
    let parkSuc = document.getElementById("parkSuc");
    let cableCompleteValue = parseInt(document.getElementById("direction").value);
}

document.getElementById("parkSuc").addEventListener("change", updatecableTouchingOptions);

function updatecableTouchingOptions() {
    let direction = document.getElementById("direction");
    let cableTouchingValue = parseInt(document.getElementById("parkSuc").value);
}

  
  

document.getElementById("section").addEventListener("change", updateRedPartialOptions);
document.getElementById("finishSection").addEventListener("change", updateRedPartialOptionse);
document.getElementById("direction").addEventListener("change", updatecableCompleteOptions);
document.getElementById("parkSuc").addEventListener("change", updatecableTouchingOptions);
document.getElementById('calculatorForm').addEventListener('change', calculatePoints);


function calculatePoints() {
    const section = parseInt(document.getElementById("section").value) * 1;
    const laps = parseInt(document.getElementById("laps").value) * 1;
    const finishSection = parseInt(document.getElementById("finishSection").value);
    const movedSigns = parseInt(document.getElementById("movedSigns").value);
    const notMovedSigns = parseInt(document.getElementById('notMovedSigns').value);
    const moved3Laps = parseInt(document.getElementById("moved3Laps").value);
    const still3Laps = parseInt(document.getElementById("still3Laps").value);
    const parkSuc = parseInt(document.getElementById("parkSuc").value);
    const direction = parseInt(document.getElementById("direction").value);
    const parkPart = parseInt(document.getElementById("parkPart").value);
    const takeOut = parseInt(document.getElementById("takeOut").value);
    const disqualified = parseInt(document.getElementById("disqualified").value);


    let totalPoints = section + laps + finishSection + movedSigns + notMovedSigns + moved3Laps + still3Laps + parkSuc + direction + parkPart + takeOut + disqualified;

    if (takeOut === 1) {
        totalPoints = (totalPoints / 2) - 0.5; // Divide by 2 if takeOut is Yes
    }

    if (disqualified === 1) {
        totalPoints = 0; // Set total points to 0 if disqualified is Yes
    }

    document.getElementById("totalPoints").innerHTML = totalPoints + " ";
    displayRemark(totalPoints);

    

}

function resetForm() {
    document.getElementById("section").value = "0";
    document.getElementById("laps").value = "0";
    document.getElementById("finishSection").value = "0";
    document.getElementById("movedSigns").value = "0";
    document.getElementById('notMovedSigns').value = "0";
    document.getElementById("moved3Laps").value = "0";
    document.getElementById("still3Laps").value = "0";
    document.getElementById("parkSuc").value = "0";
    document.getElementById("direction").value = "0";
    document.getElementById("parkPart").value = "0";
    document.getElementById("takeOut").value = "0";
    document.getElementById("disqualified").value = "0";
    document.getElementById("totalPoints").innerHTML = "0 / 100";
    updateRedPartialOptions();
}




let timer;
let time = 0;

function startChrono() {
    stopChrono(); // Stop any existing timer
    timer = setInterval(updateChrono, 1000);
}

function stopChrono() {
    clearInterval(timer);
}

function resetChrono() {
    stopChrono();
    time = 0;
    document.getElementById('time').textContent = formatTime(time);
    document.getElementById('pointsOverTime').textContent = '0 points in 00:00';
}

function updateChrono() {
    time++;
    document.getElementById('time').textContent = formatTime(time);
    updatePointsOverTime(); // Update points over time display
    if (time >= 180) {
        stopChrono();
        document.getElementById('Sound').play(); // Play the alarm sound
    }
}

function formatTime(seconds) {
    const minutes = Math.floor(seconds / 60);
    const remainingSeconds = seconds % 60;
    return `${minutes.toString().padStart(2, '0')}:${remainingSeconds.toString().padStart(2, '0')}`;
}



function updatePointsOverTime() {
    const points = document.getElementById('totalPoints').textContent;
    const timeText = document.getElementById('time').textContent;
    document.getElementById('pointsOverTime').textContent = `${points} points in ${timeText}`;
}
function displayRemark(totalPoints) {
    const remarkText = document.getElementById('remarkText');
    if (totalPoints >= 0 && totalPoints <= 30) {
        remarkText.textContent = "Your result is bad, you must practice";
        remarkText.style.color = "red";
    } else if (totalPoints > 30 && totalPoints <= 60) {
        remarkText.textContent = "You're improving, keep working hard!";
        remarkText.style.color = "orange";
    } else if (totalPoints > 60 && totalPoints <= 90) {
        remarkText.textContent = "Great job! Keep it up!";
        remarkText.style.color = "blue";
    } else if (totalPoints > 90 && totalPoints <= 120) {
        remarkText.textContent = "Well done! You’re doing awesome!";
        remarkText.style.color = "green";
    }
}

function resetAll() {
    document.getElementById('calculatorForm').reset();
    document.getElementById('totalPoints').textContent = '0';
    document.getElementById('time').textContent = '00:00';
    document.getElementById('pointsOverTime').textContent = '0 points in 00:00';
    document.getElementById('remarkText').textContent = '';
    resetChrono(); // Reset the chronometer
}


