from time import *
from random import *
from operator import itemgetter
from psonic import *
from serial import *
import serial.tools.list_ports
port = list(serial.tools.list_ports.comports())[0][0]
ser = serial.Serial(port, 115200)
val = 0

notes=[A3, B3, D4, E4, Fs4, A4, B4]
lengths=[0.125, 0.25, 0.375, 0.5]
max_values=[0, 0, 0, 0]

positions=list(range(16))


sections=[]
for i in range(8):
    sections.append({'section': i+1})
bar=0
signature=2


#Initialization over


def get_highest(values):
    if values==[0,0,0,0]:
        return "NULL"
    max_value = max(values)
    max_index = values.index(max_value)
    return max_index
            

shuffle(positions)

for x in range(len(sections)):#populating dictonaries with randoms
    rand_note=notes[randint(0, len(notes)-1)]
    rand_length=lengths[randint(0, len(lengths)-1)]
    rand_pos=positions[x]
    sections[x]['note']=rand_note
    sections[x]['length']=rand_length
    sections[x]['position']=rand_pos


while True:

    rand_section=randint(0, len(sections)-1)
    rand_note=notes[randint(0, len(notes)-1)]
    rand_length=lengths[randint(0, len(lengths)-1)]
    rand_pos_index=randint(len(sections), len(positions)-1)
    rand_pos=positions[rand_pos_index]
    if randint(1, 100)<=33:
        print("pos switch")
        positions[rand_pos_index]=sections[rand_section]['position']
        sections[rand_section]['position']=rand_pos
    else:
        print("note switch")
        sections[rand_section]['note']=rand_note
        sections[rand_section]['length']=rand_length
    
    print(", ".join([str(section['note']) for section in sections]))
    
    for i in range(len(positions)):
        
        counter=0
        while ser.inWaiting()>0:
            line = ser.readline()
            valid=line.split(b',')
            if len(valid)!=4:
                continue
            values=[int(x) for x in valid]
            for b in range(len(max_values)):
                if values[b]>max_values[b] or counter==0:
                    max_values[b]=values[b]
            counter+=1
        amp_values=[a/255.0 for a in max_values]

        activated=get_highest(max_values)           

        note=False
        for c in range(len(sections)):
            if sections[c]['position']==i:
                note=sections[c]
                note['amp']=amp_values[c%len(amp_values)]
                break
        if note!=False:
            play(note['note'], sustain=note['length'], amp=note['amp'])

        sleep(signature/8)
        
    bar+=1
        
