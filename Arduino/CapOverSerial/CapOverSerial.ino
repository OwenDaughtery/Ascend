#include <CapacitiveSensor.h>

CapacitiveSensor cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor cs_8_6 = CapacitiveSensor(8,6);        // 10M resistor between pins 8 & 6, pin 6 is sensor pin, add a wire and or foil if desired

long last1 = 0;
long last2 = 0;
long thresh = 0;

float cof = 0.3;

void setup(){
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);  
}

void loop(){
    long start = millis();

    
    long total1 =  cs_4_2.capacitiveSensor(30);
    long temp1 = last1 + cof * (total1 - last1);

// begin threshold test
//    if (thresh == 0)
//      thresh = (total1 * 2);
//    long threshtotal = total1 - thresh;
//  end threshold test
 
    long total2 = cs_8_6.capacitiveSensor(30);
    long temp2 = last2 + cof * (total2 - last2);
   

    delay(10);                             // arbitrary delay to limit data to serial port 
    Serial.print(temp1);
    Serial.print("\t");
    Serial.println(temp2);
    Serial.print("\t");
    Serial.print("");

    last1 = temp1;
    last2 = temp2;
    
}

//thereshold is subtractor from values, inverse square law 1\r2, logarthmic, swaure root it, have cooeficient, foil ground plane, grounding of building

