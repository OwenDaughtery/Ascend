#include <CapacitiveSensor.h>
#include <Encoder.h>
#include <elapsedMillis.h>
#include <Bounce2.h>

#define minScale 1
#define maxScale 255
#define raw 0

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

int pins[8] = {
  6, 7, 8, 9, 10, 14, 15, 16
};
float thresholdMargin = 1.5;
long scale;

float cof = 0.4;

void setup(){

  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  
  debouncer.attach(2);
  debouncer.interval(10);
  
  for(int i=0; i<8; i++){
     cs[i].set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   }
   
   Serial.begin(9600);  
}

void loop(){
    debouncer.update();
    timeElapsed = 0;
    if( debouncer.fell() ){
      for(int i=0; i<8; i++){
        thresholds[i] = thresholdMargin * lasts[i];
      }
      
    }else if(debouncer.read() == LOW){      
      for(int i=0; i<8; i++){
        thresholds[i] = max(thresholdMargin * lasts[i], thresholds[i]);
      }
    }


    scale = dial.read();
    if( scale < minScale ){
      dial.write(scale=minScale);
    }
    if( scale > maxScale ){
      dial.write(scale=maxScale);
    }


  for(int i=0; i<8; i++){
    long total =  cs[i].capacitiveSensor(30);
    //long total = 0;
    long temp = lasts[i] + cof * (total - lasts[i]);   
    long adjustedVal = scale * sqrt(max(temp-thresholds[i],0));
    if (i!=0)
      Serial.print(",");
      #if raw
        Serial.print(total);
      #else      
        Serial.print(min(255, adjustedVal ));  
      #endif
    lasts[i] = temp;
   }
   Serial.println("");

    /*long delayDuration = 40-timeElapsed;
    if( delayDuration > 0 ){
      delay(delayDuration);                             // arbitrary delay to limit data to serial port     
    }*/

    /*for(int i=0; i<8; i++){
      pinMode(pins[i], OUTPUT);
      digitalWrite(pins[i], LOW);
      }
    delay(5);
    for(int i=0; i<8; i++){
      pinMode(pins[i], INPUT);
      }*/
      
}

//thereshold is subtractor from values, inverse square law 1\r2, logarthmic, swaure root it, have cooeficient, foil ground plane, grounding of building
//numpy 2d array 
//header pins, enamel wire

//get enamel wire
//tape up cardboard
//connect cardboard to arduino
//run arduino code 

//run python code
//code python code so all 8 lines are plotted
//get it running on Pi
//ground it
//notes are: A3, B3, D4, E4, F#4, A4, B4, D5

