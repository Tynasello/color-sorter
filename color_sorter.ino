#include <Servo.h>

Servo pickup;
Servo path;

#define S0 4
#define S1 5
#define S2 7
#define S3 6

#define sensorOut 8

int fR = 0;
int fG = 0;
int fB = 0;

int cR = 0;
int cG = 0;
int cB = 0;

void setup() {
  
  Serial.begin(9600);
  
  pinMode(S0,OUTPUT);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);
  pinMode(sensorOut,INPUT);
  //serial communication
  Serial.begin(9600);
  //frequency scaled to 20%; common practice
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  pickup.attach(10);
  path.attach(11);
}

void loop() {
   for(int x =2; x<180; x++){
     pickup.write(x);
     delay(10);
   }
   delay(5);
   pickup.write(86);
  delay(1000);
  int color = getColor();
  switch (color){
    case 1:
      path.write(5);
      break;
    case 2:
      path.write(35);
      break;
    case 3:
      path.write(80); 
      break;
  }
   delay(1000);
   for(int x =86; x>-1; x--){
     pickup.write(x);
     delay(3);
   }   
  delay(1200);
  
  
}

int getColor(){
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //red colour
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  fR = pulseIn(sensorOut,LOW);//reading red colour frequency
  //cR = map(fR,142 , 231, 255, 0);


  Serial.print("R =");
  Serial.print(fR);

  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //green colour
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  fG = pulseIn(sensorOut,LOW);//reading green colour frequency
  //cG = map(fG, 153, 230, 255, 0);


  Serial.print(",G = ");
  Serial.print(fG);
  
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //blue colour
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  fB = pulseIn(sensorOut,LOW);//reading blue colour frequency
  //cB = map(fB, XX, XX, 255, 0);

  Serial.print(",B = ");
  Serial.print(fB);
  Serial.println();
  
  int color = 0;
  
  // checks what colour is being detected
  if( fR>124 & fR<134 &fG>136){
      color=1;//red
  }

  if(fR>125 & fR<137 &fG>129 & fG<138 ){
      color =2;//green
  }
  if( fR>100 & fR<120  & fG>90 & fG<151){
      color =3;//yellow
  }
  Serial.println(color);
  delay(1000);
  return color;
}
