import serial
from time import sleep

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


while(True):
    
        
    for i in range (150, 35, -1):
        
        send = str(i*0.01) + '\n'
        send = bytes(send, encoding = 'utf-8')
        print(send)
        ser.write(send)
        #ser.flush()
        sleep(0.2)
    
    sleep(1)
    


        
