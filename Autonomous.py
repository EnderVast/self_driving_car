import keras
from keras.models import Sequential
from keras.models import load_model
from picamera.array import PiRGBArray
import cv2
import numpy as np
from picamera import PiCamera
from time import sleep
import RPi.GPIO as GPIO
import serial
import os

buttonPin = 16

camera = PiCamera()
camera.vflip = True
camera.resolution = (300, 100)
camera.framerate = 10
rawCapture = PiRGBArray(camera, size = (300, 100))

model = load_model("model.h5")

address = '/dev/ttyUSB'

try:
    ser = serial.Serial(address + '0', 115200)
    port = 0
except:
    pass

try:
    ser = serial.Serial(address + '1', 115200)
    port = 1
except:
    pass

try:
    ser = serial.Serial(address + '2', 115200)
    port = 2
except:
    pass

print('Arduino connected on USB', port)

sleep(0.5)

for frame in camera.capture_continuous(rawCapture, format = "bgr", use_video_port = True):
    image = frame.array
    key = cv2.waitKey(1) & 0xFF
    rawCapture.truncate(0)
    image = cv2.cvtColor(image, cv2.COLOR_BGR2YUV)
    image = cv2.GaussianBlur(image, (3, 3), 0)
    image = cv2.resize(image, (200, 66))
    cv2.imshow("Frame", image)
    image = image/255
    image = image.reshape(1, 66, 200, 3)
    result = model.predict(image)
    ser.write(result)
    print(result)
    sleep(0.02)
    if key == ord("q"):
        break
    
ser.close()
