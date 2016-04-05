#include <CapacitiveSensor.h>

CapacitiveSensor cs = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

long last = 0;
float cof = 0.25;

void setup(){
   cs.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);  
}

void loop(){
    long start = millis();
    long total =  cs.capacitiveSensor(30);
    long temp = last + cof * (total - last);
    

    delay(10);                             // arbitrary delay to limit data to serial port 
    Serial.print(temp);
    Serial.print("\t"); 
    Serial.println("");

    last = temp;
    
}
