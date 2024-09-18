import cv2
import os
from flask import Flask, request, render_template, render_template_string, Response

app = Flask(__name__)
video_capture = cv2.VideoCapture(0)

def gen():    
    while True:
        ret, image = video_capture.read()
        cv2.imwrite('t.jpg', image)
        yield (b'--frame\r\n'
           b'Content-Type: image/jpeg\r\n\r\n' + open('t.jpg', 'rb').read() + b'\r\n')
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

# end of video stream

@app.route('/name', methods =["GET", "POST"])
def name():
    # if request.method == "POST":
    #    # getting input with name = fname in HTML form
    #     first_name = request.form.get("fname")

        
    #     return "Your name is "+ first_name

    first_name = request.form.get('fname')
    return render_template("index.html", firstname =first_name)

# @app.route('/name', methods =["GET", "POST"])
# def bob():
#     return render_template('index.html', value=)


if __name__ == '__main__':
    app.run()