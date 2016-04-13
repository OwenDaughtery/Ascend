from time import *
from random import randint

notes=['A3', 'B3', 'D4', 'E4', 'Fs4', 'A4', 'B4', 'D5']
lengths=[1.5, 1.4, 1.3, 1.2, 1.1, 1]
position=[1,2,3,4,5,6,7,8]

section1 = {'note': "", 'length': "", 'position': ""}
section2 = {'note': "", 'length': "", 'position': ""}
section3 = {'note': "", 'length': "", 'position': ""}
section4 = {'note': "", 'length': "", 'position': ""}
section5 = {'note': "", 'length': "", 'position': ""}
section6 = {'note': "", 'length': "", 'position': ""}
section7 = {'note': "", 'length': "", 'position': ""}
section8 = {'note': "", 'length': "", 'position': ""}

sections=[section1, section2, section3, section4, section5, section6, section7, section8]

#Initialization over

while True:
    for x in range(0,7):#populating dictonaries with randoms
        rand_note=notes[randint(0,7)]
        rand_length=lengths[randint(0,5)]
        rand_pos=position[randint(0,7)]        
        sections[x]['note']=rand_note
        sections[x]['length']=rand_length
        sections[x]['position']=rand_pos

    
    for i in range (1,5):
        
        print(str(i) + "th bar")


        
        #printing or "sending" of the dictionaries in order would happen here
        sleep(0.5)
