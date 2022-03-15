/*
  *File        : Implementation of Obstruction Avoiding Robot using Ultrasonic Sensor and Arduino UNO:
  *Information : This project attempts to create an obstruction avoiding robot which can automatically sense the presence of an obstruction in its path and avoid them.
                It intelligently detects barrier present in its path through the ultrasonic sensors, with the help of the internal code from the Arduino UNO,decisions 
                are made to avoid the barriers. This has been achieved by using an ultrasonic sensor and the development board Arduino UNO. The ultrasonic sensor is 
                mounted on a servo motor at the front of the vehicle for a wider field of view. The ultrasonic sensor acquires data which is processed by the Arduino 
                which then decides the direction of travel for the robot.
  *Autor       : Eng. Ibrahim OBAIDO
  *Date        : 13.03.2022
 */
 
#include <Servo.h>
#define in1 2//--------------------------------------------------------------------->>Right motor pole 1
#define in2 3//--------------------------------------------------------------------->>Right motor pole 2
#define in3 4//--------------------------------------------------------------------->>left motor pole 1
#define in4 7//--------------------------------------------------------------------->>left motor pole 1
#define ena 5//--------------------------------------------------------------------->>Right motor speed
#define enb 6//--------------------------------------------------------------------->>Right motor speed
Servo myservo;//-------------------------------------------------------------------->>create servo object to control a servo
int pos = 0;//---------------------------------------------------------------------->>variable to store the servo position
const int trigPin = 11;//----------------------------------------------------------->>Trigger Pin of Ultrasonic
const int echoPin = 12;//----------------------------------------------------------->>Echo Pin of Ultrasonic
long duration;//-------------------------------------------------------------------->>used by ultrasonic Function
int distance,Cdistance,Rdistance,Ldistance;//--------------------------------------->>Cdistance=center Distance Rdistance=Right Distance Ldistance=Left Distance
/*************************************************************************************************************************************/
void setup() 
{
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(trigPin, OUTPUT);//------------------------------------------------------------->>Sets the trigPin as an Output
  pinMode(echoPin, INPUT);//-------------------------------------------------------------->>Sets the echoPin as an Input
  myservo.attach(9);//-------------------------------------------------------------------->>attaches the servo on pin 9 to the servo object
  myservo.write(90);//-------------------------------------------------------------------->>Initial Pos of Servo at center
}

void loop()
{
  Cdistance=ultrasonic();//-------------------------------------------------------------->>take ultrasonic distance value
  if(Cdistance>50)//--------------------------------------------------------------------->>if greater than 50 cm
        {
          forward();//------------------------------------------------------------------->>go to forward
        }
  else if(Cdistance<50&&Cdistance>30)//-------------------------------------------------->>if greater than 40 cm
        {
          forward_2();//----------------------------------------------------------------->>go to forward
        }
   else 
        {
          if(Cdistance<=20&&Cdistance>2)
          reverse();//------------------------------------------------------------------->>if close to object reverse to get more space to change orientatio
          off();//----------------------------------------------------------------------->>stop robot
          myservo.write(10);//----------------------------------------------------------->>Turn servo Right 
          delay(300);
          Rdistance=ultrasonic();//------------------------------------------------------>>get ultrasonic value at right
          myservo.write(170);//---------------------------------------------------------->>Turn servo Left
          delay(300);
          Ldistance=ultrasonic();//------------------------------------------------------>>get ultrasonic value at left
          myservo.write(90);//----------------------------------------------------------->>return to center pos
          delay(300);
          comparison(Rdistance, Ldistance);//-------------------------------------------->>go to Comparasion function
          off();//----------------------------------------------------------------------->>stop after execute Comparison function action
          delay(150);
        }
        /******************************** reset all variables**************************************/
  Rdistance=0;
  Ldistance=0;
  Cdistance=0;
}
/*************************************************************************************************************************************/
int ultrasonic(void)//------------------------------------------------------------------------------>>get distance captured by ultrasonic sensor
{
  distance=0;
  digitalWrite(trigPin, LOW);//--------------------------------------------------------------------->>Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);//-------------------------------------------------------------------->>Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);//-------------------------------------------------------------->>Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;//--------------------------------------------------------------------->>Calculating the distance
  return distance;
}
/*************************************************************************************************************************************/
void comparison(int R, int L)//-------------------------------------------------------------------->>compare values of right and left Servo Pos 
{
  if(R>25||L>25)
  {
     if(R>L||R==L)
     {
       Tright90();
     }
     else
     {
       Tleft90();
     }
  }
  else
  {
      reverse_2();
  }
}
/*********************************************************************forward****************************************************************/
void forward()
{
  analogWrite(ena,140);
  analogWrite(enb,140);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
/*********************************************************************forward_2****************************************************************/
void forward_2()
{
  analogWrite(ena,70);
  analogWrite(enb,70);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
/***********************************************************************Off**************************************************************/
void off()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
/**********************************************************************Tleft90***************************************************************/
void Tleft90()
{
  analogWrite(ena,130);
  analogWrite(enb,130);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(500);
}
/**********************************************************************Tright90***************************************************************/
void Tright90()
{
  analogWrite(ena,130);
  analogWrite(enb,130);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(500);  
}
/**********************************************************************reverse***************************************************************/
void reverse()
{
  analogWrite(ena,140);
  analogWrite(enb,140);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(500);
}
/**********************************************************************reverse_2***************************************************************/
void reverse_2()
{
  analogWrite(ena,70);
  analogWrite(enb,70);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(150);
}
