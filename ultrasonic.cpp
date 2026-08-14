#include <LiquidCrystal.h>
#include <Servo.h>

long duration;
int distance;
int buzzerPin = A0;
int LEDpin = 3;
const int trigPin = 10;
const int echoPin = 11;
bool printDist = true; 
bool altTone = false;

unsigned long previousServoMillis = 0;
unsigned long previousSensorMillis = 0;
const long servoInterval = 15;   // Move servo 1 degree every 15ms
const long sensorInterval = 100; // Read sensor & update LCD every 100ms
int pos = 0;
int servoDirection = 1; // 1 moves it forward, -1 moves it backward

LiquidCrystal lcd(6,7,8,9,12,13);
Servo myservo;

void setup() {
  // Gentle reminder: Changed this to 16, 2 for your 1602A display!
  lcd.begin(16, 2); 
  myservo.attach(5);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDpin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  // Get the current "time" since the Arduino turned on
  unsigned long currentMillis = millis();

  if (currentMillis - previousServoMillis >= servoInterval) {
    previousServoMillis = currentMillis; // Reset servo stopwatch

    // Move the motor
    pos = pos + servoDirection;
    myservo.write(pos);

    // Reverse direction at the limits (0 and 180)
    if (pos >= 180) {
      servoDirection = -1;
    } else if (pos <= 0) {
      servoDirection = 1;
    }
  }

  if (currentMillis - previousSensorMillis >= sensorInterval) {
    previousSensorMillis = currentMillis; // Reset sensor stopwatch

    // Trigger the sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the echo and calculate distance
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    // Check for out of bounds
    if(distance > 3000) {
      printDist = false;
    } else {
      printDist = true;
    }

    if (distance < 15) {
      if (!altTone) {
        tone(buzzerPin, 440);
        digitalWrite(LEDpin, HIGH);
        altTone = true;
      }
      else {
        tone(buzzerPin, 700);
        digitalWrite(LEDpin, LOW);
        altTone = false;
      }
    }
    else {
      noTone(buzzerPin);
      digitalWrite(LEDpin, LOW);
    }

    // Print to LCD
    if (printDist) {
      lcd.setCursor(0,0);
      lcd.print("Distance: ");
      lcd.print(distance);
      lcd.print("     "); 
    }
  }
}