
var ctx = document.getElementById("canvas").getContext('2d');
var img = new Image();
img.src = videoFeedUrl;

// need only for static image
//img.onload = function(){   
//    ctx.drawImage(img, 0, 0);
//};

const redIn = document.getElementById('red in');
const redOut = document.getElementById('red out');

const fpsIn = document.getElementById('fps in');
const fpsOut = document.getElementById('fps out');

function updateFPS() {
    fpsOut.innerText = fpsIn.value;
}

fpsIn.addEventListener("input", updateFPS);

function updateRed() {
    redOut.innerText = redIn.value;
}

redIn.addEventListener("input", updateRed);
// need only for animated image
function refreshCanvas(){
    ctx.drawImage(img, 0, 0);
};

window.setInterval("refreshCanvas()", 50);

$(document).ready(function() {
    function update(){
        recieveFramerate()
        sendFramerateLimit()
        recieveFramerateLimit()
    }

    function recieveFramerate() {
        $.ajax({
            url: '/framerate',
            method: 'GET',
            success: function(data) {
                $('#framerate').text(data.value);
            },
            error: function(error) {
                console.error("Error fetching double value:", error);
            }
        });
    }

    function recieveFramerateLimit() {
        $.ajax({
            url: '/framerate_limit',
            method: 'GET',
            success: function(data) {
                $('#framerate_limit').text(data.value);
            },
            error: function(error) {
                console.error("Error fetching double value:", error);
            }
        });
    }

    function sendFramerateLimit(){
        $.ajax({
            url: '/framerate_limit',
            method: 'POST',
            data: JSON.stringify({
                "fps": fpsIn.value
            }),
            contentType: "application/json; charset=utf-8",
            traditional: true,

            success: function(data) {
                $('#framerate_limit').text(data.fps);
            },
            error: function(error) {
                console.error("Error fetching double value:", error);
            }
        });
    }

    // Fetch the double value every 2 seconds (2000 ms)
    setInterval(update, 50);
});