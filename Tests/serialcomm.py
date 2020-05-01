import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)
from time import sleep
import serial

address = '/dev/ttyUSB'
steering_angles = []
is_recording = False
buttonPin = 16

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
sleep(2)

while(True):
    if ser.inWaiting() > 0:
        incoming_data = ord(ser.read())         
        steering_angles.append(incoming_data)
        print('Steering angle: ', incoming_data)
        ser.reset_input_buffer()
            
        
        
        
