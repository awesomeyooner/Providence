import cv2
import os
import time
from flask import Flask, request, render_template, render_template_string, Response, jsonify

app = Flask(__name__)
video_capture = cv2.VideoCapture(0)

prevTime = 0
framerate_cap = 20
framerate = 0

def gen():    
    global prevTime
    global framerate
    global framerate_cap

    while True:
        ret, image = video_capture.read()
        
        _, buffer = cv2.imencode('.jpg', image)
        frame = buffer.tobytes()
        framerate = 1 / (time.time() - prevTime)
        prevTime = time.time()
        yield (b'--frame\r\n'
           b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')
        
    video_capture.release()

@app.route('/')
def index():
    """Video streaming"""
    return render_template('index.html')

@app.route('/video_feed')
def video_feed():
    """Video streaming route. Put this in the src attribute of an img tag."""
    return Response(gen(),
                mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/mynumber', methods =["GET", "POST"])
def mynumber():
    return jsonify(value=framerate_cap)

@app.route('/limitFPS', methods=['GET', 'POST'])
def limitFPS():
    global framerate_cap

    if(request.method == 'POST'):
        framerate_cap = request.get_json(force=True).get('fps')
    
    return "success"

@app.route('/name')
def name():
    return 

if __name__ == '__main__':
    app.run(host="0.0.0.0", port="5801")