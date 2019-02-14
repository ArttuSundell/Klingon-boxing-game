
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include "pitches.h"

Servo myservo;  
Servo myservo2; 

LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);  // Set the LCD I2C address

const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;
const int button4Pin = 5;
const int touchPin1 = 6;
const int touchPin2 = 7;
const int piezo = 8;

//servo positions, centerPos is the starting position and min and max are extreme positions
const int centerPos = 90;
const int minPos = 0;
const int maxPos = 180;
int posArray[] = {maxPos,minPos,maxPos,minPos};

//variable stepp defines how much servon position changes during one loop, (makes possible simultaneous movements for both players)
int stepp = 10;

//waiting period for servo-movements
const int wait = 20;

//notes for the punch hit effect
int hitsound[] = {
 NOTE_FS6,NOTE_FS6,NOTE_FS6,NOTE_F6,NOTE_F6,NOTE_F6,NOTE_E6,NOTE_E6,NOTE_E6};

//note durations of the punch hit effect
int noteDurations[] = {
70,70,70,70,70,70,70,70,70,
70,70,70,70,70,70,70,70,70
};

//notes for the intro tune (eye of the tiger)
 int intro[] = {
  NOTE_A1,  
  NOTE_AS1, 
  NOTE_B1,  
  NOTE_C2,  
  NOTE_CS2, 
  NOTE_D2,  
  NOTE_DS2, 
  NOTE_E2,  
  NOTE_F2,  
  NOTE_FS2, 
  NOTE_G2,  
  NOTE_GS2, 
  NOTE_A2,  
  NOTE_AS2,
  NOTE_B2,  
  NOTE_C3,  
  NOTE_CS3, 
  NOTE_D3,  
  NOTE_DS3, 
  NOTE_E3, 
  NOTE_F3,  
  NOTE_FS3,
  NOTE_G3,  
  NOTE_GS3, 
  NOTE_A3,  
  NOTE_AS3, 
  NOTE_B3,
  NOTE_C4,0,NOTE_C4,NOTE_C4,NOTE_C4,0,NOTE_C4,NOTE_C4,NOTE_C4,0,NOTE_C4,NOTE_C4,NOTE_C4,NOTE_C4,NOTE_C4,NOTE_C4,NOTE_C4,NOTE_C4,NOTE_C4,
  NOTE_C4,0,0,0,0,0,NOTE_C4,0,0,NOTE_AS3,0,0,NOTE_C4,
  0,0,0,0,0,NOTE_C4,0,0,NOTE_AS3,0,0,NOTE_C4,
  0,0,0,0,0,NOTE_C4,0,0,NOTE_AS3,0,0,NOTE_GS3,

  0,0,
  
  NOTE_C4,0,0,0,0,0,NOTE_C4,0,0,NOTE_AS3,0,0,NOTE_C4,
  0,0,0,0,0,NOTE_C4,0,0,NOTE_AS3,0,0,NOTE_C4,
  0,0,0,0,0,NOTE_C4,0,0,NOTE_AS3,0,0,NOTE_GS3,

  NOTE_G3,  
  NOTE_FS3,
  NOTE_F3,  
  NOTE_E3,  
  NOTE_DS3, 
  NOTE_D3,  
  NOTE_CS3, 
  NOTE_C3,  
  NOTE_B2,  
  NOTE_AS2, 
  NOTE_A2,  
  NOTE_GS2, 
  NOTE_G2,  
  NOTE_FS2, 
  NOTE_F2,  
  NOTE_E2,  
  NOTE_DS2, 
  NOTE_D2,  
  NOTE_CS2, 
  NOTE_C2,  
  NOTE_B1,  
  NOTE_AS1, 
  NOTE_A1,  
  NOTE_GS1, 
  NOTE_G1,  
  NOTE_FS1, 
  NOTE_F1,  
  NOTE_E1,  
  NOTE_DS1, 
  NOTE_D1,  
  NOTE_CS1, 
  NOTE_C1,  
  NOTE_B0
};

//note durations of intro tune
int noteDurations2[] = {
  30,30,30,30,30,30,30,30,30,30,
  30,30,30,30,30,30,30,30,30,30,
  30,30,30,30,30,30,30,

  
  8,4,16,16,
  8,4,16,16,
  8,4,16,16,
  16,16,16,16,16,16,16,
  
  8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,1,

  2,4,

  8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,1,

  30,30,30,30,30,30,30,30,30,30,
  30,30,30,30,30,30,30,30,30,30,
  30,30,30,30,30,30,30,30,30,30,
  30,30,30,

  30,30,30,30,30,30,30,30,30,30,
  30,30,30,30,30,30,30,30,30,30,
  30,30,30,30,30,30,30,30,30,30,
  30,30,30

  
};
//melody of the winning tune
int victoryMelody[] = {
 
  NOTE_C4,NOTE_C4,NOTE_C4,NOTE_C4,NOTE_C4,NOTE_C4,NOTE_C4,NOTE_C4,NOTE_E4,NOTE_C4,NOTE_C4,NOTE_C4,
  NOTE_E4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_G4,NOTE_E4,NOTE_E4,NOTE_E4,0,
  NOTE_E4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_E4,0,NOTE_E4,NOTE_E4,NOTE_F4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_E4,
  NOTE_E6,NOTE_G6,NOTE_A6,
  NOTE_E7,NOTE_E7,NOTE_G7,NOTE_G7,NOTE_A7,NOTE_A7,0,NOTE_E7,NOTE_E7,NOTE_G7,NOTE_G7,NOTE_A7,NOTE_A7,0,
  NOTE_A6,NOTE_B6,NOTE_E5,
  NOTE_E7,NOTE_E7,NOTE_G7,NOTE_G7,NOTE_A7,NOTE_A7,0,NOTE_E7,NOTE_E7,NOTE_G7,NOTE_G7,NOTE_A7,NOTE_A7,0,
  NOTE_E6,NOTE_G6,NOTE_A6,
  NOTE_E7,NOTE_E7,NOTE_G7,NOTE_G7,NOTE_A7,NOTE_A7,0,NOTE_E7,NOTE_E7,NOTE_G7,NOTE_G7,NOTE_A7,NOTE_A7,0,
  NOTE_A6,NOTE_B6,NOTE_E5,
  NOTE_E7,NOTE_E7,NOTE_G7,NOTE_G7,NOTE_A7,NOTE_A7,0,NOTE_E7,NOTE_E7,NOTE_G7,NOTE_G7,NOTE_A7,NOTE_A7,0,
  NOTE_D6,NOTE_C6,NOTE_D6,0,NOTE_C6,NOTE_D6,NOTE_E6,0,NOTE_C6,NOTE_C6,NOTE_B6,NOTE_B6,NOTE_A5,NOTE_A5,NOTE_G5,0,NOTE_C6,NOTE_B6,0,
  NOTE_D7,NOTE_E7,NOTE_E7,NOTE_E7,NOTE_G7,NOTE_G7,NOTE_A7,NOTE_A7,0,NOTE_E6,NOTE_E6,NOTE_G6,NOTE_G6,NOTE_A6,NOTE_A6,0,
  NOTE_E5,NOTE_E5,NOTE_G5,NOTE_G5,NOTE_A5,NOTE_A5,0,NOTE_E4,NOTE_E4,NOTE_G4,NOTE_G4,NOTE_A4,NOTE_A4,0,
    
};
//note durations of the winning tune
int noteDurations3[] = {  
  8,8,4,8,8,4,8,8,4,8,8,4,
  8,8,4,8,8,4,8,8,4,8,8,4,4,
  4,8,8,4,8,8,8,8,2,4,4,8,8,8,4,2,
  8,3,2,
  60,60,60,60,60,60,4,60,60,60,60,60,60,3,
  8,3,2,
  60,60,60,60,60,60,4,60,60,60,60,60,60,3,
  8,3,2,
  60,60,60,60,60,60,4,60,60,60,60,60,60,3,
  8,3,2,
  60,60,60,60,60,60,4,60,60,60,60,60,60,3,
  8,8,4,8,8,8,2,8,8,8,4,8,4,8,4,4,4,1,8,
  2,2,60,60,60,60,60,60,4,60,60,60,60,60,60,4,
  60,60,60,60,60,60,4,60,60,60,60,60,60,4,
  
  
};


int buttonState[] = {0,0,0,0};
int touchState[] = {0,0};
bool highState[] = {false,false};

//variables controlling servo movements
int movecounter[4];
int returnmovecounter[4];

bool moving[] = {false,false,false,false};

//scores
int score[] = {0,0};
int matchScore[] = {0,0};

bool fightOn = false;
void setup() {
  
  movecounter[0] = centerPos;
  movecounter[1] = centerPos;
  movecounter[2] = centerPos;
  movecounter[3] = centerPos;

  returnmovecounter[0] = maxPos;
  returnmovecounter[1] = minPos;
  returnmovecounter[2] = maxPos;
  returnmovecounter[3] = minPos;

  myservo.attach(11);
  myservo2.attach(12);
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Are you ready to");
  lcd.setCursor ( 5, 1 );
  lcd.print("rumble?");
  delay(1000);
  lcd.clear();
}

void loop() {

  while(fightOn == false )
  {
    lcd.setCursor ( 2, 0 );
    lcd.print("Both players");
    lcd.setCursor ( 0, 1 );
    lcd.print("hold left button");
    for (int thisNote = 0; thisNote < sizeof(intro)/ sizeof(int); thisNote++) {
      buttonState[0] = digitalRead(button1Pin);
      buttonState[2] = digitalRead(button3Pin);
      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations2[thisNote];
      tone(piezo, intro[thisNote], noteDuration);
  
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(piezo);
      if (buttonState[0] == HIGH && buttonState[2] == HIGH)
      {
        fightOn = true;
        thisNote = sizeof(intro)/ sizeof(int);
        lcd.clear();
      }
    }
    
  }
  buttonState[0] = digitalRead(button1Pin);
  buttonState[1] = digitalRead(button2Pin);
  buttonState[2] = digitalRead(button3Pin);
  buttonState[3] = digitalRead(button4Pin);
  touchState[0] = digitalRead(touchPin1);
  touchState[1] = digitalRead(touchPin2);

  //the closing of circuit is stored into highState-variable
  for(int i = 0; i < 2; i++)
  {
    if (touchState[i] == HIGH)
    {
      highState[i] = true;
    }
  }
  
  //a point is added to the player when the circuit opens after closing
  for(int i = 0; i < 2; i++)
  {
    if (highState[i] && touchState[i] == LOW)
    {
      score[i] += 1;
      highState[i] = false;
      for (int thisNote = 0; thisNote < sizeof(hitsound)/ sizeof(int); thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(piezo, hitsound[thisNote], noteDuration);
  
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(piezo);
      }
    }
  }

  //pressing punch or dodge defines moving-variable to true
  for(int i = 0; i < 4; i++)
  {
    if(buttonState[i] == HIGH) {
      moving[i] = true;
    }
  }

  if (moving[0] == true)
  {
    
    if(movecounter[0] < posArray[0])
    {
      movecounter[0] += stepp;
      myservo.write(movecounter[0]);
    }
    else if(movecounter[0] >= maxPos)
    {
      returnmovecounter[0] -= stepp;
      myservo.write(returnmovecounter[0]);
    }
  }
  if (moving[1] == true)
  {
    
    if(movecounter[1] > posArray[1])
    {
      movecounter[1] -= stepp;
      myservo.write(movecounter[1]);
    }
    else if(movecounter[1] <= posArray[1])
    {
      returnmovecounter[1] += stepp;
      myservo.write(returnmovecounter[1]);
    }
  }
 if (moving[2] == true)
  {
    
    if(movecounter[2] < posArray[2])
    {
      movecounter[2] += stepp;
      myservo2.write(movecounter[1]);
    }
    else if(movecounter[1] >= posArray[2])
    {
      returnmovecounter[2] -= stepp;
      myservo2.write(returnmovecounter[2]);
    }
  }
 if (moving[3] == true)
  {
    
    if(movecounter[3] > posArray[3])
    {
      movecounter[3] -= stepp;
      myservo2.write(movecounter[1]);
    }
    else if(movecounter[3] <= posArray[3])
    {
      returnmovecounter[3] += stepp;
      myservo2.write(returnmovecounter[3]);
    }
  }
  
  delay(wait);

  //if servo has returned to start position, variables are set back to initial value;
  for(int i = 0; i < 4; i++)
  {
    if (returnmovecounter[i] == centerPos)
    {
      moving[i] = false;
      movecounter[i] = centerPos;
      returnmovecounter[i] = posArray[i];
    }
  }
  lcd.print(score[0]);
  lcd.setCursor (5,1);
  lcd.print("FIGHT!");
  
  if (score[1] > 9)
    {
       lcd.setCursor(14,0);
    }
  else
    {
      lcd.setCursor(15,0);
    }
    
  lcd.print(score[1]);
  lcd.setCursor(0,0);
  if (score[1] > 9 || score[0] > 9)
  {
    lcd.clear();
    lcd.print(score[0]);
    lcd.setCursor(14,0);
    lcd.print(score[1]);
    lcd.setCursor (3,1);
    if(score[1]>9)
    {
      lcd.print("KO, P2 won!");
      matchScore[1] += 1;
    }
    else if(score[0] > 9)
    {
      lcd.print("KO, P1 won!");
      matchScore[0] += 1;
    }
    
    //playing the winning tune
    for (int thisNote = 0; thisNote < sizeof(victoryMelody)/ sizeof(int); thisNote++) {

      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations3[thisNote];
      tone(piezo, victoryMelody[thisNote], noteDuration);
  
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(piezo);
    }
    delay(3000);
    fightOn = false;
    score[0] = 0;
    score[1] = 0;
  }
}

