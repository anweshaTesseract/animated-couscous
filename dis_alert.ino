#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C l(0x27,16,2);
int trig=13;
int echo=12,led=11,buz=10;
void setup() {
  // put your setup code here, to run once:
  l.init();
  l.backlight();
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(led,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trig,LOW);//initially, set tri to low at start of every loop
delay(2);
digitalWrite(trig,HIGH);//echo becomes high here automatically
delayMicroseconds(10);
//since the sensor internally expects the trig pin to be high for 10 microsec
//(expects at lease 10microsec pulse)-to work perfectly,
// giving any more than that does not guarantee the sensor's behavior
// And giving any less might cause the sensor to not recognise as a valid pulse and the sensor may not start measurement.
digitalWrite(trig,LOW);//trig is made low here to finish sending the 10 microsec pulse to the sensor.
unsigned long t=pulseIn(echo,HIGH);//echo is high for how long?
//It will be high for as long as it takes for the ultrasound to return. 
//Therefore for (distance travelled in total)/(speed of sound in room temp).
//hence 2d=speed*time and d=speed*time/2
//where time is in microsec(pulseIn returns in microsec) and speed in m/s. 
//so speed=343m/s. time=t microsec=t*10^(-6) sec. so dist=343*t*10^(-6) m. 
//But the object for a small project like this is in range of cm. So we convert it to cm.
//dist=354*t*10^(-6)*10^(2) cm=0.0343*t cm
float d=0.0343*t/2;
Serial.print(d);
Serial.println("cm");
l.setCursor(0,0);//Column then row
  l.print("Distance(cm):");
  l.setCursor(13,0);
  l.print(int(d));
  l.print(" ");
if(d<=10 && d>=0)
{
  analogWrite(buz,255);
  delay(10);
  digitalWrite(buz,LOW);
  delay(10);
  analogWrite(led,255);
  //255 is maximum-because 2^8=256 and arduino's pulse width modulation is by
  //8-bits timer.
  l.setCursor(0,1);
  l.print("Very close");
  l.print("          ");
  delay(10);
}
else if(d>10 && d<=15)
{
  analogWrite(buz,128);
  delay(50);
  digitalWrite(buz,LOW);
  delay(50);
  analogWrite(led,128);
  l.setCursor(0,1);
  l.print("Far");
  l.print("          ");
  delay(10);
}
else
{
  digitalWrite(buz,LOW);
  delay(50);
  digitalWrite(led,LOW);
  l.setCursor(0,1);
  l.print("Too far");
  l.print("          ");
  delay(50);
}
}
/*
P.S. This is code for the Tinkercad project. Since I learnt a bit more about millis-about how to use it, and I had tried to add a few features to the original project, so I 
pasted it here.

int b=5,r=9,g=0,bl=6,but=3;
unsigned long pt=0;
void setup()
{
 pinMode(b,OUTPUT);//Buzzer
  pinMode(r,OUTPUT);//Red led
  pinMode(bl,OUTPUT);//Blue led
  pinMode(g,OUTPUT);//Green led
    pinMode(but,INPUT_PULLUP);//button
  Serial.begin(9600);
  
} bool pst=LOW,cst;
  unsigned long cm=0;
void loop()
{
  cst=!digitalRead(but);
  unsigned long t=0;
  if(cst==pst)
  t=millis()-pt;
  Serial.print(cst);
  Serial.print("    ");
  Serial.print(t);
  Serial.print("     ");
  Serial.println(analogRead(A0));
  
  if(pst==0 && cst==1)
  {digitalWrite(r,LOW);
   if(analogRead(A0)<=0.3*1022){
     analogWrite(bl,0.3*255);}
     
   else if(analogRead(A0)<=0.5*1022 && analogRead(A0)>0.3*1022)
   {analogWrite(bl,0.5*255);
   delay(50);
     analogWrite(b,0.5*255);}
   else
   {
     analogWrite(bl,255);
   delay(50);
     analogWrite(b,255);
   }
   pst=HIGH;
   pt=millis();
   cm=millis();
  }
  else if(pst==1 && cst==1)
  {
    if(t<5000){
      digitalWrite(r,LOW);
    if(analogRead(A0)<=0.3*1022){
    analogWrite(bl,0.3*255);
  if(millis()-cm>=200){
       if(digitalRead(b)==0)
       analogWrite(b,0.3*255);
       else
         digitalWrite(b,LOW);
       cm=millis();}}
   else if(analogRead(A0)<=0.5*1022 && analogRead(A0)>0.3*1022)
   {analogWrite(bl,0.5*255);
   delay(50);
     analogWrite(b,0.5*255);}
   else
   {
     analogWrite(bl,255);
   delay(50);
     analogWrite(b,255);
   }}
    
    else
    {digitalWrite(bl,LOW);
      if(analogRead(A0)<=0.3*1022){
    analogWrite(r,0.3*255);
   delay(50);
     analogWrite(b,0.3*255);}
   else if(analogRead(A0)<=0.5*1022 && analogRead(A0)>0.3*1022)
   {analogWrite(r,0.5*255);
   delay(50);
     analogWrite(b,0.5*255);}
   else
   {
     analogWrite(r,255);
   delay(50);
     analogWrite(b,255);
   }}
    
      pst=HIGH;
  }
  else if(pst==HIGH && cst==LOW)
  {
    digitalWrite(r,LOW);
    digitalWrite(bl,LOW);
    digitalWrite(b,LOW);
    pst=LOW;
    pt=millis();
  }
}
*/
