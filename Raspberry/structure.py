from time import *
from random import randint
from operator import itemgetter
from psonic import *
from serial import *
import serial.tools.list_ports
port = list(serial.tools.list_ports.comports())[0][0]
ser = serial.Serial(port, 9600)
val = 0

notes=['A3', 'B3', 'D4', 'E4', 'Fs4', 'A4', 'B4', 'D5']
lengths=[1.5, 1.4, 1.3, 1.2, 1.1, 1]
position=[1,2,3,4,5,6,7,8]

section1 = {'note': "", 'length': 0, 'position': 0}
section2 = {'note': "", 'length': 0, 'position': 0}
section3 = {'note': "", 'length': 0, 'position': 0}
section4 = {'note': "", 'length': 0, 'position': 0}
section5 = {'note': "", 'length': 0, 'position': 0}
section6 = {'note': "", 'length': 0, 'position': 0}
section7 = {'note': "", 'length': 0, 'position': 0}
section8 = {'note': "", 'length': 0, 'position': 0}

sections=[section1, section2, section3, section4, section5, section6, section7, section8]

#Initialization over

while True:
    for x in range(0,8):#populating dictonaries with randoms
        rand_note=notes[randint(0,7)]
        rand_length=lengths[randint(0,5)]
        rand_pos=position[randint(0,7)]        
        sections[x]['note']=rand_note
        sections[x]['length']=rand_length
        sections[x]['position']=rand_pos

    sorted_sections = sorted(sections, key=itemgetter("position"))#sort all dictionaries in order of their position
    bar=1
    for y in range (1,5):
        print(str(bar) + "th bar")
        for i in range (0,8):
            while ser.inWaiting()>0:
                val=int(ser.readline())
                print(val)
            #have if statement here registering whether the section is being touched and if so:
            print("note " + str(i+1))#debug text so I don't lose myself
            print(sorted_sections[i])
            sleep(1)
        bar+=1
        
        
