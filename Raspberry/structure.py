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

section1 = {'section': 1, 'note': "", 'length': 0, 'position': 0}
section2 = {'section': 2, 'note': "", 'length': 0, 'position': 0}
section3 = {'section': 3, 'note': "", 'length': 0, 'position': 0}
section4 = {'section': 4, 'note': "", 'length': 0, 'position': 0}
section5 = {'section': 5, 'note': "", 'length': 0, 'position': 0}
section6 = {'section': 6, 'note': "", 'length': 0, 'position': 0}
section7 = {'section': 7, 'note': "", 'length': 0, 'position': 0}
section8 = {'section': 8, 'note': "", 'length': 0, 'position': 0}

sections=[section1, section2, section3, section4, section5, section6, section7, section8]

#Initialization over


def get_highest(values):
    max_value = max(values)
    max_index = values.index(max_value)
    counter=0
    for y in range(0,4):
        if values[y]>35:
            counter+=1
    return counter
            
#    print("max value" + str(max_value))
#    print("max_index" + str(max_index))
#    print("")

while True:
    for x in range(0,4):#populating dictonaries with randoms#AMOUNT OF SECTIONS
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
        for i in range (0,3):#AMOUNT OF SECTIONS
            amount_values=0
            sum_values=[0,0,0,0,0,0,0,0]
            while ser.inWaiting()>0:
                line = ser.readline()
                #print(line)
                valid=line.split(b',')
                if len(valid)!=4:#AMOUNT OF SECTIONS
                    print("a")
                    continue
                values=[int(x) for x in valid]
                sum_values=[a + b for a, b in zip(values, sum_values)]
                amount_values+=1

            #print(sum_values)
            print(values)
            activated=get_highest(values)
            current_section=sorted_sections[i]['section']
            print("note " + str(i+1))#debug text so I don't lose myself
            print("current section: " + str(current_section))
            print(sorted_sections[i])
            print("")
            sleep(1)
        bar+=1
        
