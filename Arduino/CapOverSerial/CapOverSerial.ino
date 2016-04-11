#include <CapacitiveSensor.h>

CapacitiveSensor cs[8] = {
  CapacitiveSensor(5, 6), // 10M resistor between pins 5 & 6, pin 6 is sensor pin, add a wire and or foil if desired
  CapacitiveSensor(5, 7),
  CapacitiveSensor(5, 8),
  CapacitiveSensor(5, 9),
  CapacitiveSensor(5, 10),
  CapacitiveSensor(5, 14),
  CapacitiveSensor(5, 15),
  CapacitiveSensor(5, 16)
};

long lasts[8] = {
  0,0,0,0,0,0,0,0  
};


float cof = 0.4;

void setup(){
  for(int i=0; i<8; i++){
     cs[i].set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   }
   Serial.begin(9600);  
}

void loop(){
    long start = millis();

  for(int i=0; i<8; i++){
    long total =  cs[i].capacitiveSensor(30);
    long temp = lasts[i] + cof * (total - lasts[i]);   
    if (i!=0)
      Serial.print(",");
    Serial.print(temp);  
    lasts[i] = temp;
   }
   Serial.println("");

   // delay(10);                             // arbitrary delay to limit data to serial port     

}

//thereshold is subtractor from values, inverse square law 1\r2, logarthmic, swaure root it, have cooeficient, foil ground plane, grounding of building

