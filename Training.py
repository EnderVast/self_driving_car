from time import sleep
from datetime import datetime
import RPi.GPIO as GPIO
import serial
import os
import picamera
import csv
import numpy as np

address = '/dev/ttyUSB'
current_dir = os.getcwd()
steering_angles = []
img_dir = []
imgs_dir = []
is_recording = False
buttonPin = 16
v = 0

GPIO.setmode(GPIO.BOARD)
GPIO.setup(buttonPin, GPIO.IN, pull_up_down = GPIO.PUD_UP)

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
    
ser.flushInput()
print('Arduino connected on USB', port)
sleep(0.5)
print('Press button to start recording training data')
camera = picamera.PiCamera()
camera.resolution = (600, 400)
camera.framerate = 10
camera.vflip = True

sleep(2)

def record_data():
    i = 0
    global is_recording
    global img_dir
    global steering_angles
    while is_recording == True:
              
        incoming_data = ord(ser.read())         
        steering_angles.append(incoming_data)
        img_dir.append(current_dir + '/recorded_images/' + '{}.jpg'.format(datetime.now()))
        print("Steering angle: ", incoming_data)
        yield img_dir[i]
        i += 1
        ser.reset_input_buffer()
        
        if GPIO.input(buttonPin) == False:
            is_recording = False
            print('Recording stopped. Press button to start again')
            sleep(2)
    

try:
    os.mkdir(current_dir + '/data')
    os.mkdir(current_dir + '/data/recorded_images')
    os.chdir(current_dir + '/data')
    current_dir = os.getcwd()

except:
    os.chdir(current_dir + '/data')
    current_dir = os.getcwd()

while(True):

    if GPIO.input(buttonPin) == False and is_recording == False:
        print('Recording started. Press button to stop')
        print('Saving images in: ', os.getcwd() + 'recorded_images')
        camera.start_preview()
        sleep(1)
        is_recording = True
        
   
    while is_recording == True:
        
        if ser.inWaiting() > 0:
            camera.capture_sequence(record_data(), use_video_port = True)
            os.chdir(current_dir)
            with open('img_dir.csv', 'a') as imgdir:
                csv_writer = csv.writer(imgdir)
                for i in range(1, len(img_dir)):    #start from 1 because apparently first data steering angle always 0
                    csv_data = []
                    csv_data.append(img_dir[i])
                    csv_data.append(steering_angles[i])
                    csv_writer.writerow(csv_data)
                    
        elif v == 0:
            print("Error: no connection")
            v = 1
                    
                        

                  

            
            
            
        
        
            
        
        
        
