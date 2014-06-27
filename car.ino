#include <Servo.h>
 
Servo myservo;
int distance = 0;
int velocity = 0;
int steering = 0;
byte distancePin = 0;
byte motorPin = 5;
byte dirFpin = 7;
byte dirBpin = 8;
byte servoPin = 9;
long previousLCDMillis = 0;
long LCDinterval = 150;
long previousRXTXMillis = 0;
long RXTXinterval = 20;

int distanceVal()
{
  distance = analogRead(distancePin);
  distance = 2076 / (distance - 11);
  distance = constrain(distance, 4 ,50);
  return distance;
  
}
  
void setup() 
{
  pinMode(motorPin, OUTPUT);
  pinMode(dirFpin, OUTPUT);
  pinMode(dirBpin, OUTPUT);
  digitalWrite(dirBpin, LOW);
  digitalWrite(dirFpin, LOW);
  analogWrite(motorPin, 0);
  myservo.attach(servoPin);
  Serial.begin(19200);
}

void forward()
{
  if (distanceVal() > 7)
  {
    velocity = Serial.parseInt();
    steering = map(Serial.parseInt(), 0, 179, 128, 60);
    Serial.println(distanceVal());
    digitalWrite(dirFpin, HIGH);
    digitalWrite(dirBpin, LOW);
    analogWrite(motorPin, velocity);
    myservo.write(steering);
  }
  else
  {
    Serial.parseInt();
    steering = map(Serial.parseInt(), 0, 179, 128, 60);
    Serial.println(distanceVal());
    digitalWrite(dirBpin, LOW);
    digitalWrite(dirFpin, LOW);
    analogWrite(motorPin, 0);
    myservo.write(steering);
  }
    
}

void backward()
{
  velocity = Serial.parseInt();
  steering = map(Serial.parseInt(), 0, 179, 128, 60);
  Serial.println(distanceVal());
  digitalWrite(dirFpin, LOW);
  digitalWrite(dirBpin, HIGH);
  analogWrite(motorPin, velocity);
  myservo.write(steering);
}

void stopMove()
{
  steering = map(Serial.parseInt(), 0, 179, 128, 60);
  Serial.println(distanceVal());
  digitalWrite(dirBpin, LOW);
  digitalWrite(dirFpin, LOW);
  analogWrite(motorPin, 0);
  myservo.write(steering);
}

  

void loop()
{
unsigned long currentLCDMillis = millis();
unsigned long currentRXTXMillis = millis(); 
  
if (currentRXTXMillis - previousRXTXMillis > RXTXinterval)
  {
    previousRXTXMillis = currentRXTXMillis;
    while (Serial.available() > 0)
    {
    
      char syncChar = Serial.read();
    
      if (syncChar == 'f')
      {
        forward();
      }
      if (syncChar == 'b')
      {
        backward();
      }
      else if (syncChar == 's')
      {
        stopMove();
      }
    }
  }
  if (currentLCDMillis - previousLCDMillis > LCDinterval)
  {
    previousLCDMillis = currentLCDMillis;
    Serial.println(distanceVal());
  }
}



