#include <Servo.h>

Servo myservo;  
Servo myservo2; 

const int button1Pin = 3;
const int button2Pin = 2;
const int button3Pin = 6;
const int button4Pin = 9;

const int touchPin = 7;


int button1State = 0;
int button2State = 0;
int button3State = 0;
int button4State = 0;
int touchstate = 0;
int upmovecounter1 = 90;
int upmovecounter2 = 90;
int upmovecounter3 = 90;
int upmovecounter4 = 90;
int downmovecounter1 = 180;
int downmovecounter2 = 0;
int downmovecounter3 = 180;
int downmovecounter4 = 0;
bool move1 = false;
bool move2 = false;
bool move3 = false;
bool move4 = false;

void setup() {
  myservo2.attach(12);
  myservo.attach(11);
}
void loop() {
  
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);
  button4State = digitalRead(button4Pin);
  touchstate = digitalRead(touchPin);
  
  if(button1State == HIGH) {
    move1 = true;
  }
  
  if(button2State == HIGH) {
    move2 = true;
  }
  if(touchstate == HIGH) {
    move2 = true;
  }
  if(button3State == HIGH) {
    move3 = true;
  }
  if(button4State == HIGH) {
    move4 = true;
  }
  if (move1 == true && move3 == true)
  {
    
    if(upmovecounter1 < 180)
    {
      upmovecounter1 += 10;
      myservo.write(upmovecounter1);
    }
    else if(upmovecounter1 >= 180)
    {
      downmovecounter1 -= 10;
      myservo.write(downmovecounter1);
    }
    if(upmovecounter3 < 180)
    {
      upmovecounter3 += 10;
      myservo2.write(upmovecounter3);
    }
    else if(upmovecounter3 >= 180)
    {
      downmovecounter3 -= 10;
      myservo2.write(downmovecounter3);
    }
    delay(20);
    if (downmovecounter1 == 90){
      move1 = false;
      upmovecounter1 = 90;
      downmovecounter1 = 180;
    }
    if (downmovecounter3 == 90){
      move3 = false;
      upmovecounter3 = 90;
      downmovecounter3 = 180;
    }
  }
  else if (move1 == true)
  {
    
    if(upmovecounter1 < 180)
    {
      upmovecounter1 += 10;
      myservo.write(upmovecounter1);
      delay(20);
    }
    else if(upmovecounter1 >= 180)
    {
      downmovecounter1 -= 10;
      myservo.write(downmovecounter1);
      delay(20);
    }
    if (downmovecounter1 == 90){
      move1 = false;
      upmovecounter1 = 90;
      downmovecounter1 = 180;
    }
  }
  else if (move3 == true)
  {
    if(upmovecounter3 < 180)
    {
      upmovecounter3 += 10;
      myservo2.write(upmovecounter3);
      delay(20);
    }
    else if(upmovecounter3 >= 180)
    {
      downmovecounter3 -= 10;
      myservo2.write(downmovecounter3);
      delay(20);
    }
    if (downmovecounter3 == 90){
      move3 = false;
      upmovecounter3 = 90;
      downmovecounter3 = 180;
    }
  }
  if (move2 == true)
  {
    if(upmovecounter2 > 0)
    {
      upmovecounter2 -= 10;
      myservo.write(upmovecounter2);
      delay(20);
    }
    else if(upmovecounter2 <= 0)
    {
      downmovecounter2+= 10;
      myservo.write(downmovecounter2);
      delay(20);
    }
    if (downmovecounter2 == 90){
      move2 = false;
      upmovecounter2 = 90;
      downmovecounter2 = 0;
    }
  }
  if (move3 == true)
  {
    if(upmovecounter3 < 180)
    {
      upmovecounter3 += 10;
      myservo2.write(upmovecounter3);
      delay(20);
    }
    else if(upmovecounter3 >= 180)
    {
      downmovecounter3 -= 10;
      myservo2.write(downmovecounter3);
      delay(20);
    }
    if (downmovecounter3 == 90){
      move3 = false;
      upmovecounter3 = 90;
      downmovecounter3 = 180;
    }
  }
  if (move4 == true)
  {
    if(upmovecounter4 > 0)
    {
      upmovecounter4 -= 10;
      myservo2.write(upmovecounter4);
      delay(20);
    }
    else if(upmovecounter4 <= 0)
    {
      downmovecounter4 += 10;
      myservo2.write(downmovecounter4);
      delay(20);
    }
    if (downmovecounter4 == 90){
      move4 = false;
      upmovecounter4 = 90;
      downmovecounter4 = 0;
    }
  }
}

