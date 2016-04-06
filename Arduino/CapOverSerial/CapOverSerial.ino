#include <CapacitiveSensor.h>

CapacitiveSensor cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor cs_14_15 = CapacitiveSensor(14,15);        // 10M resistor between pins 14 & 15, pin 15 is sensor pin, add a wire and or foil if desired

long last = 0;
float cof = 0.3;

void setup(){
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);  
}

void loop(){
    long start = millis();
    long total =  cs_4_2.capacitiveSensor(30);
    long temp = last + cof * (total - last);
        
    long totaltest = cs_14_15.capacitiveSensor(30); //is a test

    
    //Serial.print("Test Commencing");
    //Serial.print(totaltest);
    //Serial.print("\t"); 
    //Serial.println("");
    //Serial.print("Test Ending");    

    delay(10);                             // arbitrary delay to limit data to serial port 
    Serial.print(totaltest);
    Serial.print(" ");
    Serial.println(temp);
    //Serial.print(" ");
    //Serial.print(50);
    Serial.print("\t"); 
    Serial.print("");

    last = temp;
    
}
