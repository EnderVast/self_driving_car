from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2

camera = PiCamera()

camera.resolution = (300, 100)
camera.framerate = 10
rawCapture = PiRGBArray(camera, size = (300, 100))

time.sleep(0.1)

for frame in camera.capture_continuous(rawCapture, format = "bgr", use_video_port = True):
    image = frame.array
    
    cv2.imshow("Frame", image)
    key = cv2.waitKey(1) & 0xFF
    
    rawCapture.truncate(0)
    time.sleep(0.02)
    print("h")
    if key == ord("q"):
        break