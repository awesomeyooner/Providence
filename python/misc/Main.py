import cv2
import os
import time
from flask import Flask, request, render_template, render_template_string, Response, jsonify
from src.CameraManager import CameraManager
from src.Constants import CameraConstants

app = Flask(__name__)
camera = CameraManager(0, 30)

def gen():    

    while True:
        ret, image = camera.getFrame()

       
        yield (b'--frame\r\n'
            b'Content-Type: image/jpeg\r\n\r\n' + camera.compressFrame(image) + b'\r\n')
    
    camera.release()

@app.route('/')
def index():
    """Video streaming"""
    return render_template('index.html')

@app.route('/video_feed')
def video_feed():
    """Video streaming route. Put this in the src attribute of an img tag."""
    return Response(gen(),
                mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/framerate', methods =["GET", "POST"])
def framerate():
    return jsonify(value=camera.getFPS())

@app.route('/framerate_limit', methods=['GET', 'POST'])
def limitFPS():
    if(request.method == 'POST'):
        camera.setFramerateLimit(
            request.get_json(force=True).get('fps')
        )
    
    return jsonify(value=camera.getFramerateLimit())

@app.route('/name')
def name():
    return 

if __name__ == '__main__':
    # app.run(host="0.0.0.0", port="5801")
    app.run(port="5801")