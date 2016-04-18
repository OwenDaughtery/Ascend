#include <CapacitiveSensor.h>
#include <Encoder.h>
#include <elapsedMillis.h>
#include <Bounce2.h>

#define minScale 1
#define maxScale 255
#define numSensors 3

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

Encoder dial(3,4);
Bounce debouncer = Bounce(); 

elapsedMillis timeElapsed;

long lasts[8] = {
  0,0,0,0,0,0,0,0  
};

long thresholds[8] = {
  0,0,0,0,0,0,0,0
};

float thresholdMargin = 1.1;
long scale;

float cof = 0.4;

void setup(){

  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  
  debouncer.attach(2);
  debouncer.interval(10);
  
  for(int i=0; i<numSensors; i++){
     cs[i].set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
     cs[i].set_CS_Timeout_Millis(10);
   }
   
   Serial.begin(115200);  
}

void loop(){
    debouncer.update();
    timeElapsed = 0;
    if( debouncer.fell() ){
      for(int i=0; i<numSensors; i++){
        thresholds[i] = lasts[i] * thresholdMargin;
      }
      
    }

    scale = dial.read() / 48;
    if( scale < minScale ){
      dial.write(scale=48*minScale);
    }
    if( scale > maxScale ){
      dial.write(scale=48*maxScale);
    }


  for(int i=0; i<numSensors; i++){
    long total =  cs[i].capacitiveSensor(5);
    long temp = lasts[i] + cof * (total - lasts[i]);   
    long adjustedVal = scale * sqrt( temp-thresholds[i] );
    if (i!=0)
      Serial.print(",");
    Serial.print( adjustedVal );  
    lasts[i] = temp;
   }
   Serial.println("");

    long delayDuration = 40-timeElapsed;
    if( delayDuration > 0 ){
      delay(delayDuration);                             // arbitrary delay to limit data to serial port     
    }

}

//thereshold is subtractor from values, inverse square law 1\r2, logarthmic, swaure root it, have cooeficient, foil ground plane, grounding of building

