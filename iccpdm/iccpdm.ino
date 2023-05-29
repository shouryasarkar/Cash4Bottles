#include <Servo.h>
#include<Wire.h>
#include <LiquidCrystal.h>

const int trigPin = 9;
const int echoPin = 8;
long duration;
int distance;

const int Enter = 10;
int val = 0;

Servo myservo1;
Servo myservo2;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  
  pinMode(Enter, INPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  myservo1.attach(13);
  myservo2.attach(12);
  myservo1.write(180);
  myservo2.write(90);
}

void ultrasonic_sensor()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(100);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.print(" CM");
  delay(80);
}

void loop()
{
  ultrasonic_sensor();
  if (distance < 7)
  {
    val++;
  }
  lcd.setCursor(0,0);
  lcd.print("Bottles Counted");
  lcd.setCursor(7,1);
  lcd.print(val);
  Serial.print("\t Val = ");
  Serial.println(val);

  int one, two;

  int digitalVal = digitalRead(Enter);
  if (digitalVal == HIGH)
  {
    one = val % 2;
    two = val / 2;

    Serial.println(one);
    Serial.println(two);
    delay(1000);

    if (one == 1)
    {
      Serial.println("This is 1 Re coin");
      myservo1.write(180);
      delay(600);
      myservo1.write(100);
      delay(600);
      myservo1.write(180);
    }
    for (int i = 0; i < two; i++)
    {
      Serial.println("This is 2 Re coin");
      myservo2.write(90);
      delay(600);
      myservo2.write(180);
      delay(600);
      myservo2.write(90);
    }
    val = val - val;
  }
}
