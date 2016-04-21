#include <Encoder.h>
#include <elapsedMillis.h>
#include <Bounce2.h>

Encoder dial(3,4);
Bounce debouncer = Bounce(); 
elapsedMillis timeElapsed;

#define numSensors 4

int readPins[4] = {
    A2,A3,A4,A5
  } ;


long lasts[4] = {
  0,0,0,0
};

long minSamples[4] = {
  0,0,0,0
};
long maxSamples[4] = {
  0,0,0,0  
};


long thresholds[4] = {
  0,0,0,0
};


void setup() {

  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);

  debouncer.attach(2);
  debouncer.interval(10);
  Serial.begin(115200);
}

void loop() {
    debouncer.update();
    timeElapsed = 0;
    if( debouncer.fell() ){
      for(int i=0; i<numSensors; i++){
        minSamples[i] = maxSamples[i] = lasts[i];
        
        
      }
      
    }else if(debouncer.read() == LOW){      
      for(int i=0; i<numSensors; i++){
        if(lasts[i] < minSamples[i]){
          minSamples[i] = lasts[i];
          }
        if(lasts[i] > maxSamples[i]){
          maxSamples[i] = lasts[i];
          }          
          
        
        thresholds[i] = (2 * maxSamples[i]) - minSamples[i];
      }
    }
  
  // put your main code here, to run repeatedly:
  for(int i=0;i<numSensors;i++){
    if(i!=0){
      Serial.print(",");
    }

    int temp = lasts[i] = touchRead( readPins[i] );
    
    Serial.print( max( temp-thresholds[i], 0 ) );
  }
  Serial.println();
  delay(250);
}
