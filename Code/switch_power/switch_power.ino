#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,10,9,8,7,6);


void SwitchPower(uint8_t var)
{
  if(var==1) 
  {
    digitalWrite(A5,1);
    digitalWrite(A4,1);
  }
  else
  {
    digitalWrite(A5,0);
    digitalWrite(A4,0);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(A5,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,0);
  pinMode(3,INPUT); // Backup Power status
  pinMode(2,INPUT); // Main power status
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Do An Tot Nghiep");
  delay(1000);
  lcd.clear();
}

int lost_pwr,backup_ready,check=0;
void loop() {
  // put your main code here, to run repeatedly:
 if((digitalRead(2) == 0)&&(lost_pwr==0)) //lost power
 {
  int i=0;
  while (digitalRead(2) == 0)
  {
    i++;
    delay(100);
    if(i>5)
    {
      lost_pwr=1;
      check=0;
      lcd.setCursor(0, 0);
      lcd.print("Lost Main POW");
      break;
    }
  }
 }
 else if(digitalRead(2) == 1)
 {
  int j=0;
  while(digitalRead(2) == 1)
  {
    j++;
    delay(100);
  }
  if(j>10)
  {
    lost_pwr=0;
    SwitchPower(0);// back to main power
    lcd.setCursor(0, 0);
    lcd.print("Run Main POW");
    lcd.setCursor(0, 1);
    lcd.print("                ");
  }
 }

 



 if((lost_pwr==1)&&(check==0))
 {
  SwitchPower(1); //switch power to backup power
  lcd.setCursor(0, 1);
  lcd.print("Switch to Backup");
  if(digitalRead(3) == 0)
  {
    delay(500);
    if(digitalRead(3) == 0) // lost backup power
    {
      lcd.setCursor(0, 1);
      lcd.print("Kick Start PSU");
      digitalWrite(A3,1) ; // kick start power backup
      delay(2000);
      digitalWrite(A3,0) ;
    }
    delay(200);
    if(digitalRead(3) == 0)  // can not start
     {
      lcd.setCursor(0, 1);
      lcd.print("PSU fail     ");
      for(int i=0; i<5; i++)
      {
      digitalWrite(13,1) ; // 
      delay(200);
      digitalWrite(13,0) ; // alarm
      delay(200);
      }
     }
     
  }
  check=1;
 }

 
}
