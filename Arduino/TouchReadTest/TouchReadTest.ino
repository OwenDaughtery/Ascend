#include <Encoder.h>
#include <elapsedMillis.h>
#include <Bounce2.h>

#define numSensors 4
#define minScale 5   // 1/20th
#define maxScale 400 // 4x
#define baseScale 100

Encoder dial(3,4);
Bounce debouncer = Bounce(); 
elapsedMillis timeElapsed;

int rawMode = 0;

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

int scale = baseScale;

void setup() {

  pinMode(2,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
  debouncer.attach(2);
  debouncer.interval(10);
  Serial.begin(115200);
  dial.write(baseScale);
}

void loop() {
    rawMode = digitalRead(11) == LOW;
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
          
        
        thresholds[i] = maxSamples[i] + ( maxSamples[i] - minSamples[i] );
      }
    }

    scale = dial.read();
    
    if( scale < minScale ){
      dial.write(scale=minScale);
    }
    if( scale > maxScale ){
      dial.write(scale=maxScale);
    }
    
  
  for(int i=0;i<numSensors;i++){
    if(i!=0){
      Serial.print(",");
    }

    int temp = lasts[i] = touchRead( readPins[i] );
    if( rawMode ){
        Serial.print( temp );
    }
    else {
      int output = temp-thresholds[i];
      output = output * scale / baseScale;
      Serial.print( min( max( output, 0 ), 255) );
    }
  }
  if( rawMode ){
    for(int i=0;i<numSensors;i++){
      Serial.print(",");
      Serial.print( maxSamples[i] - minSamples[i] );
    }
  }
  /*Serial.print(",");
  Serial.print(scale);*/
  Serial.println();
  delay(40);
}
