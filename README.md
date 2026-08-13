# surveilance_security_robot

Arduino Surveillance Robot

A sentry-style Arduino build that scans its surroundings with an ultrasonic sensor mounted on a panning servo, displays live distance readings in centimeters, and triggers an alarm (buzzer + flashing LED) whenever an object gets closer than 15 cm.

How It Works
A servo motor sweeps the ultrasonic sensor across an approximate 200° field of view, panning back and forth like a radar dish.
At each angle, the ultrasonic sensor (HC-SR04) pings and measures the distance to the nearest object in front of it.
The distance (in cm) is shown in real time on a display.
If any detected object is closer than 15 cm, the robot treats it as an intrusion:
A passive buzzer sounds an alarm tone.
An LED flashes as a visual warning.
Once the threat clears (nothing within 15 cm), the alarm stops and the robot resumes scanning.
Hardware Used
Component	Purpose
Arduino (Uno/Nano/etc.)	Main controller
HC-SR04 Ultrasonic Sensor	Distance sensing
SG90 (or similar) Servo Motor	Pans the sensor across ~200°
16x2 LCD / OLED Display	Shows live distance reading
Passive Buzzer	Sounds the alarm
LED + resistor	Visual alarm indicator
Jumper wires, breadboard, power supply	Wiring/power

(Update this table with your exact part models/specs.)

Wiring / Pin Configuration
Component	Arduino Pin
Ultrasonic Trig	e.g. D9
Ultrasonic Echo	e.g. D10
Servo Signal	e.g. D6
Buzzer	e.g. D8
LED	e.g. D7
Display (SDA/SCL or data pins)	e.g. A4/A5 (I2C)

(Replace with your actual pin assignments.)

Alarm Logic (Summary)
For each servo angle in the sweep (0° to ~200°):
    - Move servo to angle
    - Measure distance via ultrasonic sensor
    - Show distance on display
    - If distance < 15 cm:
        - Sound buzzer
        - Flash LED
    - Else:
        - Keep buzzer/LED off
Setup Instructions
Wire the components according to the pin table above.
Install any required libraries in the Arduino IDE (e.g. Servo.h, and your display's library — LiquidCrystal.h, Adafruit_SSD1306, etc.).
Upload the sketch to your Arduino.
Power the robot and watch it pan, measure, and display distances — it will alarm automatically on close-range detection.
Possible Improvements
Add a data log (SD card or serial log) of detected distances/timestamps.
Add a mode toggle (arm/disarm) via a button or switch.
Swap the passive buzzer for a louder active siren for stronger deterrence.
Add a camera module for actual visual surveillance/recording.
Adjust the 15 cm threshold via a potentiometer for a tunable sensitivity setting.
License

Feel free to use, modify, and build on this project.
