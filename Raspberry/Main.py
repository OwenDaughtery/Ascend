from psonic import *
from serial import *
from time import sleep

import serial.tools.list_ports
port = list(serial.tools.list_ports.comports())[0][0]



ser = serial.Serial(port, 9600)
val = 0

while True:
<<<<<<< HEAD
        while ser.inWaiting()>0:
                line = ser.readline()
                valid=line.split(b',')
                if len(valid)!=8:
                        continue
=======
	while ser.inWaiting()>0:
		val = int(ser.readline())
	print( val )
	sample(PERC_BELL,rate=0.5)
	time.sleep(0.7)
	
>>>>>>> baf93cca2cdac95593cf89f2d33547b25b610028

                values=[int(x) for x in valid]
                print(values)
                #sample(PERC_BELL,rate=0.5)
                #time.sleep(0.1)

