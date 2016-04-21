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
bar=0
signature=4


#Initialization over


def get_highest(values):
    if values==[0,0,0,0]:
        return "NULL"
    max_value = max(values)
    max_index = values.index(max_value)
    return max_index
            

positions=shuffle(range(8))
for x in range(0,4):#populating dictonaries with randoms
    rand_note=notes[randint(0,8)]
    rand_length=lengths[randint(0,5)]
    rand_pos=positions[x]
    sections[x]['note']=rand_note
    sections[x]['length']=rand_length
    sections[x]['position']=rand_pos
    
while True:

    rand_section=randint(0,4)
    rand_note=notes[randint(0,8)]
    rand_length=lengths[randint(0,5)]
    rand_pos_index=randint(4,8)
    rand_pos=positions[rand_pos_index]
    positions[rand_pos_index]=sections[rand_section]['position']
    sections[rand_section]['note']=rand_note
    sections[rand_section]['length']=rand_length
    sections[rand_section]['position']=rand_pos
    
    print(", ".join([section['note'] for section in sections]))
    for i in range(8):
        
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

        activated=get_highest(values)           

        note=False
        for c in range(4):
            if sections[c]['position']==i:
                note=sections[c]
                break
        if note!=False:
            play(note['note'], sustain=note['length'])

        sleep(signature/8)
        
    bar+=1
        
