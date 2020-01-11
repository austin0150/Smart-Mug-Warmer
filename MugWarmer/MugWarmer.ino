#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const int trigPin = 8;
const int echoPin = 9;

// defines variables
long duration;
int distance;
int tries = 0;
int outputState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input  

  mlx.begin();  
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance= duration*0.034/2;

  if(distance < 10){
    //Threshold temp is 85f, only because my sensor is too far away from the coffee
    if(mlx.readObjectTempF()< 85){
      if(outputState == 0)
      {
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(10, HIGH);
        outputState = 1;
        Serial.print("Dist: "); Serial.println(distance);
        Serial.print("Temp: "); Serial.println(mlx.readObjectTempF());
        Serial.print("C Temp: "); Serial.println(mlx.readObjectTempC());
      }
      
      tries = 0;
    }
    else{
      tries ++;
    }
  }
  else{
    tries ++;
  }

  if(tries > 5)
  {
    digitalWrite(10, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    delay(2000);
    outputState = 0;
    tries = 0;
  }

  delay(500);
 }
