from time import *
from random import randint
from operator import itemgetter
from psonic import *
from serial import *
import serial.tools.list_ports
port = list(serial.tools.list_ports.comports())[0][0]
ser = serial.Serial(port, 9600)
val = 0

notes=[A3, B3, D4, E4, Fs4, A4, B4, D5]
lengths=[1.5, 1.4, 1.3, 1.2, 1.1, 1]
position=[1,2,3,4]
values=[0, 0, 0, 0]

section1 = {'section': 1, 'note': "", 'length': 0, 'position': 0}
section2 = {'section': 2, 'note': "", 'length': 0, 'position': 0}
section3 = {'section': 3, 'note': "", 'length': 0, 'position': 0}
section4 = {'section': 4, 'note': "", 'length': 0, 'position': 0}

sections=[section1, section2, section3, section4]
start_flag=0

#Initialization over


def get_highest(values):
    if values==[0,0,0,0]:
        return "NULL"
    max_value = max(values)
    max_index = values.index(max_value)
    return max_index
            

while True:
    
    if start_flag==0:
        positions=shuffle(range(7))
        for x in range(0,4):#populating dictonaries with randoms
            rand_note=notes[randint(0,7)]
            rand_length=lengths[randint(0,5)]
            rand_pos=positions[x]
            
            
            sections[x]['note']=rand_note
            sections[x]['length']=rand_length
            sections[x]['position']=rand_pos
        start_flag=1


    sorted_sections = sorted(sections, key=itemgetter("position"))#sort all dictionaries in order of their position
    bar=1
    for y in range (1,5):
        positions=shuffle(range(7))
        rand_note=notes[randint(0,7)]
        rand_length=lengths[randint(0,5)]
        
        sections[y-1]['note']=rand_note
        sections[y-1]['length']=rand_length
        sections[x]['position']=rand_pos

        print(str(bar) + "th bar")
        for i in range (0,4):
            amount_values=0
            sum_values=[0,0,0,0]
            while ser.inWaiting()>0:
                line = ser.readline()
                valid=line.split(b',')
                if len(valid)!=4:
                    continue
                values=[int(x) for x in valid]
                sum_values=[a + b for a, b in zip(values, sum_values)]
                amount_values+=1

            
            #print(values)
            activated=get_highest(values)
            #print(activated)
            
            print("note " + str(i+1))#debug text so I don't lose myself            
            if activated!="NULL":
                if sorted_sections[i]['section']>activated:
                    print("current section note: " + str(current_section_note))
                    #print(sorted_sections[i])
            print(str(sorted_sections[i]['note']))
            play(sorted_sections[i]['note'])

            sleep(1)
        bar+=1
        
