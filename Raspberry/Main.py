from psonic import *
from serial import *
from time import sleep

import serial.tools.list_ports
port = serial.tools.list_ports.comports()[0][0]



ser = serial.Serial(port, 9600)
val = 0

while True:
        while ser.inWaiting()>0:
                line = ser.readline()
                valid=line.split(b',')
                if len(valid)!=8:
                        continue

                values=[int(x) for x in valid]
                print(values)
                #sample(PERC_BELL,rate=0.5)
                #time.sleep(0.1)

