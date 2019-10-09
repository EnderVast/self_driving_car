import picamera
import os
from time import sleep
from datetime import datetime

current_dir = os.getcwd()

camera = picamera.PiCamera()
camera.resolution = (640, 480)
camera.framerate = 24
sleep(1)


frames = 300

def filenames():
    frame = 0
    while frame < frames:
        yield '{}.jpg'.format(datetime.now())
        frame += 1
        
#start recording
try:
    os.mkdir(current_dir + '/recorded_images')
    os.chdir(current_dir + '/recorded_images')
except:
    os.chdir(current_dir + '/recorded_images')

print('Saving images in: ', os.getcwd())
camera.start_preview()
sleep(2)
camera.capture_sequence(filenames(), use_video_port = True)
