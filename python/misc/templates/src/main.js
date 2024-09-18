var ctx = document.getElementById("canvas").getContext('2d');
var img = new Image();
img.src = "{{ url_for('video_feed') }}";

// need only for static image
//img.onload = function(){   
//    ctx.drawImage(img, 0, 0);
//};

// need only for animated image
function refreshCanvas(){
    ctx.drawImage(img, 0, 0);
};

window.setInterval("refreshCanvas()", 50);

$(document).ready(function() {
    function fetchDoubleValue() {
        $.ajax({
            url: '/get_double',
            method: 'GET',
            success: function(data) {
                $('#double-value').text(data.value);
            },
            error: function(error) {
                console.error("Error fetching double value:", error);
            }
        });
    }

    // Fetch the double value every 2 seconds (2000 ms)
    setInterval(fetchDoubleValue, 2000);
});