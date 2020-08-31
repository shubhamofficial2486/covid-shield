
#include <MPU6050_tockn.h>
#include <Wire.h>

int trigPin1 = 11;    // Trigger
int echoPin1 = 12;    // Echo
int trigPin2 = 9;
int echoPin2 = 10;
int buzzerPin = 13;
int ledPin=3;
long duration1,duration2, cm1,cm2, inches1, inches2;
float gyro_avg, acc_avg;
int i,j;
MPU6050 mpu6050(Wire);

long timer = 0;

float gyro[10], acc[10];
void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
    //Define inputs and outputs
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {

  int n=0,c=0;
  float avg_acc,avg_gyro;
   mpu6050.update();

  if(millis() - timer > 1000){

    acc_avg = (mpu6050.getAccX()+mpu6050.getAccX()+mpu6050.getAccZ())/3;
    gyro_avg = (mpu6050.getGyroX()+mpu6050.getGyroY()+mpu6050.getGyroZ())/3;
    Serial.println("=======================================================");
    //Serial.print("temp : ");Serial.println(mpu6050.getTemp());
    Serial.print("accX : ");Serial.print(mpu6050.getAccX());
    Serial.print("\taccY : ");Serial.print(mpu6050.getAccY());
    Serial.print("\taccZ : ");Serial.println(mpu6050.getAccZ());
  
    Serial.print("gyroX : ");Serial.print(mpu6050.getGyroX());
    Serial.print("\tgyroY : ");Serial.print(mpu6050.getGyroY());
    Serial.print("\tgyroZ : ");Serial.println(mpu6050.getGyroZ());

    Serial.print("\tgyro_avg :");Serial.print(gyro_avg);
    Serial.print("\tacc_avg :");Serial.println(acc_avg);
    
    Serial.println("=======================================================\n");
    timer = millis();

  }
  if(acc_avg<0)
  {
    acc_avg=acc_avg*-1;
    }
  if (gyro_avg<0)
  {
    gyro_avg=gyro_avg*-1;
  }
  digitalWrite(trigPin1, LOW);
  //digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  //digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  //digitalWrite(trigPin2, LOW);
  
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);
  duration2 = pulseIn(echoPin2, HIGH);
 
  // Convert the time into a distance
  cm1 = (duration1/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  //inches1 = (duration1/2) / 74;   // Divide by 74 or multiply by 0.0135
  //cm2 = (duration2/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  //inches2 = (duration2/2) / 74;   // Divide by 74 or multiply by 0.0135 

  
  //Serial.print(inches1);
  //Serial.print("in, ");
  Serial.print(cm1);
  Serial.print("cm");
  
// Serial.print(inches2);
// Serial.print("in, ");
 //Serial.print(cm2);
// Serial.print("cm");
// Serial.println();
  
  acc[i]= acc_avg;
  for(n=0;n<10;n++)
  {
    avg_acc=avg_acc+acc[i];
    avg_acc=avg_acc/10;
  }
  if(avg_acc>0.45)
  {
    gyro[j]=gyro_avg;
    for(n=0;n<10;n++)
    {
      if(gyro[j]>30)
      c++;
    }
    if(c=0)
    {
       
       social_distancing();
    
    }
  }
  social_distancing();
  face_touch();
  Serial.println();
  delay(250);
  }

  
void social_distancing()
{
  if(cm1<100&&cm1>30)
 { 
   digitalWrite(buzzerPin,HIGH);
    
    Serial.println("alert!!  the person is so close");
 }
    if(cm1>150)
    {
      digitalWrite(buzzerPin,LOW);
    }
    }



void face_touch()
{
  if(cm1<15&&cm1>1)
  { if(ledPin<8)
   {
    
    Serial.print(ledPin-2);Serial.println(" time face touch");
    digitalWrite(ledPin,HIGH);
    ledPin++;
    
    delay(500);
   }
   else {
    digitalWrite(buzzerPin,HIGH);
   }
   }
   
}    
  
  
